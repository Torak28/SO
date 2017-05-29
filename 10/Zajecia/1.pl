#!/usr/bin/perl

#use warnings;
use Cwd 'abs_path';

#W zadanym katalogu usunąć wszystkie niepoprawne(wiszące) linki symboliczne, a  poprawne zmienić
#na linki twarde

if(@ARGV == 1){
	$sciezka = $ARGV[0];
	if(-d $sciezka){
		print "Podales dobra sciezke\n";
		opendir(DIR, $sciezka) or die "Nie udalo sie otworzyc: $!";
		@pliki = readdir DIR;
		closedir(DIR);
		for $plik (@pliki){
			if( -l "$sciezka/$plik") {
               			 if ( -e "$sciezka/$plik"){
                        		$abs_path = abs_path("$sciezka/$plik");
					$nowy = "$sciezka$plik";
					#TWORZENIE I USUWANIE STAREGO
					unlink "$sciezka/$plik";
					link $abs_path, $nowy;
                		}	
               			 if ( ! -e "$sciezka/$plik"){
                        		#USUWANIE
					unlink "$sciezka/$plik";
                		}
        		}
		}
	}else{
		print "Zly argument\n";
	}
}else{
	print "Nie podano argumentu\n";
}
