CC = g++
CFLAGS = -O4 -std=c++14
LFLAGS = -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -pthread

clean:
	rm -f ConnectFour.exe ConnectFour *.gch
all:
	$(CC) $(CFLAGS) *.h *.cpp -o ConnectFour $(LFLAGS) 