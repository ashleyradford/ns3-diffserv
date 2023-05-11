#include "spq.h"

// int
// main (int argc, char *argv[])
// {
//     // create UDP packets
//     Ptr<Packet> udp_packet1 = Create<Packet>();
//     UdpHeader udpHeader;
//     udpHeader.SetSourcePort(4000);
//     udp_packet1->AddHeader(udpHeader);
//     Ipv4Header ipHeader;
//     ipHeader.SetProtocol(17);
//     ipHeader.SetSource(Ipv4Address("10.0.0.1"));
//     udp_packet1->AddHeader(ipHeader);
//     PppHeader pppHeader;
//     udp_packet1->AddHeader(pppHeader);
//     std::cout << "Packet 1 created " << udp_packet1 << std::endl;

//     Ptr<Packet> udp_packet2 = Create<Packet>();
//     udpHeader.SetSourcePort(4000);
//     udp_packet2->AddHeader(udpHeader);
//     ipHeader.SetProtocol(17);
//     ipHeader.SetSource(Ipv4Address("10.0.0.1"));
//     udp_packet2->AddHeader(ipHeader);
//     udp_packet2->AddHeader(pppHeader);
//     std::cout << "Packet 2 created " << udp_packet2 << std::endl;

//     Ptr<Packet> udp_packet3 = Create<Packet>();
//     udpHeader.SetSourcePort(5000);
//     udp_packet3->AddHeader(udpHeader);
//     ipHeader.SetProtocol(17);
//     ipHeader.SetSource(Ipv4Address("10.0.0.1"));
//     udp_packet3->AddHeader(ipHeader);
//     udp_packet3->AddHeader(pppHeader);
//     std::cout << "Packet 3 created " << udp_packet3 << std::endl;

//     Ptr<Packet> udp_packet4 = Create<Packet>();
//     udpHeader.SetSourcePort(5000);
//     udp_packet4->AddHeader(udpHeader);
//     ipHeader.SetProtocol(17);
//     ipHeader.SetSource(Ipv4Address("10.0.0.1"));
//     udp_packet4->AddHeader(ipHeader);
//     udp_packet4->AddHeader(pppHeader);
//     std::cout << "Packet 4 created " << udp_packet4 << std::endl;

//     Ptr<Packet> udp_packet5 = Create<Packet>();
//     udpHeader.SetSourcePort(6000);
//     udp_packet5->AddHeader(udpHeader);
//     ipHeader.SetProtocol(17);
//     ipHeader.SetSource(Ipv4Address("10.0.0.1"));
//     udp_packet5->AddHeader(ipHeader);
//     udp_packet5->AddHeader(pppHeader);
//     std::cout << "Packet 5 created " << udp_packet5 << std::endl;

//     // create Filter Elements
//     SrcPortNumber fe1(4000);
//     SrcPortNumber fe2(5000);

//     // create filters
//     Filter f1, f2;
//     f1.AddElement(&fe1);
//     f2.AddElement(&fe2);

//     // create Traffic Class 1
//     TrafficClass trafficClass1;
//     trafficClass1.SetMaxPackets(5);
//     trafficClass1.SetPriorityLevel(1);
//     trafficClass1.SetDefault(0);
//     trafficClass1.AddFilter(&f1);

//     // create Traffic Class 2
//     TrafficClass trafficClass2;
//     trafficClass2.SetMaxPackets(5);
//     trafficClass2.SetPriorityLevel(3);
//     trafficClass2.SetDefault(1);
//     trafficClass2.AddFilter(&f2);

//     // create SPQ class
//     SPQ spq;

//     // no queues
//     std::cout << "Trying to dequeue before queues added:" << std::endl;
//     spq.Dequeue(); // try to dequeue

//     // empty queues
//     spq.AddQueue(&trafficClass1);
//     spq.AddQueue(&trafficClass2);
//     std::cout << "Trying to dequeue from empty queues:" << std::endl;
//     spq.Dequeue(); // try to dequeue
    
//     // dequeue packet from default filter
//     spq.Enqueue(udp_packet5);
//     std::cout << "Dequeueing default packet." << std::endl;
//     Ptr<Packet> dequeued_p = spq.Dequeue();
//     std::cout << dequeued_p << std::endl;

//     // dequeue empty queues
//     std::cout << "Default packet should be removed:" << std::endl;
//     dequeued_p = spq.Dequeue();

//     // enqueue 4 packets
//     spq.Enqueue(udp_packet4);
//     spq.Enqueue(udp_packet3);
//     spq.Enqueue(udp_packet1);
//     spq.Enqueue(udp_packet2);

//     Ptr<const Packet> peeked = spq.Peek();
//     std::cout << "Peeking a packet: " << peeked << std::endl;

//     dequeued_p = spq.Dequeue();
//     std::cout << dequeued_p << std::endl;
//     dequeued_p = spq.Dequeue();
//     std::cout << dequeued_p << std::endl;
//     dequeued_p = spq.Dequeue();
//     std::cout << dequeued_p << std::endl;
//     dequeued_p = spq.Dequeue();
//     std::cout << dequeued_p << std::endl;

//     // no more packets to dequeue
//     std::cout << "All packets should be dequeued:" << std::endl;
//     dequeued_p = spq.Dequeue();
// }
