CC=g++
CFLAGS=-std=c++11 -Wall -pthread

KNN_SERVER_SRCS=Distances/Canberra.cpp Classify/TrainCatalog.cpp Distances/Chebyshev.cpp Classify/Database.cpp Distances/Distance.cpp Distances/Euclidean.cpp Server/Server.cpp Distances/Manhattan.cpp Distances/Minkowski.cpp Classify/ClassificationLogic.cpp Commands/Command.cpp IOs/DefaultIO.cpp Commands/DisplayResultsCommand.cpp Commands/DownloadResultsCommand.cpp Commands/ExitCommand.cpp Commands/ClassifyDataCommand.cpp Commands/SettingsCommand.cpp Commands/UploadDataCommand.cpp IOs/StandardIO.cpp IOs/SocketIO.cpp Classify/TestCatalog.cpp Classify/Catalog.cpp IOs/CLI.cpp Server/ClientHandler.cpp

KNN_SERVER_OBJS=$(KNN_SERVER_SRCS:.cpp=.o)

KNN_SERVER_OUT=server.out

CLIENT_SRCS=Client/Client.cpp IOs/DefaultIO.cpp IOs/StandardIO.cpp IOs/SocketIO.cpp

CLIENT_OBJS=$(CLIENT_SRCS:.cpp=.o)

CLIENT_OUT=client.out

all: knn_server client

knn_server: $(KNN_SERVER_OBJS)
	$(CC) $(CFLAGS) -o $(KNN_SERVER_OUT) $(KNN_SERVER_OBJS)

client: $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $(CLIENT_OUT) $(CLIENT_OBJS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(KNN_SERVER_OBJS) $(CLIENT_OBJS) $(KNN_SERVER_OUT) $(CLIENT_OUT)

