#!/bin/bash


rm backgrounds/*.img
rm backgrounds/*.map
rm backgrounds/*.pal
rm h/*.h

wine grit.exe bmp/*.bmp -g -gTFF00FF -m -mRtf -mLs -p -ftb

for f in `ls *.bin`
do
	echo "Processing file $f ..."
	FILE_WITHOUT_EXTENSION=`echo  $f | sed 's/bmp\///' | sed 's/.bin//'`
	mv $f $FILE_WITHOUT_EXTENSION
done
mv *.img backgrounds
mv *.map backgrounds
mv *.pal backgrounds
mv *.h h
