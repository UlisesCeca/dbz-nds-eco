#!/bin/bash

rm fonts\*.img
rm fonts\*.map
rm fonts\*.pal
rm h\*.h

wine grit.old.exe bmp/*.bmp -g -gTFF00FF -mR! -p -ftb

for f in `ls *.bin`
do
	echo "Processing file $f ..."
	FILE_WITHOUT_EXTENSION=`echo  $f | sed 's/bmp\///' | sed 's/.bin//'`
	mv $f $FILE_WITHOUT_EXTENSION
done

mv *.img *.fnt
mv *.fnt fonts
mv *.pal fonts
rm *.map
mv *.h h
