program: driver.o graph.o graph_interface.o
	g++ -std=c++11 -o program driver.o graph.o graph_interface.o


main.o: driver.cpp graph_interface.h graph.h
	g++ -std=c++11 -c driver.cpp



Console.o: graph.h graph.cpp graph_interface.h
	g++ -std=c++11 -c graph.cpp

clean:
	rm program *.o