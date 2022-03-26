##
# Hacking
#

CC     = g++
CFLAGS = -c

all:  hack

hack: main.o hack.o
	$(CC) Obj/main.o Obj/hack.o -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio -lm -o hack

main.o: Src/main.cpp
	$(CC) $(CFLAGS) Src/main.cpp -o Obj/main.o

hack.o: Src/hack.cpp
	$(CC) $(CFLAGS) Src/hack.cpp -o Obj/hack.o

clean:
	rm -rf Obj/*.o hack

# end
