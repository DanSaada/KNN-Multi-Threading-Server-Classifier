all: server client

SERVER_SRCS = $(wildcard Commands/*.cpp Distances/*.cpp Server/*.cpp IOs/*.cpp Classify/*.cpp)
SERVER_OBJS = $(SERVER_SRCS:.cpp=.o)
CLIENT_SRCS = $(wildcard Client/*.cpp IOs/*.cpp)
CLIENT_OBJS = $(CLIENT_SRCS:.cpp=.o)

$(SERVER_OBJS): %.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(CLIENT_OBJS): %.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

server: $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $(SERVER_OUT) $(SERVER_OBJS)

client: $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $(CLIENT_OUT) $(CLIENT_OBJS)

clean:
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS) $(SERVER_OUT) $(CLIENT_OUT)


#server: %.o : Commands/%.cpp Commands/%.h Distances/%.cpp Distances/%.h Server/%.cpp Server/%.h IOs/%.cpp IOs/%.h Classify/%.cpp Classify/%.h
#	g++ -std=c++11 -Wall -o server.out
#
#client: Client.o
#	g++ -std=c++11 -Wall -o client.out Client.o
#
#Client.o: Client.cpp
#	g++ -std=c++11 -Wall -c Client.cpp
#
#Server.o: Server/Server.cpp
#	g++ -std=c++11 -Wall -c Server.cpp
#
#classificationLogic.o: Classify/ClassificationLogic.cpp
#	g++ -std=c++11 -Wall -c classificationLogic.cpp
#
#Distance.o: Distances/Distance.cpp
#	g++ -std=c++11 -Wall -c Distance.cpp
#
#Canberra.o: Distances/Canberra.cpp
#	g++ -std=c++11 -Wall -c Canberra.cpp
#
#Catalog.o: Classify/TrainCatalog.cpp
#	g++ -std=c++11 -Wall -c Catalog.cpp
#
#Chebyshev.o: Distances/Chebyshev.cpp
#	g++ -std=c++11 -Wall -c Chebyshev.cpp
#
#Database.o: Classify/Database.cpp
#	g++ -std=c++11 -Wall -c Database.cpp
#
#Euclidean.o: Distances/Euclidean.cpp
#	g++ -std=c++11 -Wall -c Euclidean.cpp
#
#Manhattan.o: Distances/Manhattan.cpp
#	g++ -std=c++11 -Wall -c Manhattan.cpp
#
#Minkowski.o: Distances/Minkowski.cpp
#	g++ -std=c++11 -Wall -c Minkowski.cpp
#
#clean:
#	rm -f *.o server.out client.out

