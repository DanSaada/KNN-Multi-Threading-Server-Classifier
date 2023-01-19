all: server client

server: Server.o classificationLogic.o Distance.o Canberra.o Catalog.o Chebyshev.o Database.o Euclidean.o Manhattan.o Minkowski.o
	g++ -std=c++11 -Wall -o server.out Server.o classificationLogic.o Distance.o Canberra.o Catalog.o Chebyshev.o Database.o Euclidean.o Manhattan.o Minkowski.o

client: Client.o
	g++ -std=c++11 -Wall -o client.out Client.o

Client.o: Client.cpp
	g++ -std=c++11 -Wall -c Client.cpp

Server.o: Server/Server.cpp
	g++ -std=c++11 -Wall -c Server.cpp

classificationLogic.o: Classify/ClassificationLogic.cpp
	g++ -std=c++11 -Wall -c classificationLogic.cpp

Distance.o: Distances/Distance.cpp
	g++ -std=c++11 -Wall -c Distance.cpp

Canberra.o: Distances/Canberra.cpp
	g++ -std=c++11 -Wall -c Canberra.cpp

Catalog.o: Classify/TrainCatalog.cpp
	g++ -std=c++11 -Wall -c Catalog.cpp

Chebyshev.o: Distances/Chebyshev.cpp
	g++ -std=c++11 -Wall -c Chebyshev.cpp

Database.o: Classify/Database.cpp
	g++ -std=c++11 -Wall -c Database.cpp

Euclidean.o: Distances/Euclidean.cpp
	g++ -std=c++11 -Wall -c Euclidean.cpp

Manhattan.o: Distances/Manhattan.cpp
	g++ -std=c++11 -Wall -c Manhattan.cpp

Minkowski.o: Distances/Minkowski.cpp
	g++ -std=c++11 -Wall -c Minkowski.cpp

clean:
	rm -f *.o server.out client.out

