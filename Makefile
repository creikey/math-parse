.PHONY: clean

all: *.o
	g++ *.o

%.o: %.cpp
	g++ -c $(CXXFLAGS) $^

clean:
	-rm *.o
	-rm *.gch
	-rm a.out
