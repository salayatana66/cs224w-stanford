#
# Makefile for non-Microsoft compilers
#	tested only on Linux

include Makefile.config

## Main application file

all: q1.o q2.o

# COMPILE
q1.o: q1.cpp $(CSNAP)/Snap.o
	$(CC) $(CXXFLAGS) -o q1.o q1.cpp $(CSNAP)/Snap.o -I$(CSNAP) -I$(CGLIB) $(LDFLAGS) $(LIBS)

q2.o: q2.cpp $(CSNAP)/Snap.o
	$(CC) $(CXXFLAGS) -o q2.o q2.cpp $(CSNAP)/Snap.o -I$(CSNAP) -I$(CGLIB) $(LDFLAGS) $(LIBS)

q3.o: q3.cpp $(CSNAP)/Snap.o
	$(CC) $(CXXFLAGS) -o q3.o q3.cpp $(CSNAP)/Snap.o -I$(CSNAP) -I$(CGLIB) $(LDFLAGS) $(LIBS)


$(CSNAP)/Snap.o:
	$(MAKE) -C $(CSNAP)

clean:
	rm -f *.o $(DEMOS) *.exe
	rm -rf Debug Release
	rm -rf *.Err demo*.dat

