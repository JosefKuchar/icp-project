.PHONY: build run clean doxygen pack

build:
	mkdir -p src/build
	cd src/build && qmake .. && make -j 8
	cp src/build/icpacman .

all: build doxygen

run: build
	./icpacman

clean:
	rm -rf src/build doc xkucha28-xsirov00.zip build-* icpacman

doxygen:
	doxygen Doxyfile

pack: clean
	mkdir -p doc
	zip -r xkucha28-xsirov00.zip Makefile Doxyfile README.* src examples doc
