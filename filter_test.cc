#include "filter.h"

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
//     SrcIPAddress srcIP1(Ipv4Address("10.0.1.1"));
//     SrcIPAddress srcIP2(Ipv4Address("10.0.0.1"));

//     // add filter elements to the filter, not a match
//     Filter filter1;
//     filter1.AddElement(&udpSrcPort);
//     filter1.AddElement(&srcIP1);
//     bool isMatch = filter1.match(udp_packet);
//     std::cout << "Filter test no match: " << isMatch << std::endl;

//     // add filter elements to the filter, match
//     Filter filter2;
//     filter2.AddElement(&udpSrcPort);
//     filter2.AddElement(&srcIP2);
//     isMatch = filter2.match(udp_packet);
//     std::cout << "Filter test match: " << isMatch << std::endl;
// }
