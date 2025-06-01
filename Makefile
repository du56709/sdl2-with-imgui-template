CC =  gcc
CXX = g++

src/poly.o: src/poly.cpp
	$(CXX) -c -I./include/ -o $@ $< $(CFLAGS)

clean:
	$(RM) src/*.o

