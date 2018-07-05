use Tk;
use strict;

my $mw = MainWindow->new;
	$mw->Label(-text => 'Myrc ver 0.1')->pack;
	$mw->Button(
		-text    => 'Quit',
		-command => sub { exit },
  	)->pack;
    my $list = $mw->Scrolled();
    $list->pack();
    $list->focus;

    $list->insert(0, qw/Alabama Alaska Arizona Arkansas California Colorado Connecticut Delaware Florida Georgia Hawaii Idaho Illinois Indiana Iowa Kansas Kentucky Louisiana Maine Maryland Massachusetts Michigan Minnesota Mississippi Missouri Montana Nebraska Nevada/, 'New Hampshire', 'New Jersey', 'New Mexico', 'New York', 'North Carolina', 'North Dakota', qw/Ohio Oklahoma Oregon Pennsylvania/, 'Rhode Island', 'South Carolina', 'South Dakota', qw/Tennessee Texas Utah Vermont Virginia Washington/, 'West Virginia', 'Wisconsin', 'Wyoming');

    $list->activate(0);
MainLoop;
