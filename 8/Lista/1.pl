#!/usr/bin/perl

use warnings;
use File::Find;

$sciezka = $ARGV[0];

find(\&print_name_if_dir, $sciezka);

sub print_name_if_dir{
	print $_ if -d $_;
	print "\n" if -d $_;
}
