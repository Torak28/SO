#!/usr/bin/perl

use File::Find;

$sciezka = $ARGV[0];

find(\&print_name_if_dir, $sciezka);

sub print_name_if_dir{
	($dev,$ino,$mode,$nlink,$uid,$gid,$rdev,$size,
        $atime,$mtime,$ctime,$blksize,$blocks) = stat $_;
	if( -f $_ ){
		print "$_ $size \n";
	}
}
