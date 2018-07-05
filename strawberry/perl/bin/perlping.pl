use strict;
use threads;
use threads::shared;
use Thread::Queue;
my $q = Thread::Queue->new();
my $pingcache;
my $host :shared = 1;
$host = $ARGV[0];

my $thr = threads->new(\&pingpoller);
$thr->detach;


sub pingpoller {
	open MYPING, "c:/windows/system32/ping.exe -t $host |" or die "$!";

	while (my $line = <MYPING>) {
		$q->enqueue($line);
	}
}


use Tk;

my $MW = Tk::MainWindow->new;
$MW->title("Nebula Ping Version 1.0");
$MW->resizable('0', '0');
$MW->geometry("500x500");
my $myicon = $MW->Photo(-file => "planetlogo.gif", -format => 'gif');

my $pingbox = $MW->Scrolled('Listbox',
	-scrollbars => 'ose',
)->pack(qw/-fill both -expand 1/);


$MW->Button(
	-text => 'Copy',
	-command => sub {
		$MW->clipboardClear;
		$MW->clipboardAppend($pingcache);
		}
)->pack();




my $repeat = $MW->repeat(100 => \&getpingdata);

sub getpingdata {
	if ($q->pending ne "0") {
		my $pingdata = $q->dequeue();
		chop $pingdata; chop $pingdata;
		$pingbox->insert('end', $pingdata);
		$pingcache = "$pingcache \n $pingdata";
		$pingdata = "";


	}
}
MainLoop;





