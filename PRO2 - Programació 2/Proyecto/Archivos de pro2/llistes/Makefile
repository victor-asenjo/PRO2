OPCIONS = -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11
#
# si se compila desde el linux de la FIB conviene usar g++-5 en lugar de g++
#
pert_list_int.exe: pert_list_int.o listIOint.o
	g++ -o pert_list_int.exe pert_list_int.o listIOint.o
#
pert_list_int.o: pert_list_int.cc listIOint.hh
	g++ -c pert_list_int.cc -I$(INCLUSIONS) $(OPCIONS) 
#
listIOint.o: listIOint.cc listIOint.hh
	g++ -c listIOint.cc -I$(INCLUSIONS) $(OPCIONS) 
#
tar: pert_list_int.cc listIOint.cc listIOint.hh
	tar cvf sol.tar pert_list_int.cc listIOint.cc listIOint.hh
#
clean:
	rm -f *.o
	rm -f *.exe
