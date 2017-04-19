#! /bin/bash

# Wypisz zawartość zadanego pliku regularnego zamieniając HTML-owe kolory hashowe:
# #123456
# Na odwrócony znaczenie bgr:
# #bgr(86,52,18)

#

if [ $# -eq 1 -a -f $1 ]
then
	cat $1 | awk '\
		BEGIN { regex = "#(([0-9]){6})"}\
		{
			while(match($0, regex, tab)){
				R1 = substr(tab[1],1,1);
				R2 = substr(tab[1],2,1);
				G1 = substr(tab[1],3,1);
				G2 = substr(tab[1],4,1);
				B1 = substr(tab[1],5,1);
				B2 = substr(tab[1],6,1);
	
				j = 1;
				s = 16;

				R = (R2 * j) + (R1 * s);
				G = (G2 * j) + (G1 * s);
				B = (B2 * j) + (B1 * s);

				$0 = gensub(regex, "bgr("B","G","R")","1", $0); 
			}
			print $0;
		}'
fi

