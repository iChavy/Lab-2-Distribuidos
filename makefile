gridding: gridding.cc corrutina.o tarea.o tarea_local.o matriz.o
	u++ -o gridding gridding.cc corrutina.o tarea.o tarea_local.o matriz.o

tarea.o: tarea.cc tarea.h 
	u++ -c tarea.cc 

tarea_local.o: tarea_local.cc tarea_local.h 
	u++ -c tarea_local.cc 

corrutina.o: corrutina.cc corrutina.h
	u++ -c corrutina.cc
	
matriz.o: matriz.cc matriz.h
	u++ -c matriz.cc

clean:
	rm -f *.raw *.o gridding