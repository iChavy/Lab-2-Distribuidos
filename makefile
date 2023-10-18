run: gridding
	./gridding -i hltau_completo_uv.csv -o datosgrideados -d 0,003 -N 2048 -c 10 -t 10
	
gridding: gridding.cc tarea.cc corrutina.cc tarea_local.cc
	u++ -o gridding gridding.cc

clean:
	rm -f gridding