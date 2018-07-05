use Tk;
use strict;

my $mw = MainWindow->new;
	$mw->Label(-text => 'Myrc ver 0.1')->pack;
    my $list = $mw->Scrolled(qw/Listbox -setgrid 1 -height 12 -scrollbars e/);
    $list->pack();
    $list->focus;

    $list->insert(0, qw/Alabama Alaska/);

    $list->activate(0);
	$mw->Button(
		-text    => 'blah',
		-command => sub { $list->insert(0, 'blah'); },
  	)->pack;
MainLoop;






