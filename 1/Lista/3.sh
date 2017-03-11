#! /bin/bash/

#Kasowanie  wszystkich  plików  w  zadanym  katalogu  (parametr  wywołania  skryptu),  poza  
#plikami wykonywalnymi, mającymi ustawiony bit dostępu typu „execute”.

echo Usuwanie plikow w $1 jeśli nie są "execute"

for file in $1/*; do
	if [ -x $file -a -f $file ]
	then
		echo Usuwanie $file
		rm $file
	fi
done

#Komendy:
#-a jako AND
#-x jako czy execute 
