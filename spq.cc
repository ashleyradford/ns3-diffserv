#include "spq.h"

SPQ::SPQ() {}

/**
 * Finds the next scheduled packet by looping through the TrafficClasses
 * in q_class. The next sheduled packet will be from the highest
 * prioritized non empty queue.
 * 
 * Once this queue is found, Schedule will simply peek and return
 * the front packet.
 * 
 * \returns next scheduled packet
 */
Ptr<const Packet>
SPQ::Schedule() const
{
    // get traffic class queues
    std::vector<TrafficClass*> queues = GetQueues();

    // check that there are queues to serve
    if (queues.size() == 0)
    {
        std::cout << "No queues to serve." << std::endl;
        return nullptr;
    }

    // find highest nonempty queue
    uint32_t priority_queue = 0;
    uint32_t empty_count = 0;
    for (int i = 0; i < queues.size(); i++)
    {
        if (queues[i]->IsEmpty())
        {
            empty_count++;
        }
        else if (queues[i]->GetPriorityLevel() < queues[priority_queue]->GetPriorityLevel() || queues[priority_queue]->IsEmpty())
        {
            priority_queue = i;
        }
    }

    // check if all queues are empty
    if (empty_count == queues.size())
    {
        std::cout << "All queues are empty." << std::endl;
        return nullptr;
    }

    return queues[priority_queue]->Peek();
}
