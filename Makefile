build:
	cd src/build && qmake .. && make

run: build
	./src/build/ICP
