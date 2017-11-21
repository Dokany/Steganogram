# Steganogram
Image sharing application build using UNIX sockets and UDP to implement Remote Invocation Middleware (RMI) and grant its users capabilties to control their images' sharing privileges.

#### Contributors (Group D)
- Aley Baracat
- Sara Seleem
- John Sourour
- Yasmin ElDokany

#### To compile:
g++ -std=c++11 -pthread -Wno-write-strings Peer.h Peer.cpp Message.h Message.cpp AckData.h AckData.cpp AuthData.h AuthData.cpp ImageListData.h ImageListData.cpp StatusData.h StatusData.cpp ImageRequestData.h ImageRequestData.cpp ImageData.h ImageData.cpp Data.h Data.cpp UDPSocket.h UDPSocket.cpp main_test.cpp PackGen.h PackGen.cpp -o o


##### This project is supervised by Prof. Amr El-Kadi under the CSCE 445/4411 course.
