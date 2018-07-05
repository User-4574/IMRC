#!/usr/bin/perl -w

use IO::Socket;
use strict;
my $user = "asdfblahblahd2-jhamilton";
my $server = "irc.theplanet.com";
my $port = "6667";
my $filterstring = "d2|dllstx2|maint|question";
my $channel = "#pr";





my $isjoined = "0";
my $blah = "0";
my $clientsock = IO::Socket::INET->new(
        Proto => "tcp",
        PeerAddr => $server,
        PeerPort => $port,
) or die "cannot connect";

$clientsock->autoflush(1);
print $clientsock "USER  $user 0 *  : Perl Client\n";
print $clientsock "NICK $user\n";

die "can't fork: $!" unless defined(my $kidpid = fork());
die "can't fork: $!" unless defined(my $kidpid2 = fork());
if ($kidpid) {
        while (my $myline = <$clientsock>) {
		$clientsock->flush();
                if ($myline =~ /PING/) {
                        $myline =~ s/PING/PONG/;
                        print $clientsock $myline;
                        if ($isjoined == "0") {
                                print $clientsock "join $channel\n";
                                $isjoined = "1";
                        }
               } else {
                        my @thisline = split /:/, $myline;
                        my @thisline2 = split /!/, $thisline[1];
                        if ($thisline[2]) {
                                if ($thisline[2] =~ /$filterstring/i) {
                                        print "$thisline2[0] : $thisline[2]";
#                                       print "$myline\n";
                                }
                        }
               }
      }

        kill("TERM", $kidpid);
} elsif ($kidpid2) {
        sleep 2;
        print "\e[2J";
        kill("TERM", $kidpid2);
} else {
        my $myline3;
        print "blah\n";
        while ($myline3 = <STDIN>) {
                print "blah\n";
		$clientsock->flush();
#                print $clientsock "privmsg $channel $myline3\n";
                print $clientsock "$myline3\n";
        }
}
close $clientsock;
