#use Tk;
#use strict;
use IO::Socket;
use Thread::Use;
use threads qw[ async ];
use threads::shared;
#set some defaults so we don't have to worry about errors

my $user = "d2-jhamilton";
my $server = "irc.theplanet.com";
my $port = "6667";
my $filterstring = "d2|dllstx2|maint|question";
my $channel = "#pr";


my $mytextvariable;

my $configfile = "myrc.conf";
if (-e $configfile) {

  require $configfile;

} else {

  buildconfigfile();
}

my $thr = threads->new( sub {
	useit Tk;
	my $MW = Tk::MainWindow->new;
	$MW->configure(-menu => my $menubar = $MW->Menu);

	$menubar->cascade(qw/-label IRC -tearoff 0 -underline 0 -menuitems/ =>
	[
	      [command  => '~Connect', -command => [\&ircconnect]],
	      [command  => '~Disconnect', -command => [\&ircdisconnect]],
	      [command  => 'Connect ~Options', -command => [\&myoptions]]
	]);

	my $lf1 = $MW->Label(-text => 'IRC filtered')->grid(qw/-row 0 -column -0/);
	my $ircfilter = $MW->Scrolled('ROText',
	   -scrollbars         => 'e',
	    -wrap               => 'word',
	    -takefocus          => 0,
	
	)->grid(qw/-row 1 -column 0 -sticky nsew/);


	my $lf2 = $MW->Label(-text => 'IRC RAW')->grid(qw/-row 0 -column 1/);
	my $ircmain = $MW->Scrolled('ROText',
	    -scrollbars         => 'e',
	    -wrap               => 'word',
	    -takefocus          => 0,

	)->grid(qw/-row 1 -column 1 -sticky nsew/);

	my $e1 = $MW->Entry(
		-relief => 'sunken',
		-width => '180',
	)->grid(qw/-row 2 -column 0 -columnspan 2/);

	#$e1->eventAdd('<<entertext>>' => '<Return>');
	#$e1->bind('Tk::Entry','<<entertext>>'=> sub { $e1->delete(0,1000)});
	$e1->bind("<Return>", \&blahblahblah);


	my $enterbutton = $MW->Button(
		-text => 'Enter',
		-command => sub {blahblah()},
		-takefocus => "1",
	)->grid(qw/-row 2 -column 2/);




	MainLoop;
	noit Tk;
	print "blahblah";
});

$thr->join();
#ircconnect();

sub blahblahblah () {
	#$e1->delete(0,10000);
}

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
  

