#! /bin/bash/

#Łączenie w jeden wszystkich plików należących do zadanego katalogu (parametr wywołania 
#skryptu), o zadanym rozszerzeniu (drugi parametr skryptu). Kolejność, w jakiej pliki zostaną
#połączone  -  nieistotna.  Treść  każdego  pliku  powinna  być  poprzedzona  nagłówkiem  z  jego  
#nazwą

echo Łącze pliki z $1 w jeden plik tekstowy

#Tworzenie pliczku:
PLICZKI=$1/pliczki$2
touch $PLICZKI

for file in $1/*;do
	if [ -f $file -a $file != $PLICZKI ]
	then
		echo Zapisywanie $file
		echo $file >> $PLICZKI
		cat $file >> $PLICZKI
		echo "" >> $PLICZKI
	fi
done

#Komendy:
# >> jako przekazanie strumienia 
