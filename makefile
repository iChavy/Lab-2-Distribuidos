run: gridding
	./gridding -i hltau_completo_uv.csv -o datosgrideados -d 0,003 -N 2048 -c 10 -t 10
	

gridding: gridding_copy.cc corrutina.o tarea.o tarea_local.o matriz.o
	u++ -o gridding gridding_copy.cc corrutina.o tarea.o tarea_local.o matriz.o

corrutina.o: corrutina.cc corrutina.h
	u++ -c corrutina.cc

tarea.o: tarea.cc tarea.h corrutina.o matriz.o
	u++ -c tarea.cc corrutina.o matriz.o

tarea_local.o: tarea_local.cc tarea_local.h corrutina.o
	u++ -c tarea_local.cc corrutina.o

matriz.o: matriz.cc matriz.h
	u++ -c matriz.cc


clean:
	rm -f *.raw *.o *.exe