Problem Statement: Implement a modified Go-Back-N ARQ protocol using UDP sockets.

Learning Objectives: This assignment problem will help you to tune up your programming skills. Particularly, you are going to learn TCP/UDP socket programming concepts using
                      UNIX libraries.
					 
Programming Language to be used: C/C++ (gcc compiler)

Modified Go-Back-N ARQ Protocol Description:

The modified Go-Back-N ARQ would work simply as an extended stop-and-wait ARQ
protocol, where instead of transmitting a single packet and waiting for its acknowledgment,
i.e., ACK, the sender would transmit certain number of packets equal to the size of
window (WS), and then, will wait for WS number of ACKs. On receipt of WS ACKs
against the transmitted packets in a window, the sender can transmit another WS packets.
A base pointer (Base) keeps track of the packet number of the
next packet to be transmitted in the subsequent rounds.


What needs to be done?

You have to implement a client and a server program using DATAGRAM sockets. The
client sends a file (e.g., infile.txt) to the server using the modified Go-Back-N ARQ
protocol. The client breaks the file into equal-sized packets (pkt_size) and transmit to
the server. The packets received at server are first copied into a buffer and then written
to a file. (Note: It is your choice to either write one packet at a time or all the packets
at once to the file.). The packets would reach immediately without fail (you can assume
no packet loss…!!!) to the server as both the programs (server and client) would either
run on the same host machine or in same LAN. Therefore, you can consider to introduce 
a dummy time delay at server before sending ACK packet corresponding to a DATA packet
to get the output in the desired format.

Packet Format: 

You have to use a uniform packet format for data packets and ACK
packets. Typical fields in a packet structure can be are; pkt_type, pkt_length, is_last_pkt,
payload, pkt seq_no .
(Note: you can add more fields based on your implementation.)
The client program should take the server IP address, Server port number, file_name,
pkt_size, and WS as command line arguments. 


Implementation Guidelines:

i) Handle errors/exceptions and program termination in a graceful manner.
ii) Put comments in your code at appropriate places for better readability.
iii) Create a readme file (readme.txt) which contains key implementation details
(e.g., packet format, packetization process, file writing process etc.) and
limitations of your implementation.




