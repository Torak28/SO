#! /bin/bash/

#Kasowanie wszystkich plików pustych (o zerowej wielkości) w zadanym katalogu (parametr wywołania 
#skryptu).  Skrypt  powinien  tworzyć  w  zadanym  pliku  listę  skasowanych  plików. Nie powinien
#analizować dołączeń symbolicznych. 

echo Kasuje pliki puste w $1

PLIKI=$1/Usuniete_pliki.txt

touch $PLIKI

for file in $1/*;do
	if [ -f $file -a ! -s $file -a $file != $PLIKI ]
	then
		echo Usuwam $file
		echo $file >> $PLIKI	
		rm $file
	fi
done

#Komendy:
#-s czyli ze nie pusty
#-L -h do te dowaiazania symboliczne 
