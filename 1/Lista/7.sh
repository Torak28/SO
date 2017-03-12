#! /bin/bash/

#Przesuwanie  wszystkich  plików  z  ustawionym  prawem  wykonywania  z  jednego  katalogu  do  
#drugiego.   Pozostałe   pliki   w   katalogu   nie   powinny   być  ruszane.   Nazwy   katalogów,   
#źródłowego i docelowego, zadawane jako parametry skryptu.  

echo przecoszenie wszystkich "execute" z $1 do $2

for file in $1/*; do
	if [ -f $file -a -x $file ]
	then
		echo Kopiowanie $file do $2/
		cp $file "$2"/
	fi
done

#Komendy
#cp - kopiowanie
