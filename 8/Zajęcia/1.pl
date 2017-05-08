#!/usr/bin/perl

use warnings;
use File::Find;
use File::Basename;
use Cwd;

#Dane jest drzewo katalogowe. Wypisać w nim liczbę:
#a) dowiązań symbolicznych na pliki regularne
#b) dowiązań symbolicznych zdefiniowanych ścieżką względną
#c) plików regularnych posiadających co najmniej 2 dowiązania twarde

$dow = 0;
$wzg = 0;
$reg = 0;

if(@ARGV == 1){
	$sciezka = $ARGV[0];
	if(-d $sciezka){
		print "Podales dobra sciezke\n";
		find(\&print_count_if, $sciezka);
		print "dow = $dow, wzg = $wzg, reg = $reg\n";
	}
}else{
	print "Nie podano argumentu\n";
}

sub print_count_if{
	($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size,
        $atime,$mtime,$ctime,$blksize,$blocks) = stat $_;
	if( -l $_ ){
		$path = readlink($_);
		$sbr = substr $path, 0, 1;
		if ($sbr ne "/"){
			$wzg += 1;
		} 
		if ( -f $_) {
			$dow += 1;		
		}
	}else{
		if( ($nlink ==  2) && (-f $_ )){
			$reg +=1;
                }
	}
}
