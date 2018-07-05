#!/usr/bin/perl
use strict;
use Net::Ping;

my $host = $ARGV[0];

my $p = Net::Ping->new("udp");
print "$host is alive.\n" if $p->ping($host);
$p->close();
