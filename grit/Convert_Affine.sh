#!/bin/bash


rm affine/*.img
rm affine/*.map
rm affine/*.pal
rm h/*.h

wine grit.exe bmp/*.bmp -g -gTFF00FF -m -mRtf -mLa -p -pS -ftb -fa -Omypal.pal

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

mv *.img affine
mv *.map affine
mv *.pal affine
mv *.h h
