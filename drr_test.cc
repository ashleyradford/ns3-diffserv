#include "drr.h"

int
main (int argc, char *argv[])
{
    // create UDP packets
    Ptr<Packet> udp_packet1 = Create<Packet>(50);
    UdpHeader udpHeader;
    udpHeader.SetSourcePort(4000);
    udp_packet1->AddHeader(udpHeader);
    Ipv4Header ipHeader;
    ipHeader.SetProtocol(17);
    ipHeader.SetSource(Ipv4Address("10.0.0.1"));
    udp_packet1->AddHeader(ipHeader);
    PppHeader pppHeader;
    udp_packet1->AddHeader(pppHeader);
    std::cout << "Packet 1 created " << udp_packet1 << std::endl;

    Ptr<Packet> udp_packet2 = Create<Packet>(500);
    udpHeader.SetSourcePort(4000);
    udp_packet2->AddHeader(udpHeader);
    ipHeader.SetProtocol(17);
    ipHeader.SetSource(Ipv4Address("10.0.0.1"));
    udp_packet2->AddHeader(ipHeader);
    udp_packet2->AddHeader(pppHeader);
    std::cout << "Packet 2 created " << udp_packet2 << std::endl;

    Ptr<Packet> udp_packet3 = Create<Packet>(150);
    udpHeader.SetSourcePort(5000);
    udp_packet3->AddHeader(udpHeader);
    ipHeader.SetProtocol(17);
    ipHeader.SetSource(Ipv4Address("10.0.0.1"));
    udp_packet3->AddHeader(ipHeader);
    udp_packet3->AddHeader(pppHeader);
    std::cout << "Packet 3 created " << udp_packet3 << std::endl;

    Ptr<Packet> udp_packet4 = Create<Packet>(50);
    udpHeader.SetSourcePort(5000);
    udp_packet4->AddHeader(udpHeader);
    ipHeader.SetProtocol(17);
    ipHeader.SetSource(Ipv4Address("10.0.0.1"));
    udp_packet4->AddHeader(ipHeader);
    udp_packet4->AddHeader(pppHeader);
    std::cout << "Packet 4 created " << udp_packet4 << std::endl;

    Ptr<Packet> udp_packet5 = Create<Packet>(700);
    udpHeader.SetSourcePort(6000);
    udp_packet5->AddHeader(udpHeader);
    ipHeader.SetProtocol(17);
    ipHeader.SetSource(Ipv4Address("10.0.0.1"));
    udp_packet5->AddHeader(ipHeader);
    udp_packet5->AddHeader(pppHeader);
    std::cout << "Packet 5 created " << udp_packet5 << std::endl;

    // create Filter Elements
    SrcPortNumber fe1(4000);
    SrcPortNumber fe2(5000);
    SrcPortNumber fe3(6000);

    // create filters
    Filter f1, f2, f3;
    f1.AddElement(&fe1);
    f2.AddElement(&fe2);
    f3.AddElement(&fe3);

    // create Traffic Class 1
    TrafficClass trafficClass1;
    trafficClass1.SetMaxPackets(5);
    trafficClass1.SetWeight(200);
    trafficClass1.SetDefault(1);
    trafficClass1.AddFilter(&f1);

    // create Traffic Class 2
    TrafficClass trafficClass2;
    trafficClass2.SetMaxPackets(5);
    trafficClass2.SetWeight(100);
    trafficClass2.SetDefault(0);
    trafficClass2.AddFilter(&f2);

    // create Traffic Class 3
    TrafficClass trafficClass3;
    trafficClass3.SetMaxPackets(5);
    trafficClass3.SetWeight(300);
    trafficClass3.SetDefault(0);
    trafficClass3.AddFilter(&f3);

    // create DRR class
    DRR drr;

    // no queues
    std::cout << "Trying to dequeue before queues added:" << std::endl;
    drr.Dequeue(); // try to dequeue

    // empty queues
    drr.AddQueue(&trafficClass1);
    drr.AddQueue(&trafficClass2);
    drr.AddQueue(&trafficClass3);
    std::cout << "Trying to dequeue from empty queues:" << std::endl;
    drr.Dequeue(); // try to dequeue

    // dequeue packet from default filter
    drr.Enqueue(udp_packet5);
    std::cout << "Dequeueing default packet." << std::endl;
    Ptr<Packet> dequeued_p = drr.Dequeue();
    std::cout << dequeued_p << std::endl;

    // dequeue empty queues
    std::cout << "Default packet should be removed:" << std::endl;
    dequeued_p = drr.Dequeue();

    // enqueue 4 packets
    drr.Enqueue(udp_packet1);
    drr.Enqueue(udp_packet2);
    drr.Enqueue(udp_packet3);
    drr.Enqueue(udp_packet4);
    drr.Enqueue(udp_packet5);

    Ptr<const Packet> peeked = drr.Peek();
    std::cout << "Peeking a packet: " << peeked << std::endl;

    dequeued_p = drr.Dequeue();
    std::cout << dequeued_p << std::endl;
    dequeued_p = drr.Dequeue();
    std::cout << dequeued_p << std::endl;
    dequeued_p = drr.Dequeue();
    std::cout << dequeued_p << std::endl;
    dequeued_p = drr.Dequeue();
    std::cout << dequeued_p << std::endl;
    dequeued_p = drr.Dequeue();
    std::cout << dequeued_p << std::endl;

    // no more packets to dequeue
    std::cout << "All packets should be dequeued:" << std::endl;
    dequeued_p = drr.Dequeue();
}
