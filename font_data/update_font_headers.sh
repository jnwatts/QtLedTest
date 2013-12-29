#!/bin/sh

rm -f *.c *.h
for f in *.xml; do
	f=${f%.*}
	FontImageToHeaders ${f}
	[ -f "${f}.PNG" ] && mv "${f}.PNG" "${f}.png"
done
