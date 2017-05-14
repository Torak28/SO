#!/usr/bin/perl

use warnings;

$string = "To+jest+mój+text\n";
print $string;
$string =~ tr/+/ /;
print $string, "\n";
#output: To jest moj text

$string = "To-jest-moj-text\n";
print $string;
$string =~ s/\-/ /g;
print $string;
#output: To jest moj text


$tekst = "0Ala123 ma45 kota6789";
$tekst2 = "0Ala123 ma45 kota6789";
$tekst3 = "0Ala123 ma45 kota6789";
$tekst4 = "0Ala123 ma45 kota6789";
$tekst5 = "0Ala123 ma45 kota6789";



$tekst =~ tr/0-9/*/;
#Cyfry na *
print $tekst, "\n";
#output: *Ala*** ma** kota****

$tekst2 =~ tr/0-9/*/c;
#Odwrotność cyfr na gwiazdki
print $tekst2, "\n";
#output: 0***123***45*****6789


$tekst3 =~ tr/0-9/*/d;
#Wszystkie zera na gwiazdki a inne cyfry usuwa!
print $tekst3, "\n";
#output: *Ala ma kota

$tekst4 =~ tr/0-9/*/s;
#Squash duplicate replaced characters?
print $tekst4, "\n";
#output: Ala* ma* kota*

$tekst5 =~ tr/0-9/*/r;
#Sam tekst5 jest niezmieniony ale zapytanie zwrocilo zmieniony tekst
print $tekst5, "\n";
#output: 0Ala123 ma45 kota6789
