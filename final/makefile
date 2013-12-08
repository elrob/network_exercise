network: network_target router_target host_target message_target
	g++ -g network.o message.o router.o host.o -o network

network_target: networkMain.cpp message.h router.h host.h 
	g++ -c -g networkMain.cpp -o network.o

router_target: router.cpp router.h message.h host.h
	g++ -c -g router.cpp

host_target: host.cpp host.h router.h message.h
	g++ -c -g host.cpp

message_target: message.cpp message.h
	g++ -c -g message.cpp

clean:
	rm -rf *.o network
