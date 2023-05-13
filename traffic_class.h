#ifndef TRAFFIC_CLASS_H
#define TRAFFIC_CLASS_H

#include "ns3/core-module.h"
#include "filter.h"

using namespace ns3;

class TrafficClass
{
    public:
        TrafficClass();

        std::vector<Filter*> filters;

        bool Enqueue(Ptr<Packet> p);
        Ptr<Packet> Dequeue();
        Ptr<Packet> Remove();
        Ptr<const Packet> Peek();
        bool match(Ptr<Packet> p);
        bool IsEmpty();
        uint32_t GetSize();
        void AddFilter(Filter* filter);
        void SetMaxPackets(uint32_t max_p);
        void SetWeight(double_t w);
        double_t GetWeight();
        void SetPriorityLevel(uint32_t level);
        uint32_t GetPriorityLevel();
        void SetDefault(bool d);
        bool GetDefault();

    private:
        uint32_t packets;
        uint32_t maxPackets;
        double_t weight;
        uint32_t priority_level;
        bool isDefault;
        std::queue<Ptr<Packet>> m_queue;
};

#endif // TRAFFIC_CLASS_H
