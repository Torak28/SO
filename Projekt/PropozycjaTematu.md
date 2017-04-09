# Projekt

## Próba odtworzenia Mona Lisy algorytmem genetycznym z wykorzystaniem wielowątkowości.

### Założenia

Zaczynamy od dwóch takiej samej wielkości obrazów. Jeden z Nich jest znanym obrazem, np. Mona Lisą lub Leną. Na znanym obrazie wybieramy dwa punkty w sposób losowy. Na ich podstawie budujemy na znanym obrazie prostokąt dla którego liczymy średni kolor w danym kwadracie. Ten sam prostokąt wyrysujemy, dokładnie w tych samych punktach co na znanym obrazie i wypełniamy go średnim kolorem wyliczonym wcześniej. Dalej porównujemy znany obraz z naszym "dziełem" i powtarzamy całą zabawę aż uzyskamy jakiś rozsądnie podobny "twór".

Oczywiście każdy prostokąt będzie przezroczysty, przez co możliwe będzie nakładanie się.

### Grupy wątków

+ Podział obrazów(znanego i naszego) na sektory
+ zapełnianie losowymi kwadratami
+ sklejanie całości
+ wyliczanie funkcji podobieństwa


### Sam algorytm

1. Każdy jeden etap generuje 100 obrazów
2. Selekcja(wybierane jest 10 "najlepszych")
3. Krzyżowanie najlepszych(nałożenie na siebie)
4. Mutacja(lekkie zmiany w umieszczeniu punktów)
5. Ocena(jak nie jest "dobra" to wracamy do punktu **2**)

### Zasoby

+ Obraz orginalny
+ Podzielony obraz
+ Wyniki