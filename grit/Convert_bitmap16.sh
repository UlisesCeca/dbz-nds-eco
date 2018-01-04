#!/bin/bash

rm bitmap16\*.img

wine grit.exe bmp/*.bmp -gb -gu16 -gB16 -ftb -fh! -gTFF00FF
for f in `ls *.bin`
do
	echo "Processing file $f ..."
	FILE_WITHOUT_EXTENSION=`echo  $f | sed 's/bmp\///' | sed 's/.bin//'`
	mv $f $FILE_WITHOUT_EXTENSION
done

mv *.img bitmap16
