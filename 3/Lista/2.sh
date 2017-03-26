#! /bin/bash/

if [ $# -eq 1 ]
then
	find $1 -type f -name "*.mp3" -exec rm -f '{}' \; -printf "Usuwanie pliczkow mp3" -print
fi
