# Projekt

Poniżej zamieściłem trzy propozycje tematu:

+ **Restauracja / Zarządzanie kuchnią**
+ **Wataha / Kolonia zwierząt**
+ **Hotel / Zarządzanie zasobem**

Przy czym jeśli akceptuje Pan pierwszą to proszę drugiej i trzeciej nawet nie czytać.

## Restauracja / Zarządzanie kuchnią

### Założenia

Restauracja w iście Francuskim stylu. Z osobnymi kucharzami do poszczególnych etapów przygotowania dania i z kucharzem zarządzającym. Do tego zbiór kelnerów obsługujących gości i zmywak. Całość polega na tym by talerz z kuchni został dostarczony do klienta, dalej do zmywaka i z powrotem na kuchnie. Samo przygotowanie potrawy wynika z jego przepisu(dla uproszczenia można założyć np.5 przepisów) oraz dostępności poszczególnych Mistrzów w swoim fachu. Do tego Kelner i Klienci, zanoszący i jedzący potrawy w losowych czasach z jakiegoś przedziału. Na końcu czeka na talerz zmywak, który w określonym czasie czyści talerze pojedynczo.

### Grupy wątków
+ Kelnerzy
+ Główny kucharz
+ Mistrz sosów
+ Mistrz mięsa
+ Mistrz sałatek
+ Mistrz zup
+ Mistrz wypieków
+ Zmywak
+ Klienci

### Zasoby
+ Talerze

Idea jest taka żeby tak obsługiwać talerzami, tj. przekazywać z kuchni na salę i do zmywaka tak żeby ich nie zabrakło.

## Wataha / Kolonia zwierząt

### Założenia

Na jakimś obszarze o zadeklarowanej wielkości żyje stado wilków zajmując powierzchnie równą jego liczebności. Cała powierzchnia dostępna jest znacząco większa od powierzchni zajmowanej przez wilki. Zajmując jakiś teren wataha "grabi" go z zasobów. Zasoby odrastają naturalnie w określonym czasie gdy pola na których rosną nie są zajmowane przez watahę. Oczywiście wilk nie jedząc "traci" zasoby. Tym samym stado musi ciągle zmieniać swoje położenie. 
Co więcej wataha dzieli się na samce i samice. Ilość samic i samców jest losowana na starcie programu. Samice by się rozmnażać potrzebują być "najedzone" tak samo jak samce(Można przyjąć jakieś 5 zasobów na osobnika). Samice opiekują się młodymi przez określoną liczbę tur, podczas których potrzebują więcej jedzenia. Płeć młodego wilka jest losowana. 
Nad całą wataha i jej pomyślnością stoi najstarszy wilk - przywódca stada. Po przeżyciu określonej długości życia wilk umiera, oczywiście zakładając że wcześniej nie umarł z głodu(przez np. 5 tur niczego nie jadł).

### Grupy wątków
+ Samiec Alfa
+ Samce
+ Samice
+ Teran(odnawianie się zasobów i och kontrola)

### Zasoby
+ Pożywienie
+ Wiek wilka(w sensie możliwości wyczerpania)

## Hotel / Zarządzanie zasobem

### Założenia

W hotelu o skończonej liczbie pięter jest określona ilość pokoi na piętro. Pokoi dla trzech, dwóch i jednej osoby. Do recepcji schodzą goście i trzeba ich jakoś rozlokować.
Dodatkowo w hotelu znajdują się dwie windy o określonym udźwigu. Każdy z gości hotelowych zabiera ze sobą losowy bagaż. Do boy ‘a hotelowego należy dostarczenie ich w jak najszybszym czasie i w sposób najbardziej efektowny.

### Grupy wątków
+ Recepcja
+ Pokoje
+ Boy

### Zasoby
+ Bagaże
+ Windy
