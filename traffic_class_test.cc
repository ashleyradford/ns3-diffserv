#include "traffic_class.h"

// int
// main (int argc, char *argv[])
// {
//     // create UDP packet
//     Ptr<Packet> udp_packet = Create<Packet>();
//     UdpHeader udpHeader;
//     udpHeader.SetSourcePort(4000);
//     udpHeader.SetDestinationPort(5000);
//     udp_packet->AddHeader(udpHeader);
//     Ipv4Header ipHeader;
//     ipHeader.SetProtocol(17);
//     ipHeader.SetSource(Ipv4Address("10.0.0.1"));
//     ipHeader.SetDestination(Ipv4Address("10.0.0.2"));
//     udp_packet->AddHeader(ipHeader);
//     PppHeader pppHeader;
//     udp_packet->AddHeader(pppHeader);

//     // create some filter elements
//     SrcPortNumber udpSrcPort(4000);
//     SrcIPAddress srcIP1(Ipv4Address("10.0.0.0"));
//     DstIPAddress dstIP(Ipv4Address("10.0.0.2"));

//     // add filter elements to the filter, match
//     Filter filter1, filter2;
//     filter1.AddElement(&udpSrcPort);
//     filter1.AddElement(&srcIP1);
//     filter2.AddElement(&dstIP);

//     // create Traffic Class
//     TrafficClass trafficClass;
//     trafficClass.SetMaxPackets(1);
//     trafficClass.SetWeight(10.0);
//     trafficClass.SetPriorityLevel(1);
//     trafficClass.SetDefault(1);

//     // check Traffic Class filters
//     bool matched = trafficClass.match(udp_packet);
//     std::cout << "Packet matched (no filters): " << matched << std::endl;

//     // add filter to Traffic Class and check
//     trafficClass.AddFilter(&filter1);
//     matched = trafficClass.match(udp_packet);
//     std::cout << "Packet not matched: " << matched << std::endl;
//     trafficClass.AddFilter(&filter2);
//     matched = trafficClass.match(udp_packet);
//     std::cout << "Packet matched: " << matched << std::endl;

//     // add packets to Traffic Class
//     bool added = trafficClass.Enqueue(udp_packet);
//     std::cout << "Packet addded: " << added << std::endl;
//     added = trafficClass.Enqueue(udp_packet);
//     std::cout << "Packet not addded: " << added << std::endl;

//     // dequeue packets from Traffic Class
//     Ptr<Packet> p = trafficClass.Dequeue();
//     p = trafficClass.Dequeue();
//     Ptr<Packet const> p_const = trafficClass.Peek();

//     // now add back 1 packet
//     added = trafficClass.Enqueue(udp_packet);
//     std::cout << "Packet addded: " << added << std::endl;
//     p_const = trafficClass.Peek();
//     std::cout << p_const << std::endl;

//     // peek should not remove, so we should not be able to add
//     added = trafficClass.Enqueue(udp_packet);
//     std::cout << "Packet not addded: " << added << std::endl;

//     std::cout << "Get priority level: " << trafficClass.GetPriorityLevel() << std::endl;
// }
