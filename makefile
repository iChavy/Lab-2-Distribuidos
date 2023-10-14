run: gridding
	./gridding -i prueba100.csv -o datosgrideados -d 0.5 -N 512 -c 10 -t 10
	
gridding: gridding.cc tarea.cc corrutina.cc
	u++ -o gridding gridding.cc



clean:
	rm -f gridding