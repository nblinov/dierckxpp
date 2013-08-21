F77=gfortran
CXX=g++
SRCDIR=dierckx
CXXFLAGS = -O3 -pedantic-errors -Wimplicit -Wparentheses -Wreturn-type -Wcast-qual -Wall -Wpointer-arith -Wwrite-strings -Wconversion 
.f.o:
	$(F77) -c -o  $@ $<
example: example.cpp $(SRCDIR)/curfit.o $(SRCDIR)/splev.o $(SRCDIR)/fpback.o $(SRCDIR)/fpbspl.o $(SRCDIR)/fpchec.o $(SRCDIR)/fpcurf.o $(SRCDIR)/fpdisc.o $(SRCDIR)/fpgivs.o $(SRCDIR)/fpknot.o $(SRCDIR)/fprati.o $(SRCDIR)/fprota.o
	$(CXX) $(CXXFLAGS) -o $@ $^ -lgfortran
clean:
	rm -rf *.o ../*.o example
