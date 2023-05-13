#include "traffic_class.h"

TrafficClass::TrafficClass() : packets(0) {}

/**
 * Enqueues a packet to m_queue
 * \param p packet to enqueue
 * \returns true if successfully enqueued, false otherwise
 */
bool
TrafficClass::Enqueue(Ptr<Packet> p)
{
    if (packets < maxPackets)
    {
        m_queue.push(p);
        packets++;
        return 1;
    }
    std::cout << "Queue at capacity." << std::endl;
    return 0;
}

/**
 * Dequeues a packet from m_queue
 * \returns true if successfully dequeued, false otherwise
 */
Ptr<Packet>
TrafficClass::Dequeue()
{
    if (m_queue.empty())
    {
        std::cout << "Queue empty." << std::endl;
        return nullptr;
    }
    Ptr<Packet> p = m_queue.front();
    m_queue.pop();
    packets--;
    return p;
}

/**
 * Removes a packet from m_queue
 * \returns true if successfully removed, false otherwise
 */
Ptr<Packet>
TrafficClass::Remove()
{
    if (m_queue.empty())
    {
        std::cout << "Queue empty." << std::endl;
        return nullptr;
    }
    Ptr<Packet> p = m_queue.front();
    m_queue.pop();
    packets--;
    return p;
}

/**
 * Peeks at m_queue's front packet
 * \returns m_queue's front packet
 */
Ptr<const Packet>
TrafficClass::Peek()
{
    if (IsEmpty())
    {
        std::cout << "Queue empty." << std::endl;
        return nullptr;
    }
    Ptr<Packet> p = m_queue.front();
    return p;
}

/**
 * Matches a packet to each Filter in filters vector
 * \param p packet to match
 * \returns true if at least one filter is a match, false otherwise
 */
bool
TrafficClass::match(Ptr<Packet> p)
{
    // no filters, so automatic match
    if (filters.size() == 0)
    {
        return 1;
    }
    // check filters if they exist
    for (Filter *filter : filters)
    {
        if (filter->match(p))
        {
            return 1;
        }
    }
    return 0;
}

/**
 * Checks if there are no packets
 * \returns true if empty, false otherwise
 */
bool
TrafficClass::IsEmpty()
{
    return packets == 0;
}

/**
 * Getter for m_queue's size
 * \returns number of packets in m_queues
 */
uint32_t
TrafficClass::GetSize()
{
    return m_queue.size();
}

/**
 * Adds a Filter to filters vector
 * \param filter filter to add
 */
void
TrafficClass::AddFilter(Filter *filter)
{
    filters.push_back(filter);
}

/**
 * Set's m_queue's maximum packet size
 * \param max max size
 */
void
TrafficClass::SetMaxPackets(uint32_t max)
{
    maxPackets = max;
}

/**
 * Setter for weight
 * \param w weight
 */
void
TrafficClass::SetWeight(double_t w)
{
    weight = w;
}

/**
 * Getter for weight
 * \returns weight
 */
double_t
TrafficClass::GetWeight()
{
    return weight;
}

/**
 * Setter for priority level
 * \param level priority level
 */
void
TrafficClass::SetPriorityLevel(uint32_t level)
{
    priority_level = level;
}

/**
 * Getter for priority level
 * \returns priority level
 */
uint32_t
TrafficClass::GetPriorityLevel()
{
    return priority_level;
}

/**
 * Setter for is default
 * \param default_queue true if default, false otherwise
 */
void
TrafficClass::SetDefault(bool default_queue)
{
    isDefault = default_queue;
}

/**
 * Getter for is default
 * \returns is default
 */
bool
TrafficClass::GetDefault()
{
    return isDefault;
}
