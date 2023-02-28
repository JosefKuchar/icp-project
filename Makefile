build:
	mkdir -p src/build
	cd src/build && qmake .. && make

run: build
	./src/build/icpacman

clean:
	rm -rf src/build
