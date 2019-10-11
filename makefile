default: all

all: build/gb flashutil.gb

build/gb:
	mkdir -p build/gb

build/gb/%.o: src/%.sm83 build/gb/gb_pocket.2bpp
	rgbasm -i src/ -i build/gb -o $@ $<

build/gb/%.2bpp: assets/%.png
	rgbgfx -o $@ $<

build/gb/flashutil.out: build/gb/main.o
	rgblink -dto $@ $^

flashutil.gb: build/gb/flashutil.out
	cp $< $@
	rgbfix -f lhg -i GBFU -j -k FU -m 0 -n 0 -r 0 -t "FLASH UTIL" $@

clean:
	rm -rf build/gb
	rm flashutil.gb