use Tk;
use strict;
use IO::Socket;

#set some defaults so we don't have to worry about errors

my $user = "d2-jhamilton";
my $server = "irc.theplanet.com";
my $port = "6667";
my $filterstring = "d2|dllstx2|maint|question";
my $channel = "#pr";


my $configfile = "myrc.conf";
if (-e $configfile) {

  require $configfile;

} else {

  buildconfigfile();
}

my $MW = Tk::MainWindow->new;
$MW->configure(-menu => my $menubar = $MW->Menu);

#	my $file = $menubar->cascade(qw/-label Connect -underline 0 -menuitems/ =>
#    [
#     [command => '~Connect', -command => [\&ircconnect]],
#      [command => '~Disconnect', -command => [\&ircconnect]],
#    ],]);

$menubar->cascade(qw/-label IRC -tearoff 0 -underline 0 -menuitems/ =>
    [
      [command  => '~Connect', -command => [\&ircconnect]],
      [command  => '~Disconnect', -command => [\&ircdisconnect]],
      [command  => 'Connect ~Options', -command => [\&myoptions]]
    ]);

my $ircmain = $MW->Scrolled('ROText',
    -scrollbars         => 'e',
    -wrap               => 'word',
    -width              => 70,
    -height             => 30,
    -setgrid            => 1,
    -highlightthickness => 0,
    -padx               => 4,
    -pady               => 2,
    -takefocus          => 0,
)->grid(qw/-sticky nsew/);
#$MW->gridRowconfigure(   0, -weight => 1); # allow expansion in both ...
#$MW->gridColumnconfigure(0, -weight => 1); # ... X and Y dimensions


MainLoop;

sub ircdisconnect () {
print "blah";
}


sub ircconnect() {
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
                                            #$ircmain->insert("$thisline2[0] : $thisline[2]");
                                  }
                          }
                 }
        }

          kill("TERM", $kidpid);
  } elsif ($kidpid2) {
#          sleep 2;
#          print "\e[2J";
#          kill("TERM", $kidpid2);
  } else {
          while (defined (my $myline2 = <STDIN>)) {
                  print $clientsock "privmsg $channel $myline2\n";
          }
  }
  close $clientsock;
}

sub buildconfigfile() {
  open(MYCONFIGFILE, ">myrc.conf");
  print MYCONFIGFILE "my \$user = \"$user\";\n";
  print MYCONFIGFILE "my \$server = \"$server\";\n";
  print MYCONFIGFILE "my \$port = \"$port\";\n";
  print MYCONFIGFILE "my \$channel = \"$channel\";\n";
  close(MYCONFIGFILE);
}
  

