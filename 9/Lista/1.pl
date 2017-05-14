#!/usr/bin/perl

use warnings;

print join(':', split(//, 'abc')), "\n";
#output: a:b:c

print join(':', split(/b/, 'abc')), "\n";
#output: a:c

print join(':', split(//, 'abc', 1)), "\n";
#output: abc

print join(':', split(//, 'abc', 2)), "\n";
#output: a:bc

print join(':', split(//, 'abc', 3)), "\n";
#output: a:b:c

