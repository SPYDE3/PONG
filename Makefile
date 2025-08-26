all:compile run 
compile:
	g++ Ball.cpp Bat.cpp Pong.cpp -lsfml-graphics -lsfml-window -lsfml-system
run:
	./a.out

clean:
	rm -f timber.o timber
