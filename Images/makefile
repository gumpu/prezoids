#
#
svg_files = $(wildcard *.svg)
bmp_files = $(svg_files:.svg=.bmp)
png_files = $(svg_files:.svg=.png)

%.png : %.svg
	inkscape --export-background=white --export-png=$@ $<

%.bmp : %.png
	convert $< $@

all : $(png_files) $(bmp_files)
	echo "done"

clean :
	-rm -f $(png_files)
	-rm -f $(bmp_files)

