# Systemy Operacyjne

**Jarosław Ciołek-Żelechowski, 218386**

Zapis mojej pracy na przedmiocie. Poszczególne foldery to numery zajęć na które się przygotowałem. Wszelkie treści zadań umieściłem w samych plikach *.sh*. Co do samych materiałów to posiłkowałem się zarówno Instrukcjami, jak i Listami Zadań ze strony doktora inżyniera **Jarosława Rudego** [link](http://jaroslaw.rudy.staff.iiar.pwr.wroc.pl/dydaktyka.php)

Oprócz tego postaram się tutaj zamieścić coś w stylu notatek z przedmiotu, które będę robił w trakcie jego trwania

## Laboratorium 1(test, ls, cd)

+ *chmod u+x nazwa_pliku* Nadanie plikowi atrybutu "execute"
+ *mv stara_nazwa nowa_nazwa* Zmiana nazwy pliku/katalogu
+ *rm plik*  Usunięcie pliku
+ *$plik_A = $plik_B* Porównanie nazw dwóch plików
+ *[ $ZMIENNA -eq 0 ]* Porównanie czy zmienna jest równa 0
+ *mv stare_miejsce nowe_miejsce* Nie tylko zmiana nazwy ale też i przenoszenie
+ *rmdir* Usunięcie katalogu
+ *touch nazwa_pliku* Tworzy plik
+ *touch -m* Zmiana czasu modyfikacji na aktualny
+ *[ -f $plik_A ]* Sprawdzenie czy plik_A jest plikiem
+ *[ -d $plik_A ]* Sprawdzenie czy plik_A jest katalogiem 
+ *[ -s $plik_A ]* Sprawdzenie czy plik_A nie jest pusty
+ *[ ! -s $plik_A ]* Sprawdzenie czy plik_A jest pusty
+ *[ <TEST> -a <TEST> ]* Spójnik logiczny AND
+ *[ -x $plik_A ]* Sprawdzenie czy plik_A jest "execute" 
+ *i=`expr $i + 1`* Inkrementacja zmiennej i o 1
+ *ls -S* Wypisuje pliki w zaleznosci od wielkosci
+ *>>* Przekazanie strumienia np. *echo Ala ma kota >> nazwa_pliku.txt* 
+ *cp żródło cel* Kopiowanie żródła do celu

### Uwagi

Do każdego skryptu należy sprawdzić czy ilość argumentów się zgadza, czy argumenty mają odpowiednie typy i czy aby przypadkiem Nasz użytkowni nie jest wredny.

## Laboratorium 2(dowiązania i ścieżki)

+ *ln -s sciezka_do_pliku nazwa_dowiazania* Przepis na utworzenie dowiazania symbolicznego(sciezka do pliku to cos w stylu `/home/torak28/Pulpit/SO/2/Lista`)
+ *ln -s ../1/plikA symA* Utworzenie dowiazanie sciezka wzgledna do pliku z innego pliku w katalogu znajdujacym sie w rodzicu dla miejsca z którego dowiązanie tworzymy
+ *ls -R* Rekursywne rozwiniecie 
+ *dirname* Do wypisania nadżędnego katalogu

## Laboratorium 3(komenda find)

+ *find opcje_podstawowe ścieżki_przeszukań wyrażenia_tekstowe* Idea jes taka że przeszukane będą pełne ścieżki z całymi zagnieżdżeniami, przez opcje podstawowe można rozumieć podanie np. ram zagnieżdżania albo sposób klasyfikowania plików, a przez wyrażenie tekstowe rzumiemy np. funkje wypisanie wyniku *opcji_podstawowych* na *ścieżce_przeszukań*
+ *rwxrwxrwx* dla *uuugggooo* czyli prawa dostępu do plików ułożone bitowo dla **u** użytkownika **g** grupy i **o** innych. Do sprawdzania w *find* wykorzystuje się *-perm*

**Przykłady:**
* *find . -printf Wszystko: -print -type d -printf Katalogi -print*
* *find . -perm -400 and ! -perm -020* Znalezienie plików które przyzają prawo odczytu właścicielowi ale nie przyznają przwa zapisu właścicielowi grupowemu

## Laboratorium 4(potoki)

```sh
find > wynik.txt
head < wynik.txt
```
+ Wersja bezpotokowa, z przekierowaniem
```sh
var=$(find)
head <<< $find
```
+ Wersja bezpotokowa, naiwna
```sh
find | head
```
+ Wersja potokowa(dwa procesy jadą na raz)

+ *sort* Sortowanie linia po linii
+ *tac* Odwrotność cat - łączy i listuje podane pliki
+ *rev* Czytnie liniami od tyłu. Np. keraJ jako Jarek
+ *uniq* Usuwa powtarzające się linie(do robienia z sortem)
+ *head* Wypisuje 10 pierwszych linii wejścia i igoruje reszte
+ *tail* Wypisuje 10 ostatnich linii wejscia
+ *grep* Filtrowanie
+ *tee* Podwaja standardowe wejście i wysyła je dalej i do podanego dalej pliku
+ *tr* Zastępuje podane znaki na wejściu innymi
+ *read var1 var2* Czyta wejscie i stara sie je rozdzielic na zmienne var1 i var2

```sh
find | while read var1 var2 var3
do
	(...)
done
```
+ Wylorzystanie finda, whila i read w potoku

## Laboratorium 5(awk)

+ *awk 'tekst programu' < nazwa.pliku.do.przetworzenia* Sam opis konstrukcji
+ *awk 'NR==1{print}' README.md* Wypisuje pierwszą linijkę w pliku
+ *awk '{total += $1} END {print total}' zarobki.txt* Podliczy i zsumuje wszystkie linijki w pliku
+ *awk 'BEGIN {printf "%.3f\n", 2005.50 / 3}'* Operacje zmiennoprzecinkowe
+ *awk 'NF==1{print}' nazwaPliku* Wypisze linie w pliku które mają po jednym słowie
+ *awk '{print NF}'* Wypisuje ilosc słow w linijce
+ *awk 'NR % 2 == 0 {print}' nazwaPliku* Wypisze tylko parzyste linijki pliku
+ *index(in, find)* Przeszukuje *in* w poszukiwaniu *find* i podaje pozycje
```sh
awk 'BEGIN { print index("Jarek", "ar") }'
```
+ *length(string)* Zwraca długość stringu
```sh
awk 'BEGIN {print length("Jarek")}'
```
+ *awk '{ print length($0); }' nazwaPliku.txt* Wypisuej ilość liter  linijce
+ *awk 'BEGIN {print tolower("Jarek")}'* Zmienia litery na małe
+ *awk 'BEGIN {print toupper("Jarek")}'* Zmienia litery na duże
+ *awk '{print substr($1,1,1)}' test.txt* Substring z  zadanego obszaru
+ *awk '{split($0,array,":")} END{print array[2]}' nazwaPliku.txt* Podzieli plik na części względem **:** a następnie wypisze drugą **cząstke**
```
Dla pliku:
	aa:bb:cc:dd:ee
Wynik to:
	bb
```
+ *awk -F,* Ustanawia separator między **kolumnami** na **,**
+ *awk -F, '{print $2 > $1".txt"}' nazwaPliku* Dzieli zawartość nazwyPliku ze względu na pierwsza kolumnę do plików o nazwie z pierwszej kolumnie i zawartości z drugiej. Pliki nazywamy zgodnie z kolumna pierwsza z rozszerzeniem **.txt**

## Laboratorium 6(wyrażenia regularne)

**Wstęp**
+ *regex a(b|c)de* Szuka ciągu z abde lub acde
+ *regex .* Szuka dowolnego znaku
+ *regex [ab]* i *regex a|b* Są tym samym
+ *regex [~ab]* Jest odwrotnością *regex [ab]*
+ *regex [a-zA-Z0-9_]* Szuka pojedynczego znaku z zakresu od a do z lub od A do Z lub od 0 do 9 lub _
+ *regex [[:lower:][:upper:][:digit:]]* Oznacza to samo co powyższy bez znaku _
+ *[a-z[:digit:] !]* Jeden znak, który jest małą literą, cyfrą, spacją lub wykrzyknikiem

**Rozwinięcie**
+ *a?* Znak a lub bez znaku
+ *abc?* Ciąg ab lub abc
+ *a(bc)?* Ciąg a lub abc
+ *a+* Ciąg złożonych z a
+ *(0|1|2|3|4|5|6|7|8|9)+* Ciąg cyfr
+ *[0-9]+* To samo co u góry
+ *[0-9][0-9]+* Ciąg co najmniej dwóch cyfr
+ *([0-9][0-9])+* Ciąg z parzystą liczbą cyfr
+ *a{9}* Dokładnie 9-cio elementowy ciąg liter a
+ *a{1,3}* Od 1 do 3 elementowy ciąg liter a
+ *a{1,}* Co najmniej 1 elementowy ciąg liter a

**Zakończenie**
+ */regex/ {print $0}* Wzorzec
+ */^a$/ {print $0}* Wzorzec pojedynczej litery a
+ Zmienna jako regex
```sh
BEGIN{var="regex"} 
$0 ~ var {print $0}
```
+ *match(string,regex,array)* Zaawansowane szukanie podstringów
```sh
match( $0 , /(a|b)([0-9]+)/ , tab )
```
Da dla tekstu *jakis tekst b2001*
```sh
tab[0] = b2001
tab[1] = b
tab[2] = 2001
```
+ *sub(regex, replacement, array)* Zmiana wystąpienia regexa
+ *gsub(regex, replacement, array)* Zmiana wszystkich wystąpien regexa
+ *gensub(regex, replacement, how, tab)* Nie zmienia ale operuje na kopii i ma dodatkowy operator zakresu how. Troszkę inaczej też działa na zmiennych.

Zamiana tesktu "x,xx PLN" na "x zl i xx gr"
```sh
echo "2,56 PLN" | gawk '{ print gensub(/([0-9]+),([0-9]+) PLN/ ,"\\1 zl i \\2 gr","g",$0 )}'
#Wynik: 2 zl i 56 gr
```

## Laboratorium 7(perl - podstawy)

Teraz zaczynamy programy od:

```pl
#!/usr/bin/perl

use warnings;
```

Zmienne i tablice:
```pl
$zmienna = 1;
@tab = ("nic1", "nic2", "nic3");
```

Drukowanie czegoś:
```pl
print $zmienna;
print "\n";
```

Przypisywanie elementow tablicy:
```pl
$zmienna = $tab[0];
print $zmienna;
print "\n";
```

**@tab** jako ilosc elementow tablicy:
```pl
$zmienna = @tab;
print "Ilosc elementow $zmienna\n";
```

Wypisywanie tablicy:
```pl
# Wypisanie tablicy 1
$i = 0;
for( @tab ){
	print $tab[$i];
	print "\n";
	$i++;
}
#nic1
#nic2
#nic3


# Wypisanie tablicy 2
for(@tab){
	print;
}
print "\n";
#nic1nic2nic3

# Wypisanie tablicy 3
for $_ (@tab){
	print $_;
}
print "\n";
#nic1nic2nic3

# Wypisanie tablicy 4
print @tab;
print "\n";
#nic1nic2nic3

# Wypisanie tablicy 5
print join(", ", @tab);
print "\n";
#nic1, nic2, nic3
```

Wypisanie 1 argumentu skryptu:
```pl
print $ARGV[0];
print "\n";
```

Ilosc argumentow podanych:
```pl
if(@ARGV == 1){
	print "tak 1 zmienna\n";
}else{
	print "wiecej niz 1?\n";
}
```

Otwieranie plikow do uchwytów:
```pl
# Plik zakodowany
open(UCHWYT, "<plik.txt") or die "Nie udało sie, $!";
while(<UCHWYT>){
	print "$_";
}
close(UCHWYT);

# Plik z ARGV do uchwytu
$filename = $ARGV[0];
open $UCHWYT2, "<", $filename or die $!;
print <$UCHWYT2>;
close(UCHWYT2);
```

Odpowiednik **test**:
```pl
if (-f $ARGV[0]){
	print "regularny\n"
}

$sciezka = "plik.txt";

if (-f $sciezka ){
	print "też regularny\n";
}
```

## Laboratorium 8(find)

Otwarcie katalogu do uchwytu:

```pl
opendir(DIR, $sciezka) or die "Nie udalo sie otworzyc: $!";
@pliki = readdir DIR;
closedir(DIR);
```

Dołączenie **File::Find:**
```pl
use File::Find;
```

Wypisanie nazw katalogów w ścieżce:
```pl
$sciezka = $ARGV[0];

find(\&print_name_if_dir, $sciezka);

sub print_name_if_dir{
	print $_ if -d $_;
	print "\n" if -d $_;
}
```

Hasze, czyli słowniki:
```pl
%hasz = ('klucz1' => 'wartosc1', 'klucz2' => 'wartosc2', 'klucz3' => 'wartosc3');
$hasz{ 'klucz3' } = 'wartosc3n';

for (keys %hasz){
	print "klucz to " . $_;
	print " wartosc to " . $hasz{ $_ };
	print "\n";
}
```

wypisanie wielkosci pliczkow:
```pl
find(\&print_name_if_dir, $sciezka);

sub print_name_if_dir{
	($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size,
        $atime,$mtime,$ctime,$blksize,$blocks) = stat $_;
	if( -f $_ ){
		print "$_ $size \n";
	}
}
```

## Laboratorium 9(wyrazenia refularne)

Dzielenie i łączenie:
```pl
print join(':', split(//, 'abc')), "\n";
#output: a:b:c

print join(':', split(/b/, 'abc')), "\n";
#output: a:c

print join(':', split(//, 'abc', 1)), "\n";
#output: abc

print join(':', split(//, 'abc', 2)), "\n";
#output: a:bc

print join(':', split(//, 'abc', 3)), "\n";
#output: a:b:c
```

Transliteracja i podstawienie:
```pl
$string = "To+jest+mój+text\n";
print $string;
$string =~ tr/+/ /;
print $string, "\n";
#output: To jest moj text

$string = "To-jest-moj-text\n";
print $string;
$string =~ s/\-/ /g;
print $string;
#output: To jest moj text
```

Transliteracja:
```pl
$tekst = "0Ala123 ma45 kota6789";
$tekst2 = "0Ala123 ma45 kota6789";
$tekst3 = "0Ala123 ma45 kota6789";

$tekst =~ tr/0-9/*/;
#Cyfry na *
print $tekst, "\n";
#output: *Ala*** ma** kota****

$tekst2 =~ tr/0-9/*/c;
#Odwrotność cyfr na gwiazdki
print $tekst2, "\n";
#output: 0***123***45*****6789


$tekst3 =~ tr/0-9/*/d;
#Wszystkie zera na gwiazdki a inne cyfry usuwa!
print $tekst3, "\n";
#output: *Ala ma kota

$tekst4 =~ tr/0-9/*/s;
#Squash duplicate replaced characters?
print $tekst4, "\n";
#output: Ala* ma* kota*

$tekst5 =~ tr/0-9/*/r;
#Sam tekst5 jest niezmieniony ale zapytanie zwrocilo zmieniony tekst
print $tekst5, "\n";
#output: 0Ala123 ma45 kota6789
```

Split:
```pl
$x = "Moj super        tekst";
@word = split /\s+/, $x;
# \s+ dzieli na slowa, lepsze to niz ' ' bo zadaiala przy duzych ilosci spacji

print $x, "\n";

print $word[0], "\n";
#output: Moj
print $word[1], "\n";
#output: super
print $word[2], "\n";
#output: tekst

print "\n";

$x2 = "1.618,2.718,   3.142";
@const = split /,\s*/, $x2;
# \s* dzieli na liczby!
print $x2, "\n";

print $const[0], "\n";
#output: 1.618
print $const[1], "\n";
#output: 2.718
print $const[2], "\n";
#output: 3.142

print "\n";

$x3 = "/usr/bin";
@parts = split m!(/)!, $x3;
# split po // z uzyciem matcha do zgrupowania po /
print $x3, "\n";

print $parts[0], "\n";
#output: ''
print $parts[1], "\n";
#output: '/'
print $parts[2], "\n";
#output: 'usr'
print $parts[3], "\n";
#output: '/'
print $parts[4], "\n";
#output: 'bin'
```

Jeszcze więcej zamieniania słów:
```pl
$x = "Moj super        tekst";
@word = split /\s+/, $x;
# \s+ dzieli na slowa, lepsze to niz ' ' bo zadaiala przy duzych ilosci spacji

print $x, "\n";

print $word[0], "\n";
#output: Moj
print $word[1], "\n";
#output: super
print $word[2], "\n";
#output: tekst

print "\n";

$x2 = "1.618,2.718,   3.142";
@const = split /,\s*/, $x2;
# \s* dzieli na liczby!
print $x2, "\n";

print $const[0], "\n";
#output: 1.618
print $const[1], "\n";
#output: 2.718
print $const[2], "\n";
#output: 3.142

print "\n";

$x3 = "/usr/bin";
@parts = split m!(/)!, $x3;
# split po // z uzyciem matcha do zgrupowania po /
print $x3, "\n";

print $parts[0], "\n";
#output: ''
print $parts[1], "\n";
#output: '/'
print $parts[2], "\n";
#output: 'usr'
print $parts[3], "\n";
#output: '/'
print $parts[4], "\n";
#output: 'bin'


$x4 = "Time to feed the cat!";
print $x4, "\n";
$x4 =~ s/cat/hacker/;
print $x4, "\n";
#output: Time to feed the hacker!

$x5 = "'quoted words'";
print $x5, "\n";
$x5 =~ s/^'(.*)'$/$1/;
print $x5, "\n";
# output: "quoted words"
```

Maczowanie w pełnej okrasie:
```pl
print "Tak\n" if "Hello World" =~ /World/;
#Maczuje =~

print "Nie\n" if "Hello World" !~ /World/;
#Nie maczuje !~


$var = "World";
print "Maczuje\n" if "Hello World" =~ /$var/;

"Hello World" =~ /world/;  # Nope nie ta wielkosc liter
"Hello World" =~ /o W/;    # Yup ' ' traktowana jako normalna spacja
"Hello World" =~ /World /; # Nope nie ma ' ' pod koniec :c

"Hello World" =~ /o/;       # Maczuje 'o' w Hello
"That hat is red" =~ /hat/; # Maczuje 'hat' w that

"2+2=4" =~ /2+2/;    # Nope '+' psuje
"2+2=4" =~ /2\+2/;   # Maczuje '+' jest poprzedzony \


"housekeeper" =~ /keeper/;         # Yup
"housekeeper" =~ /^keeper/;        # Nope nie ma czegoś takiego na początku
"housekeeper" =~ /keeper$/;        # Yup
"housekeeper\n" =~ /keeper$/;      # Yup
"housekeeper" =~ /^housekeeper$/;  # Yups

"cat" =~ /cat/;            # Maczuje 'cat'
"cat" =~ /[bcr]at/;        # Maczuje 'bat', 'cat', lub 'rat'
"a15" =~ /[0-9a-fA-F]/;    # Maczuje Hex

"yEs" =~ /[yY][eE][sS]/; # Maczuje yes w każdej znakowej kombinacji
"yEs" =~ /yes/i;         # To samo co powyżej ale krócej

$x = "Housecat catenates house and cat";
$x =~ /\bcat/;  # matches cat in 'catenates'
$x =~ /cat\b/;  # matches cat in 'housecat'
$x =~ /\bcat\b/;  # matches 'cat' at end of string
```