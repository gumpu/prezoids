%.png : %.svg
	inkscape --export-background-opacity=0 --export-png=$@ $<

dist_pkgdata_DATA=spritesheet1.png background1.png

all-local: $(dist_pkgdata_DATA)

