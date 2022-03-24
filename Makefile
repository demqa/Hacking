##
# Hacking
#

CC     = g++
CFLAGS = -c

all:  hack

hack: hack.o
	$(CC) Obj/hack.o -lsfml-window -lsfml-graphics -lsfml-system -o hack

hack.o: Src/hack.cpp
	$(CC) $(CFLAGS) Src/hack.cpp -o Obj/hack.o

# end
