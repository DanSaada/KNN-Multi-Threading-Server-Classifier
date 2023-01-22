# KNN-Multi-Threading-Server-Classifier
A project about vector classification using the KNN algorithm and a multi threading server-client connection.

<!-- TOC -->
- Markdown Navigation
    - [Description](#Description)
    - [Course of the program](#Course-of-the-program)
    - [Dealing with edge cases](#Dealing-with-edge-cases)
    - [Distances](#Distances)
    - [Installing And Executing](#Installing-And-Executing)
    - [Authors](#Authors)
<!-- /TOC -->

## Description

This project implements a TCP Socket connection between a server and multiple clients. The connection between them includes at most reading and transferring files, and sending success and failure messages. The purpose of communication between them is to succeed in classifying different vectors with the help of an algorithm based on a distance metric called the KNN algorithm


<img width="300" alt="image" src="https://user-images.githubusercontent.com/112869076/210267297-323a511d-25c7-42ab-9493-fa0617a78b81.png">


The classification algorithm is implemented with the KNN (k nearest neighbors) algorithm, which is among the most common of machine learning algorithms and is used in a variety of fields.
The algorithm works as follows:
* Calculation of the distance between the input vector and all classified vectors.
* Finding K nearest neighbors.
* Classify the input vector according to the classification of the majority of neighbors (using a provided distance metrics).

<img width="501" alt="image" src="https://user-images.githubusercontent.com/112869076/206932807-d6fa4737-e8ad-40cb-b828-bff296607365.png">


Because this project is a continious one, our implementation derived from a wide 
prespective that Lacks of dependence on implementation, in order to expand the project in the future and leverage it.

We used encapsulation for the distance classes and additionally made distance abstract.
Thanks to this, our KNN calculation function that received an object of type Distance could use any of the distance functions independently of them.
In addition, since in the future we may want to change the internal implementation of the vector classification or add additional attributes to it, we implemented the relationship between the client and the server in such a way that does not create a dependency between the implementation of the classification algorithm and the communication process between them.

While planning the task and out of an ambition to improve the running time, we noticed that we don't need to sort the entire database, but it is enough for us to find the K members whose distance is the smallest from the newly inserted vector, and therefore we chose to use the Select algorithm which has an average time complexity of O(n).

We used the Command design pattern, where each command in our software has its own class. The command class can define everything that is relevant to all our system commands, and in particular a command to execute abstractly activation.
In order to disconnect the dependency between the command and the input/output source, (After all, we don't necessarily want to print to the screen standard output or read from the keyboard standard input) we defined the abstract type DefaultIO, whose successors will have to implement the read and write methods, that can proccess the source in various implementations. For Example if we want the standard input-output then we will enter StandardIO, where as if we want to create communication in a socket type then we will use SocketIO.

<img width="465" alt="image" src="https://user-images.githubusercontent.com/112869076/213036773-1993684a-f380-4e6c-84d4-69651b847df2.png">

Because we considered each connection between the server and the different clients as a separate task, we used task parallelism by multi threading those connections. That is, at a given moment, our server can communicate with several different clients at the same time, which means each client-server connection is handled by a separate thread. We also used the thread pull design pattern, which is basically a way to manage a large number of threads efficiently by reusing a fixed number of threads from a pool, rather than creating a new thread for each task. We took an advantage over this method by creating a priority queue which controls at the amount of requests from the clients to connect with the server, using a unique lock and mutex. That is, when a connection is made we check if there is a room in the queue, and add clients to the queue, from then we pop the front client from the queue and handle his requests on a thread that is available for work.
Another place where this ability is manifested is for example in option 5 in the menu, while downloading the classifications of the vectors as a list into a file on the computer, the user can continue asking for other command's execution requests because the action of downloading runs in a different thread.

<img width="343" alt="image" src="https://user-images.githubusercontent.com/112869076/213940913-7d4e43de-c449-4ea4-90fa-324a0554722e.png">


## Course of the program

First, the server is being initialize, then clients can connect to the server (the number of clients dependes on how much clients the server can handle in hold, in our program can handle 5 clients by default).

Each client is being presented with a menu with various commands which includes:
1. Upload an unclassified csv data file
2. Algorithm settings
3. Classifiy data
4. Display results
5. Download results
8. Exit

As can be understood from the menu, by pressing 1 the user can upload a "Train" file which will contain several vectors with their classifications, and a "Test" file which will contain only vectors (without their classification), then by pressing 3 the vectors from the "Test" file will be classified in accordance to the vectors in the "Train" file (using the KNN algorithm). The user then can press 4 for displaying the results on the screen, or 5 for downloading them into a local file to his choice on his computer. In addition, the user can change the algorithm settings by pressing 2, this will allow him to change the K (number of neighbors to acount in the KNN calculation) and the metric distance. Each client can end the communication with the server by pressing 8.

## Dealing with edge cases

- When a customer writes a number that is not between the options or any sign that is not a number, invalid input will be printed to the screen
- When the client requests to classify the vectors or display them or upload them to an external file (options 3,4,5) before uploading unclassified and classified vectors the server will send a message and ask him to first perform task 1
- When a client requests tasks 4,5 before performing task 3, i.e. classifying the vectors, the server will print a request from the client to sort the vectors first
- In task 2, the customer can request to replace the distance metric, and the k
But if one of them registered illegally, for example a negative number or a metric that is not one of the 5 options, the server will return an appropriate error message and will not change the metric and the k
- In tasks 1,5, the client is required to enter a path to the files on his computer, if he registers an invalid path, the server will return an error and reprint the menu on the client's screen
- The server classifies the trained and test vectors according to the length of the first vector entered into the trained catalog
- We have created a manual protocol for sending and reading messages from a socket, that is, so that the sender can inform the receiving party of the end of a message that he must send at the end "$$$", this is the sign we chose for the end of sending a message.
- Sometimes to inform about an error we used additional signs in the message for example "#" but in any case we sent "$$$" at the end of the message
- In cases where the client was unable to connect to the server's port or IP, we will exit directly from the client's program.
- When using the write function in SocketIO we added a unique lock with a mutex, this way, when multiple threads are trying to access the function at the same time, only one thread will be able to execute the function at a time and the others will wait until the lock is released, what will prevent a situation of merging of data when communicating via the socket.

## Distances

* <a href="https://en.wikipedia.org/wiki/Euclidean_distance">Euclidean distance<a name="">

  <img width="137" alt="image" src="https://user-images.githubusercontent.com/112869076/201759198-da035808-d982-4b36-bc8c-a475d4bb8d48.png">

* <a href="https://en.wikipedia.org/wiki/Taxicab_geometry">Manhattan distance<a name="">

  <img width="117" alt="image" src="https://user-images.githubusercontent.com/112869076/201761310-950f98b8-851c-4e92-b8ec-8c58fe2432d7.png">

  
* <a href="https://en.wikipedia.org/wiki/Chebyshev_distance">Chebyshev distance<a name="">

  <img width="130" alt="image" src="https://user-images.githubusercontent.com/112869076/201761602-326e2be1-445d-47cb-85d3-a339f4257951.png">

  
* <a href="https://en.wikipedia.org/wiki/Canberra_distance">Canberra_distance<a name="">

  <img width="107" alt="image" src="https://user-images.githubusercontent.com/112869076/201761855-d768aa00-8525-452d-b4d0-b5a285eb2866.png">

  
* <a href="https://en.wikipedia.org/wiki/Minkowski_distance">Minkowski distance<a name="">

  <img width="173" alt="image" src="https://user-images.githubusercontent.com/112869076/201762252-08b6bad3-ce25-442d-b172-f130fd42c5e5.png">


## Installing And Executing
    
To clone and run this application, you'll need [Git](https://git-scm.com) installed on your computer.
  
From your command line:

  
```bash
# Clone this repository.
$ git clone https://github.com/DanSaada/KNN-Multi-Threading-Server-Classifier

# Go into the repository.
$ cd KNN-Multi-Threading-Server-Classifier

# Compile using makefile.
$ make
```

```bash
# Run the program on Linux:
$ ./server.out port
$ ./client.out ip port
```

```bash
# Run the program on Windows:
$ server.out port
$ client.out ip port
```

  
## Authors
- [Dan Saada](https://github.com/DanSaada)
- [Tomer Peisikov](https://github.com/tomerp1812)

