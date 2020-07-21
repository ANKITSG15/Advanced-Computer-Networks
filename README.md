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


*****************************************************************************************************************************************
Implementation details Submitted -

1. We have to put the all the mentioned command line arguement in the given order :- 
a) Server_IP_Addres b) Server_Port_Address c) File_Name d) Packet_size(in bytes) e) Window Size

2. Input file (File_Name) must be in the same folder where the source code(client.c) is present.

3. Server port address(8888) is harded coded using #define. 

4. Server buffer(5000bytes) is also hard coded using #define.

5. Assuming Packet size = Payload.

6. Packetisation:- Packet is structured in the following manner:- 
				   SeqNo|PktSize|IsLast|PktType|Payload(Data)
whereas Seqence Number field is 4 bytes long, Packet Size field is 4 bytes long, IsLast field is 2 bytes long(1 byte for delimiter),
Packet Type field is 2 bytes long(1 byte ford delimiter), Payload field is as per the input packet size and 2 bytes long is delimiter.

7. Both sequence number and Packet size can not be more than 9999 bytes.

8. Output file(output.txt) is the file where the data is written must be placed along with server.c code.  





