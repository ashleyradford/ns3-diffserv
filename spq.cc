#include "spq.h"

// SPQ constructor
SPQ::SPQ() {}

// SPQ overridden schedule method
Ptr<const Packet> SPQ::Schedule() const {
    // get traffic class queues
    std::vector<TrafficClass*> queues = GetQueues();

    // check that there are queues to serve
    if (queues.size() == 0) {
        std::cout << "No queues to serve." << std::endl;
        return nullptr;
    }

    // find highest nonempty queue
    uint32_t priority_queue = 0;
    uint32_t empty_count = 0;
    for (int i = 0; i < queues.size(); i++) {
        if (queues[i]->IsEmpty()) {
            empty_count++;
        } else if (queues[i]->GetPriorityLevel() < queues[priority_queue]->GetPriorityLevel() || queues[priority_queue]->IsEmpty()) {
            priority_queue = i;
        }
    }

    // check if all queues are empty
    if (empty_count == queues.size()) {
        std::cout << "All queues are empty." << std::endl;
        return nullptr;
    }

    return queues[priority_queue]->Peek();
}
