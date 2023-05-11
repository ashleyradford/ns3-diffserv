#include "traffic_class.h"

// TrafficClass constructor
TrafficClass::TrafficClass() : packets(0) {}

// TrafficClass enqueue method
bool TrafficClass::Enqueue(Ptr<Packet> p) {
    if (packets < maxPackets) {
        m_queue.push(p);
        packets++;
        return 1;
    }
    std::cout << "Queue at capacity." << std::endl;
    return 0;
}

// TrafficClass dequeue method
Ptr<Packet> TrafficClass::Dequeue() {
    if (m_queue.empty()) {
        std::cout << "Queue empty." << std::endl;
        return nullptr;
    }
    Ptr<Packet> p = m_queue.front();
    m_queue.pop();
    packets--;
    return p;
}

// TrafficClass remove method
Ptr<Packet> TrafficClass::Remove() {
    if (m_queue.empty()) {
        std::cout << "Queue empty." << std::endl;
        return nullptr;
    }
    Ptr<Packet> p = m_queue.front();
    m_queue.pop();
    packets--;
    return p;
}

// TrafficClass peek method
Ptr<const Packet> TrafficClass::Peek() {
    if (IsEmpty()) {
        std::cout << "Queue empty." << std::endl;
        return nullptr;
    }
    Ptr<Packet> p = m_queue.front();
    return p;
}

// TrafficClass match method
bool TrafficClass::match(Ptr<Packet> p) {
    // no filters, so automatic match
    if (filters.size() == 0) {
        return 1;
    }
    // check filters if they exist
    for (Filter *filter : filters) {
        if (filter->match(p)) {
            return 1;
        }
    }
    return 0;
}

// TrafficClass is empty method
bool TrafficClass::IsEmpty() {
    return packets == 0;
}

// TrafficClass get size method
uint32_t TrafficClass::GetSize() {
    return m_queue.size();
}

// TrafficClass add filter method
void TrafficClass::AddFilter(Filter *filter) {
    filters.push_back(filter);
}

// TrafficClass set max packets method
void TrafficClass::SetMaxPackets(uint32_t max) {
    maxPackets = max;
}

// TrafficClass set weight method
void TrafficClass::SetWeight(double_t w) {
    weight = w;
}

// TrafficClass get weight method
double_t TrafficClass::GetWeight() {
    return weight;
}

// TrafficClass set priority level method
void TrafficClass::SetPriorityLevel(uint32_t level) {
    priority_level = level;
}

// TrafficClass get priority level method
uint32_t TrafficClass::GetPriorityLevel() {
    return priority_level;
}

// TrafficClass set default
void TrafficClass::SetDefault(bool default_queue) {
    isDefault = default_queue;
}

// TrafficClass get default
bool TrafficClass::GetDefault() {
    return isDefault;
}
