#! /bin/bash/

#Utworzenie katalogu lab2, w nim utworzenie 4 katalogów, w pierwszym należało stworzyć 3 pliki (wypełnione), w drugim katalogu trzeba było utworzyć dowiązania symboliczne do plików z katalogu pierwszego (do pliku 1 i 2 ze ścieżką względną, do 3 ze ścieżką bezwzględną), trzeci katalog miał zawierać dowiązanie do katalogu 2, w katalogu czwartym miały znaleźć się skopiowane dowiązania z katalogu drugiego. Na początku skryptu należało usunąć katalog lab2- jeżeli istniał.


LAB=Katalog
for file in `ls`; do
	if [ -d $file -a $file = $LAB ]
	then
		rm -rf $file
		mkdir $LAB
		mkdir $LAB/1
		mkdir $LAB/2
		mkdir $LAB/3
		mkdir $LAB/4
		echo "plikA" >> $LAB/1/plikA
		echo "plikB" >> $LAB/1/plikB
		echo "plikC" >> $LAB/1/plikC
		ln -s ../1/plikA $LAB/2/symA
		ln -s ../1/plikB $LAB/2/symB
		ln -s /home/torak28/Pulpit/SO/2/Lista/$LAB/1/plikC $LAB/2/symC
		ln -s ../2 $LAB/3/sym2
		cp $LAB/2/symA $LAB/4
		cp $LAB/2/symB $LAB/4
		cp $LAB/2/symC $LAB/4
	fi
done


