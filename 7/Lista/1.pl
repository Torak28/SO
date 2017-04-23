#!/usr/bin/perl

use warnings;

# hello world
print "Hello\n";

# Zmienne i tablica
$zmienna = 1;
@tab = ("nic1", "nic2", "nic3");

# Drukowanie zmiennej
print $zmienna;
print "\n";

# Przypisanie pod zmiennej elementu tablicy
$zmienna = $tab[0];
print $zmienna;
print "\n";

# @tab jako ilosc elementow tablicy
$zmienna = @tab;
print "Ilosc elementow $zmienna\n";

# Wypisanie tablicy 1
$i = 0;
for( @tab ){
	print $tab[$i];
	print "\n";
	$i++;
}

# Wypisanie tablicy 2
for(@tab){
	print;
}
print "\n";

# Wypisanie tablicy 3
for $_ (@tab){
	print $_;
}
print "\n";

# Wypisanie tablicy 4
print @tab;
print "\n";

# Wypisanie tablicy 5
print join(", ", @tab);
print "\n";

# Wypisanie 1 argumentu
print $ARGV[0];
print "\n";

# Sprawdzenie ilości argumentow
if(@ARGV == 1){
	print "tak 1 zmienna\n";
}else{
	print "wiecej niz 1?\n";
}

#Otwarcie pliku do uchwytu
open(UCHWYT, "<plik.txt") or die "Nie udało sie, $!";

#Czytanie cąłości
while(<UCHWYT>){
	print "$_";
}

#Zamykamy!
close(UCHWYT);

# Plik z ARGV do uchwytu
$filename = $ARGV[0];
open $UCHWYT2, "<", $filename or die $!;
print <$UCHWYT2>;
close(UCHWYT2);

# Sprawdzenie czy plik z ARGV jest regularny
if (-f $ARGV[0]){
	print "regularny\n"
}

$sciezka = "plik.txt";

if (-f $sciezka ){
	print "też regularny\n";
}
