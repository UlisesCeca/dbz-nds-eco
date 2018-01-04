#!/bin/bash


rm bitmap8/*.img
rm bitmap8/*.pal


wine grit.exe bmp/*.bmp -gb -gu8 -gB8 -pu8 -ftb -fh! -gTFF00FF

for f in `ls *.bin`
do
	echo "Processing file $f ..."
	FILE_WITHOUT_EXTENSION=`echo  $f | sed 's/bmp\///' | sed 's/.bin//'`
	mv $f $FILE_WITHOUT_EXTENSION
done
mv *.img bitmap8
mv *.pal bitmap8
