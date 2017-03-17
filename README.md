# Systemy Operacyjne

**Jarosław Ciołek-Żelechowski, 218386**

Zapis mojej pracy na przedmiocie. Poszczególne foldery to numery zajęć na które się przygotowałem. Wszelkie treści zadań umieściłem w samych plikach *.sh*. Co do samych materiałów to posiłkowałem się zarówno Instrukcjami, jak i Listami Zadań ze strony doktora inżyniera **Jarosława Rudego** [link](http://jaroslaw.rudy.staff.iiar.pwr.wroc.pl/dydaktyka.php)

Oprócz tego postaram się tutaj zamieścić coś w stylu notatek z przedmiotu, które będę robił w trakcie jego trwania

## Laboratorium 1

```
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