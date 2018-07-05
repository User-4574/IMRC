#!/usr/bin/perl -w
use strict;
use Socket;
my ($host, $port, $kidpid, $handle, $line, $server);


unless (@ARGV == 2) { die "usage: $0 host port" }
($host, $port) = @ARGV;



my $proto = getprotobyname('tcp');
my $iaddr = inet_aton($host);
my $paddr = sockaddr_in($port, $iaddr);
socket(Socket_Handle, PF_INET, SOCK_STREAM, $proto) or die "socket: $!";
connect(Socket_Handle, $paddr) or die "connect: $!";



die "can't fork: $!" unless defined($kidpid = fork());

if ($kidpid) {
        # copy the socket to standard output
        while (defined ($line = <Socket_Handle>)) {
            print STDOUT $line;
        }
        kill("TERM", $kidpid);                  # send SIGTERM to child
} else {
        # copy standard input to the socket
        while (defined ($line = <STDIN>)) {
            print Socket_Handle "$line\n";
        }
}
