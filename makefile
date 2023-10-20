run: gridding
	./gridding -i hltau_completo_uv.csv -o datosgrideados -d 0,003 -N 2048 -c 10 -t 10
	
gridding: gridding_copy.cc tarea.cc corrutina.cc tarea_local.cc matriz.cc
	u++ -o gridding gridding_copy.cc

clean:
	rm -f gridding