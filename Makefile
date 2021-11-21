image: a.out
	./a.out > image.ppm

a.out: main.cpp
	g++ main.cpp

clean:
	rm a.out image.ppm