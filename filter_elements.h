#ifndef FILTER_ELEMENTS_H
#define FILTER_ELEMENTS_H

#include "ns3/packet.h"
#include "ns3/ppp-header.h"
#include "ns3/ipv4-header.h"
#include "ns3/udp-header.h"
#include "ns3/tcp-header.h"

using namespace ns3;

// abstract base class
class FilterElement {
    public:
        virtual bool match(Ptr<Packet> p) const = 0;
};

// SrcIPAddress class derived from FilterElement
class SrcIPAddress : public FilterElement {
    private:
        Ipv4Address default_address;

    public:
        SrcIPAddress(Ipv4Address addr);

        bool match(Ptr<Packet> p) const override;
};

// SrcMask class derived from FilterElement
class SrcMask : public FilterElement {
    private:
        Ipv4Address default_address;
        Ipv4Mask default_mask;

    public:
        SrcMask(Ipv4Address addr, Ipv4Mask mask);

        bool match(Ptr<Packet> p) const override;
};

// SrcPortNumber class derived from FilterElement
class SrcPortNumber : public FilterElement {
    private:
        uint32_t default_port;

    public:
        SrcPortNumber(uint32_t port);

        bool match(Ptr<Packet> p) const override;
};

// DstIPAddress class derived from FilterElement
class DstIPAddress : public FilterElement {
    private:
        Ipv4Address default_address;

    public:
        DstIPAddress(Ipv4Address addr);

        bool match(Ptr<Packet> p) const override;
};

// DstMask class derived from FilterElement
class DstMask : public FilterElement {
    private:
        Ipv4Address default_address;
        Ipv4Mask default_mask;

    public:
        DstMask(Ipv4Address addr, Ipv4Mask mask);

        bool match(Ptr<Packet> p) const override;
};

// DstPortNumber class derived from FilterElement
class DstPortNumber : public FilterElement {
    private:
        uint32_t default_port;

    public:
        DstPortNumber(uint32_t port);

        bool match(Ptr<Packet> p) const override;
};

// ProtocolNumber class derived from FilterElement
class ProtocolNumber : public FilterElement {
    private:
        uint32_t default_protocol;

    public:
        ProtocolNumber(uint32_t protocol);

        bool match(Ptr<Packet> p) const override;
};

#endif // FILTER_ELEMENT_H
