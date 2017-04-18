echo "2,56 PLN" | gawk '{ print gensub(/([0-9]+),([0-9]+) PLN/ ,"\\1 zl i \\2 gr","g",$0 )}'
# Wynik: 2 zl i 56 gr

