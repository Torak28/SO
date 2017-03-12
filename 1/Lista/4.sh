#! /bin/bash/

#Numerowanie  wszystkich  plików  w  zadanym  katalogu  (parametr  wywołania  skryptu),  do  
#których  mamy  ustawione  prawo  wykonywania  („execute”),  przez  dodanie  dodatkowego  
#członu  rozszerzenia  o  postaci  .<numer kolejny>.  Numeracja  powinna  przebiegać według 
#wielkości plików.


echo Numerowanie plikow "execute" w $1, w kolejności według wielkosci 

ITERATOR=1

for file in `ls -S $1`; do
	if [ -x "$1"/$file -a -f "$1"/$file ]
	then
		echo zmiana nazwy $file na $file.$ITERATOR
		mv "$1"/$file "$1"/$file.$ITERATOR
		ITERATOR=`expr $ITERATOR + 1`
	fi
done

#Komendy:
#i=`expr $i + 1`
#ls -S grupuje pliki w zaleznosci od wielkosci
