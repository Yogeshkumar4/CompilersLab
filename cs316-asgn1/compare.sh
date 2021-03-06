#!/bin/bash

rm -rf MIPSCODE
rm -rf REFERCODE
rm -rf comparison.txt

MIPS='./MIPSCODE/'
REFER='./REFERCODE/'
FLAGS='-ast -eval -symtab -d'
mkdir MIPSCODE
mkdir REFERCODE
for f in ./Examples/*.c 
do
	filename=$(echo $f | cut -d'/' -f 3)
	filename=$(echo $filename | cut -d'.' -f 1)
	./sclp $FLAGS  $f >& $MIPS$filename.txt
	./sclp16 $FLAGS  $f >& $REFER$filename.txt
	echo "The Comparison for the file $f is:" >> comparison.txt
	diff -w -i $MIPS$filename.txt $REFER$filename.txt >> comparison.txt
	echo "-------------------------------------" >> comparison.txt
done	