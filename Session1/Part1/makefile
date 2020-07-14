classical:	practice1.cpp Affine.o Vigenere.o
			g++ practice1.cpp Affine.o Vigenere.o -o classical
Affine.o:	Affine.cpp Affine.h
			g++ -c Affine.cpp
Vigenere.o:	Vigenere.cpp Vigenere.h
			g++ -c Vigenere.cpp
clean:
			rm -f *.o classical
