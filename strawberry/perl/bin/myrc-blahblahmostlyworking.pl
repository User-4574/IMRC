#!/usr/bin/perl -w
use strict;
use Socket;
use IO::Handle;
my ($port, $kidpid, $handle, $line, $server, $channel, $isjoined, $filterstring);
my $myinput;

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
print Socket_Handle "USER adsfblahtest-jhamilton 0 *  : Perl Client\n";
print Socket_Handle "NICK adsfblahtest-jhamilton\n";

die "can't fork: $!" unless defined($kidpid = fork());


if ($kidpid) {
        while (my $myline = <Socket_Handle>) {
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
#                                if ($thisline[2] =~ /$filterstring/i) {
#                                        print "$thisline2[0] : $thisline[2]";
                                       print "$myline\n";
#                                }
                        }
               }
      }

        kill("TERM", $kidpid);
} else {
        my $myline3;
        print "blah\n";
        while ($myline3 = <STDIN>) {
                print "blah\n";
#                print Socket_Handle "privmsg $channel $myline3\n";
	}
}
close Socket_Handle;