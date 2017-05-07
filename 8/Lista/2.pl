#!/usr/bin/perl

use warnings;
use File::Find;

%hasz = ('klucz1' => 'wartosc1', 'klucz2' => 'wartosc2', 'klucz3' => 'wartosc3');
$hasz{ 'klucz3' } = 'wartosc3n';

for (keys %hasz){
	print "klucz to " . $_;
	print " wartosc to " . $hasz{ $_ };
	print "\n";
}
