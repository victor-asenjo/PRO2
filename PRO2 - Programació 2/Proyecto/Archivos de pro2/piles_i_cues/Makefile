OPCIONS = -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11
#
# si se compila desde el linux de la FIB conviene usar g++-5 en lugar de g++
#
pert_queue.exe: pert_queue.o queueIOint.o
	g++ -o pert_queue.exe pert_queue.o queueIOint.o
#
pert_queue.o: pert_queue.cc queueIOint.hh
	g++ -c pert_queue.cc -I$(INCLUSIONS) $(OPCIONS) 
#
queueIOint.o: queueIOint.cc queueIOint.hh
	g++ -c queueIOint.cc -I$(INCLUSIONS) $(OPCIONS) 
#
tar: pert_queue.cc queueIOint.cc queueIOint.hh
	tar cvf sol.tar pert_queue.cc queueIOint.cc queueIOint.hh
#
clean:
	rm -f *.o
	rm -f *.exe
