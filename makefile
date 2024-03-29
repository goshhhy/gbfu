default: all

all: build/gb flashutil.gb

build/gb:
	mkdir -p build/gb

build/gb/%.o: src/%.sm83 build/gb/tilemap.2bpp
	rgbasm -i src/ -i build/gb -o $@ $<

build/gb/%.2bpp: assets/%.png
	rgbgfx -o $@ $<

build/gb/bootcart.out: build/gb/bootcart.o
	rgblink -dto $@ $^
	truncate -s 4096 $@ 

build/gb/dumpcart.out: build/gb/dumpcart.o
	rgblink -dto $@ $^
	truncate -s 4096 $@ 

build/gb/flashutil.out: build/gb/dumpcart.out build/gb/main.o
	rgblink -dto $@ build/gb/main.o

flashutil.gb: build/gb/flashutil.out
	cp $< $@
	rgbfix -f lhg -i GBFU -j -k FU -m 0 -n 0 -r 0 -t "FLASH UTIL" $@

clean:
	rm -rf build/gb
	rm flashutil.gb