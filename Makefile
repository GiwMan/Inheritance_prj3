CXX= g++

CXXFLAGS = -Wall -g

main: test_main.o \
      PlaneApp.o \
      Object.o
$(CXX) $(CXXFLAGS) -o main \
test_main.o Object.o PlaneApp.o

PlaneApp.o : PlaneApp.h Object.h

Object.o : Object.h 

clean:
	$(RM) main *.o