#include "filter_elements.h"

// SrcIPAddress constructor
SrcIPAddress::SrcIPAddress(Ipv4Address addr) : default_address(addr) {}

// SrcIPAddress match method
bool SrcIPAddress::match(Ptr<Packet> p) const {
    Ptr<Packet> p_copy = p->Copy();

    PppHeader pppHeader;
    p_copy->RemoveHeader(pppHeader);
    Ipv4Header header;
    p_copy->PeekHeader(header);

    return header.GetSource() == default_address;
}

// SrcMask constructor
SrcMask::SrcMask(Ipv4Address addr, Ipv4Mask mask) : default_address(addr), default_mask(mask) {}

// SrcMask match method
bool SrcMask::match(Ptr<Packet> p) const {
    Ptr<Packet> p_copy = p->Copy();

    PppHeader pppHeader;
    p_copy->RemoveHeader(pppHeader);
    Ipv4Header header;
    p_copy->PeekHeader(header);

    return default_mask.IsMatch(header.GetSource(), default_address);    
}

// SrcPortNumber constructor
SrcPortNumber::SrcPortNumber(uint32_t port) : default_port(port) {}

// SrcPortNumber match method
bool SrcPortNumber::match(Ptr<Packet> p) const {
    Ptr<Packet> p_copy = p->Copy();

    PppHeader pppHeader;
    p_copy->RemoveHeader(pppHeader);
    Ipv4Header header;
    p_copy->RemoveHeader(header);

    // udp protocol number is 17 and tcp protocol is 6
    uint8_t protocol = header.GetProtocol();
    if (protocol == 17) {
        UdpHeader udpHeader;
        p_copy->PeekHeader(udpHeader);
        uint16_t port = udpHeader.GetSourcePort();
        return port == default_port;
    } else if (protocol == 6) {
        TcpHeader tcpHeader;
        p_copy->PeekHeader(tcpHeader);
        uint16_t port = tcpHeader.GetSourcePort();
        return port == default_port;
    } else {
        return 0;
    }
}

// DstIPAddress constructor
DstIPAddress::DstIPAddress(Ipv4Address addr) : default_address(addr) {}

// DstIPAddress method
bool DstIPAddress::match(Ptr<Packet> p) const {
    Ptr<Packet> p_copy = p->Copy();

    PppHeader pppHeader;
    p_copy->RemoveHeader(pppHeader);
    Ipv4Header header;
    p_copy->PeekHeader(header);

    return header.GetDestination() == default_address;
}

// DstMask constructor
DstMask::DstMask(Ipv4Address addr, Ipv4Mask mask) : default_address(addr), default_mask(mask) {}

// DstMask method
bool DstMask::match(Ptr<Packet> p) const {
    Ptr<Packet> p_copy = p->Copy();

    PppHeader pppHeader;
    p_copy->RemoveHeader(pppHeader);
    Ipv4Header header;
    p_copy->PeekHeader(header);

    return default_mask.IsMatch(header.GetSource(), default_address);  
}

// DstPortNumber constructor
DstPortNumber::DstPortNumber(uint32_t port) : default_port(port) {}

// DstPortNumber method
bool DstPortNumber::match(Ptr<Packet> p) const {
    Ptr<Packet> p_copy = p->Copy();

    PppHeader pppHeader;
    p_copy->RemoveHeader(pppHeader);
    Ipv4Header header;
    p_copy->RemoveHeader(header);
    uint8_t protocol = header.GetProtocol();

    // udp protocol number is 17 and tcp protocol is 6
    if (protocol == 17) {
        UdpHeader udpHeader;
        p_copy->PeekHeader(udpHeader);
        uint16_t port = udpHeader.GetDestinationPort();
        return port == default_port;
    } else if (protocol == 6) {
        TcpHeader tcpHeader;
        p_copy->PeekHeader(tcpHeader);
        uint16_t port = tcpHeader.GetDestinationPort();
        return port == default_port;
    } else {
        return 0;
    }
}

// DstPortNumber constructor
ProtocolNumber::ProtocolNumber(uint32_t protocol) : default_protocol(protocol) {}

// ProtocolNumber method
bool ProtocolNumber::match(Ptr<Packet> p) const {
    Ptr<Packet> p_copy = p->Copy();

    PppHeader pppHeader;
    p_copy->RemoveHeader(pppHeader);
    Ipv4Header header;
    p_copy->PeekHeader(header);

    return header.GetProtocol() == default_protocol;
}
