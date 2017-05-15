#!/usr/bin/perl

use warnings;

#Dany jest plik regularny. Dla każdej linii zawierającej tylko imiona i nazwiska wypisz
#wersje tej linii z użyciem inicjałów imion. Nie wypisywać pozostałych linii.

if(@ARGV == 1){
	$sciezka = $ARGV[0];
	if(-f $sciezka){
		open( $fh => $sciezka ) || die "Nie wyszlo otwieranie: $!";
		while($line = <$fh> ) {
			@slowa = split /\s+/, $line;
			$ile = @slowa;
			$maks = $ile-1;
			$sukces = 0;
			for($i = 0; $i < $maks; $i++){
				if ($slowa[$i] =~ /^[A-Z]/ and $slowa[$i] =~ /[a-z]$/ and $slowa[$i] =~ /[A-Za-z]/){
					$sukces += 1;
					if($sukces == $maks){
						if($slowa[-1] =~ /^[A-Z]/){
							for($j = 0; $j < $maks; $j++){
								@inicjaly = split //, $slowa[$j];
								print $inicjaly[0], ". ";
							}
							print $slowa[-1],"\n";
						}
					}
				}
			#Tutaj wypisanie nazwiska
			}
		}	
	}
}else{
	print "Nie podano argumentu\n";
}
