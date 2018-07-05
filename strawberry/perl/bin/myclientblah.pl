#!/usr/bin/perl -w
use strict;
use Socket;
my ($host, $port, $kidpid, $handle, $myline, $server, $isjoined, $channel, $line);
$channel = "#pr";

unless (@ARGV == 2) { die "usage: $0 host port" }
($host, $port) = @ARGV;



my $proto = getprotobyname('tcp');
my $iaddr = inet_aton($host);
my $paddr = sockaddr_in($port, $iaddr);
socket(Socket_Handle, PF_INET, SOCK_STREAM, $proto) or die "socket: $!";
connect(Socket_Handle, $paddr) or die "connect: $!";

print Socket_Handle "USER adsfblahtest-jhamilton 0 *  : Perl Client\n";
print Socket_Handle "NICK adsfblahtest-jhamilton\n";

die "can't fork: $!" unless defined($kidpid = fork());
$isjoined = "0";

if ($kidpid) {
	while (defined ($myline = <Socket_Handle>)) {
        	if ($myline =~ /PING/) {
            		$myline =~ s/PING/PONG/;
            		print Socket_Handle "$myline\n";
            		print "$myline\n";
            		if ($isjoined == "0") {
              			print Socket_Handle "join $channel\n";
              			$isjoined = "1";
            		}
           	} else {	
			print "$myline\n";
           	}
        }
        kill("TERM", $kidpid);                  # send SIGTERM to child
} else {
        # copy standard input to the socket
        while (defined ($line = <STDIN>)) {
#            seek(Socket_Handle,0,1);
            print Socket_Handle "$line\n";
        }
}
