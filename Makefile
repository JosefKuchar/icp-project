.PHONY: build run clean doxygen pack

build:
	mkdir -p build
	cd build && qmake ../src && make -j 16
	cp build/icpacman .

all: build doxygen

run: build
	./icpacman

clean:
	rm -rf build doc xkucha28-xsirov00.zip build-* icpacman

doxygen:
	doxygen Doxyfile

pack: clean
	mkdir -p doc
	zip -rX9 xkucha28-xsirov00.zip Makefile Doxyfile README.* src examples doc
