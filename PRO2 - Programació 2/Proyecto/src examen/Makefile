OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG  -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11

program.exe: program.o Especie.o Cjt_especies.o Cluster.o Cjt_clusters.o
	g++ -o program.exe program.o Especie.o Cjt_especies.o Cluster.o Cjt_clusters.o

Especie.o: Especie.cc Especie.hh 
	g++ -c -o $@ $< $(OPCIONS)

Cjt_especies.o: Cjt_especies.cc Cjt_especies.hh Especie.hh 
	g++ -c -o $@ $< $(OPCIONS)

Cluster.o: Cluster.cc Cluster.hh
	g++ -c -o $@ $< $(OPCIONS)

Cjt_clusters.o: Cjt_clusters.cc Cjt_clusters.hh Cluster.hh 
	g++ -c -o $@ $< $(OPCIONS)

program.o: program.cc Cjt_especies.hh Especie.hh
	g++ -c -o $@ $< $(OPCIONS)

practica.tar: Especie.cc Especie.hh Cluster.cc Cluster.hh Cjt_clusters.cc Cjt_clusters.hh program.cc
	tar -cvf practica.tar *.cc *.hh Makefile

clean:
	rm *.o
	rm *.exe

nowarnings:
	g++ -o program.exe *.cc -std=c++11

debug:
	g++ -o program.exe *.cc $(OPCIONS)

test:
	make
	./program.exe <sample.inp> z.out
	kompare z.out sample.cor
