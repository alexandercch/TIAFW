all: game.out

game.out: main.cpp TextureManager.cpp
	g++ main.cpp TextureManager.cpp -o game.out -lGL -lglut -lfreeimage

clean:
	rm -rf game.out
