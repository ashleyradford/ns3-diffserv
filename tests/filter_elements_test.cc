#include "filter_elements.h"

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

//     // create TCP packet
//     Ptr<Packet> tcp_packet = Create<Packet>();
//     TcpHeader tcpHeader;
//     tcpHeader.SetSourcePort(4000);
//     tcpHeader.SetDestinationPort(5000);
//     tcp_packet->AddHeader(tcpHeader);
//     ipHeader.SetProtocol(6);
//     ipHeader.SetSource(Ipv4Address("10.0.0.1"));
//     ipHeader.SetDestination(Ipv4Address("10.0.0.2"));
//     tcp_packet->AddHeader(ipHeader);
//     tcp_packet->AddHeader(pppHeader);

//     bool isMatch0;
//     bool isMatch1;

//     // test source ip address filter - no match
//     SrcIPAddress srcIP0(Ipv4Address("10.0.1.1"));
//     isMatch0 = srcIP0.match(udp_packet);
//     std::cout << "SrcIPAddress Test No Match: " << isMatch0 << std::endl;
//     // test source ip address filter - match
//     SrcIPAddress srcIP1(Ipv4Address("10.0.0.1"));
//     isMatch1 = srcIP1.match(udp_packet);
//     std::cout << "SrcIPAddress Test Match: " << isMatch1 << std::endl;

//     // test source mask filter - no match
//     SrcMask srcMask0(Ipv4Address("10.0.2.2"), Ipv4Mask("255.255.255.0"));
//     isMatch0 = srcMask0.match(udp_packet);
//     std::cout << "SrcMask Test No Match: " << isMatch0 << std::endl;
//     // test source mask filter - match
//     SrcMask srcMask1(Ipv4Address("10.0.0.2"), Ipv4Mask("255.255.255.0"));
//     isMatch1 = srcMask1.match(udp_packet);
//     std::cout << "SrcMask Test Match: " << isMatch1 << std::endl;

//     // test source port filter - no match (UDP)
//     SrcPortNumber udpSrcPort0(2000);
//     isMatch0 = udpSrcPort0.match(udp_packet);
//     std::cout << "UDP SrcPortNumber Test No Match: " << isMatch0 << std::endl;
//     // test source port filter - match (UDP)
//     SrcPortNumber udpSrcPort1(4000);
//     isMatch1 = udpSrcPort1.match(udp_packet);
//     std::cout << "UDP SrcPortNumber Test Match: " << isMatch1 << std::endl;

//     // test source port filter - no match (TCP)
//     SrcPortNumber tcpSrcPort0(2000);
//     isMatch0 = tcpSrcPort0.match(tcp_packet);
//     std::cout << "TCP SrcPortNumber Test No Match: " << isMatch0 << std::endl;
//     // test source port filter - match (TCP)
//     SrcPortNumber tcpSrcPort1(4000);
//     isMatch1 = tcpSrcPort1.match(tcp_packet);
//     std::cout << "TCP SrcPortNumber Test Match: " << isMatch1 << std::endl;

//     // test dest ip address filter - no match
//     DstIPAddress dstIP0(Ipv4Address("10.0.0.3"));
//     isMatch0 = dstIP0.match(udp_packet);
//     std::cout << "DstIPAddress Test No Match: " << isMatch0 << std::endl;
//     // test dest ip address filter - match
//     DstIPAddress dstIP1(Ipv4Address("10.0.0.2"));
//     isMatch1 = dstIP1.match(udp_packet);
//     std::cout << "DstIPAddress Test Match: " << isMatch1 << std::endl;

//     // test dest mask filter - no match
//     DstMask dstMask0(Ipv4Address("10.0.3.3"), Ipv4Mask("255.255.255.0"));
//     isMatch0 = dstMask0.match(udp_packet);
//     std::cout << "DstMask Test No Match: " << isMatch0 << std::endl;
//     // test dest mask filter - match
//     DstMask dstMask1(Ipv4Address("10.0.0.3"), Ipv4Mask("255.255.255.0"));
//     isMatch1 = dstMask1.match(udp_packet);
//     std::cout << "DstMask Test Match: " << isMatch1 << std::endl;

//     // test dest port filter - match (UDP)
//     DstPortNumber udpDstPort0(2000);
//     isMatch0 = udpDstPort0.match(udp_packet);
//     std::cout << "UDP DstPortNumberTest No Match: " << isMatch0 << std::endl;
//     // test dest port filter - no match (UDP)
//     DstPortNumber udpDstPort1(5000);
//     isMatch1 = udpDstPort1.match(udp_packet);
//     std::cout << "UDP DstPortNumber Test Match: " << isMatch1 << std::endl;

//     // test dest port filter - match (TCP)
//     DstPortNumber tcpDstPort0(2000);
//     isMatch0 = tcpDstPort0.match(tcp_packet);
//     std::cout << "TCP DstPortNumberTest No Match: " << isMatch0 << std::endl;
//     // test dest port filter - no match (TCP)
//     DstPortNumber tcpDstPort1(5000);
//     isMatch1 = tcpDstPort1.match(tcp_packet);
//     std::cout << "TCP DstPortNumber Test Match: " << isMatch1 << std::endl;

//     // test protocol filter - match
//     ProtocolNumber protocolNumber0(6);
//     isMatch0 = protocolNumber0.match(udp_packet);
//     std::cout << "ProtocolNumber No Match: " << isMatch0 << std::endl;
//     // test protocol filter - no match
//     ProtocolNumber protocolNumber1(17);
//     isMatch1 = protocolNumber1.match(udp_packet);
//     std::cout << "ProtocolNumber Match: " << isMatch1 << std::endl;
// }
