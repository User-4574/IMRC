#!/usr/bin/perl -w
use strict;
use Socket;
use IO::Select;
use IO::Handle;
my ($port, $kidpid, $handle, $line, $server, $channel, $isjoined, $filterstring, $myline);
my $myinput;
my $pollTime = ".1";
my $delay = ".1";
#my $buf;
my $bits1;

#unless (@ARGV == 2) { die "usage: $0 host port" }
#($host, $port) = @ARGV;


$channel = "#pr";
$server = "irc.theplanet.com";
$port = "6667";
$isjoined = "0";
$filterstring = "d2|dllstx2|maint|help";

my $proto = getprotobyname('tcp');
my $iaddr = inet_aton($server);
my $paddr = sockaddr_in($port, $iaddr);
socket(Socket_Handle, PF_INET, SOCK_STREAM, $proto) or die "socket: $!";
connect(Socket_Handle, $paddr) or die "connect: $!";



select(Socket_Handle); $| = 1; select(STDOUT); $| = 1; select(STDIN); $| = 1; select(STDOUT);
#$|=1;
#autoflush Socket_Handle 1;
Socket_Handle->autoflush(1);
print Socket_Handle "USER blahtest-jhamilton 0 *  : Perl Client\n";
print Socket_Handle "NICK blahtest-jhamilton\n";

die "can't fork: $!" unless defined($kidpid = fork());

my $blocking = 1;
ioctl(Socket_Handle, 0x8004667E, \&blocking);


if ($kidpid) {
	#this polling shit is necessary since you can't simultaneosly read and write to a socket in windows
	vec($bits1,fileno(Socket_Handle),1)=1;
	while(1) {
		my $rc=select(my $rout1=$bits1,my $wout1=$bits1,my $eout1=$bits1,$pollTime); # poll
		if ( vec($rout1,fileno(Socket_Handle),1) ) {
#			sysread( Socket_Handle, $myline, 1000 );
			$myline = <Socket_Handle>;
	                if ($myline =~ /PING/) {
	                        $myline =~ s/PING/PONG/;
	                        print Socket_Handle $myline;
	                        if ($isjoined == "0") {
	                                print Socket_Handle "join $channel\n";
	                                $isjoined = "1";
	                        }
	               } else {
	                        my @thisline = split /:/, $myline;
	                        my @thisline2 = split /!/, $thisline[1];
	                        if ($thisline[2]) {
#	                                if ($thisline[2] =~ /$filterstring/i) {
#	                                        print "$thisline2[0] : $thisline[2]";
                                       print "$myline\n";
#	                                }
	                        }
	               }
		}
	}




#	while(my $myline = <Socket_Handle>) {
#                if ($myline =~ /PING/) {
#                        $myline =~ s/PING/PONG/;
#                        print Socket_Handle $myline;
#                        if ($isjoined == "0") {
#                                print Socket_Handle "join $channel\n";
#                                $isjoined = "1";
#                        }
#               } else {
#                        my @thisline = split /:/, $myline;
#                        my @thisline2 = split /!/, $thisline[1];
#                        if ($thisline[2]) {
##                                if ($thisline[2] =~ /$filterstring/i) {
##                                        print "$thisline2[0] : $thisline[2]";
#                                       print "$myline\n";
##                                }
#                        }
#               }
#      }

        kill("TERM", $kidpid);
} else {
        while ($myline = <STDIN>) {
                print Socket_Handle "privmsg $channel $myline\n";
	}
}
close Socket_Handle;