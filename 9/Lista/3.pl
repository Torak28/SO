#!/usr/bin/perl

use warnings;

$x = "Moj super        tekst";
@word = split /\s+/, $x;
# \s+ dzieli na slowa, lepsze to niz ' ' bo zadaiala przy duzych ilosci spacji

print $x, "\n";

print $word[0], "\n";
#output: Moj
print $word[1], "\n";
#output: super
print $word[2], "\n";
#output: tekst

print "\n";

$x2 = "1.618,2.718,   3.142";
@const = split /,\s*/, $x2;
# \s* dzieli na liczby!
print $x2, "\n";

print $const[0], "\n";
#output: 1.618
print $const[1], "\n";
#output: 2.718
print $const[2], "\n";
#output: 3.142

print "\n";

$x3 = "/usr/bin";
@parts = split m!(/)!, $x3;
# split po // z uzyciem matcha do zgrupowania po /
print $x3, "\n";

print $parts[0], "\n";
#output: ''
print $parts[1], "\n";
#output: '/'
print $parts[2], "\n";
#output: 'usr'
print $parts[3], "\n";
#output: '/'
print $parts[4], "\n";
#output: 'bin'


$x4 = "Time to feed the cat!";
print $x4, "\n";
$x4 =~ s/cat/hacker/;
print $x4, "\n";
#output: Time to feed the hacker!

$x5 = "'quoted words'";
print $x5, "\n";
$x5 =~ s/^'(.*)'$/$1/;
print $x5, "\n";
# output: "quoted words"
