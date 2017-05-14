#!/usr/bin/perl

use warnings;

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
"housekeeper" =~ /^housekeeper$/;  # Yup

"cat" =~ /cat/;            # Maczuje 'cat'
"cat" =~ /[bcr]at/;        # Maczuje 'bat', 'cat', lub 'rat'
"a15" =~ /[0-9a-fA-F]/;    # Maczuje Hex

"yEs" =~ /[yY][eE][sS]/; # Maczuje yes w każdej znakowej kombinacji
"yEs" =~ /yes/i;         # To samo co powyżej ale krócej

$x = "Housecat catenates house and cat";
$x =~ /\bcat/;  # matches cat in 'catenates'
$x =~ /cat\b/;  # matches cat in 'housecat'
$x =~ /\bcat\b/;  # matches 'cat' at end of string
