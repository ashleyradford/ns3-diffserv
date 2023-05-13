#include "diff_serv.h"

DiffServ::DiffServ() {}

/**
 * Enqueues a packet
 * \param p packet to enqueue
 * \returns true if successfully enqueued, false otherwise
 */
bool
DiffServ::Enqueue(Ptr<Packet> p)
{
    bool added = DoEnqueue(p);
    // std::cout << "Added: " << added << std::endl;
    return added;
}

/**
 * Dequeues the next scheduled packet
 * \returns packet that is dequeued
 */
Ptr<Packet>
DiffServ::Dequeue()
{
    Ptr<Packet> retrieved = DoDequeue();
    return retrieved;
}

/**
 * Renoves the next scheduled packet
 * \returns packet that is removed
 */
Ptr<Packet>
DiffServ::Remove()
{
    Ptr<Packet> removed = DoRemove();
    return removed;
}

/**
 * Peeks at the next scheduled packet
 * \returns next scheduled packet
 */
Ptr<const Packet>
DiffServ::Peek() const
{
    Ptr<const Packet> peeked = DoPeek();
    return peeked;
}

/**
 * Classifies a packet to a TrafficClass
 * \param p packet to classify
 * \returns index of TrafficClass
 */
uint32_t
DiffServ::Classify(Ptr<Packet> p)
{
    uint32_t default_index = -1;
    for (int i = 0; i < q_class.size(); i++)
    {
        if (q_class[i]->match(p))
        {
            return i;
        }
        if (q_class[i]->GetDefault())
        {
            default_index = i;
        }
    }
    return default_index;
}

/**
 * Adds a TrafficClass to q_class vector
 * \param tc traffic class to add
 */
void
DiffServ::AddQueue(TrafficClass* tc)
{
    q_class.push_back(tc);
}

/**
 * Getter for q_class
 * \returns DiffServ's q_class
 */
std::vector<TrafficClass*>
DiffServ::GetQueues() const
{
    return q_class;
}

/**
 * Dequeues the front packet from the next scheduled TrafficClass in q_class
 * \returns packet that has been dequeued
 */
Ptr<Packet>
DiffServ::DoDequeue()
{
    Ptr<const Packet> scheduled_packet = Schedule();

    // dequeue packet if not null
    if (scheduled_packet)
    {
        uint32_t index = Classify(scheduled_packet->Copy());
        return q_class[index]->Dequeue();
    }

    return nullptr;
}

/**
 * Enqueues a packet to its classified TrafficClass in q_class
 * \param p packet to enqueue
 * \returns true if successfully enqueued, false otherwise
 */
bool
DiffServ::DoEnqueue(Ptr<Packet> p)
{
    uint32_t index = Classify(p);
    if (index == -1)
    {
        return 0;
    }
    q_class[index]->Enqueue(p);
    return 1;
}

/**
 * Removes the front packet from the next scheduled TrafficClass in q_class
 * \returns packet that has been removed
 */
Ptr<Packet>
DiffServ::DoRemove()
{
    Ptr<const Packet> removed_packet = Schedule();

    // remove packet if not null
    if (removed_packet)
    {
        uint32_t index = Classify(removed_packet->Copy());
        return q_class[index]->Remove();
    }

    return nullptr;
}

/**
 * Peeks at the front packet from the next scheduled TrafficClass in q_class
 * \returns next scheduled packet
 */
Ptr<const Packet>
DiffServ::DoPeek() const
{
    Ptr<const Packet> next_packet = Schedule()->Copy();
    return next_packet;
}
