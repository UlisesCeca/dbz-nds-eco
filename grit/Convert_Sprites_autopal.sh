#!/bin/bash


rm sprites\*.img
rm sprites\*.map
rm sprites\*.pal
rm h\*.h

wine grit.exe bmp/*.bmp -g -gTFF00FF -p -ftb

for f in `ls *.bin`
do
	echo "Processing file $f ..."
	FILE_WITHOUT_EXTENSION=`echo  $f | sed 's/bmp\///' | sed 's/.bin//'`
	mv $f $FILE_WITHOUT_EXTENSION
done
mv *.img sprites
mv *.pal sprites
rm *.map
mv *.h h
