#!/bin/bash

rm cmaps/*.cmp
rm h/*.h

wine grit.exe bmp/*.bmp -g -gTFF00FF -m -mRt -mLf -p -ftb

for f in `ls *.bin`
do
	echo "Processing file $f ..."
	FILE_WITHOUT_EXTENSION=`echo  $f | sed 's/bmp\///' | sed 's/.bin//'`
	mv $f $FILE_WITHOUT_EXTENSION
done

for i in *.map;
do
    FILE_WITHOUT_EXTENSION=`echo  $i | sed -e 's/\.map/\.cmp/'`
    echo $i
    mv $i cmaps/$FILE_WITHOUT_EXTENSION
done
for i in *.img;
do
    FILE_WITHOUT_EXTENSION=`echo  $i |  sed -e 's/\.img/\.dat/'`
    echo $i
    mv $i cmaps/$FILE_WITHOUT_EXTENSION
done

rm *.pal
for i in *.h
do
    mv $i h
done