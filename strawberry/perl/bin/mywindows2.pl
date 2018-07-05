use Tk;
use strict;
my @top1;


my $mw = MainWindow->new;
	$mw->Label(-text => 'blah')->pack;
my $top1[0] = $mw->Toplevel;
	$top1[0]->Label(-text => 'blah2')->pack;
MainLoop;