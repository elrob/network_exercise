network: network_target message_target router_target host_target
	g++ -g robs_network.o message.o router.o host.o -o network

network_target: robs_networkMain.cpp message.h router.h host.h 
	g++ -c -g robs_networkMain.cpp -o robs_network.o

router_target: router.cpp router.h message.h host.h
	g++ -c -g router.cpp

host_target: host.cpp host.h router.h message.h
	g++ -c -g host.cpp

message_target: message.cpp message.h
	g++ -c -g message.cpp

clean:
	rm -rf *.o network
