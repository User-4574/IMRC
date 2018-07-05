sub printtime {
	my $now = localtime;
	if ($now =~ /(\d\d:\d\d:\d\d)/) {
		$now = $1;
	}
	return $now;
}
print printtime();