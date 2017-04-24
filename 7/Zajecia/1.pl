#!/usr/bin/perl

use warnings;
use File::Copy;

#W zadanym katalogu usunąc wszystkie pliki regularne do których wykonawca skryptu
#ma prawo wykonania, ale nie ma prawa zapisu. Tworzyć kopie usuwanych plików w
#pliku nazwapliku.bak.

if(@ARGV == 1){
	$sciezka = $ARGV[0];
	if(-d $sciezka){
		print "Podales dobra sciezke\n";
		opendir(DIR, $sciezka) or die "Nie udalo sie otworzyc: $!";
		@pliki = readdir DIR;
		closedir(DIR);
		for $plik (@pliki){
			if(-f "$sciezka/$plik" and -x "$sciezka/$plik" and not(-w "$sciezka/$plik") ){
				print "tak $plik\n";
				copy("$sciezka/$plik", "$sciezka/$plik.bak") or die "Kopiowanie nie poszlo: $!";
				unlink "$sciezka/$plik";
			}else{
				print "nie $plik\n";
			}
		}
	}
}else{
	print "Nie podano argumentu\n";
}
