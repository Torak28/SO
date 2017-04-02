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
