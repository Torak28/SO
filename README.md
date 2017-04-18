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

## Laboratorium 5 (awk)

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

+ *regex a(b|c)de* Szuka ciągu z abde lub acde
+ *regex .* Szuka dowolnego znaku
+ *regex [ab]* i *regex a|b* Są tym samym
+ *regex [~ab]* Jest odwrotnością *regex [ab]*
+ *regex [a-zA-Z0-9_]* Szuka pojedynczego znaku z zakresu od a do z lub od A do Z lub od 0 do 9 lub _
+ *regex [[:lower:][:upper:][:digit:]]* Oznacza to samo co powyższy bez znaku _
+ *[a-z[:digit:] !]* Jeden znak, który jest małą literą, cyfrą, spacją lub wykrzyknikiem

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


