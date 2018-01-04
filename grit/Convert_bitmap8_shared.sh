#!/bin/bash


rm bitmap8/*.img
rm bitmap8/*.pal


wine grit.exe bmp/*.bmp -gb -gu8 -gB8 -pu16 -pS -ftb -fh! -Omypal.pal -gTFF00FF
for f in `ls *.bin`
do
	echo "Processing file $f ..."
	FILE_WITHOUT_EXTENSION=`echo  $f | sed 's/bmp\///' | sed 's/.bin//'`
	mv $f $FILE_WITHOUT_EXTENSION
done

for f in `ls *.img`
do
	echo "Processing file $f ..."
	FILE_WITHOUT_EXTENSION=`echo  $f | sed 's/bmp\///' | sed 's/.img//'`
	cp mypal.pal $FILE_WITHOUT_EXTENSION.pal
done

rm mypal.pal
mv *.img bitmap8
mv *.pal bitmap8
