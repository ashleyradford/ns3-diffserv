#include "drr.h"

// SPQ constructor
DRR::DRR() : active_queue(0) {}

// DRR overridden schedule method
Ptr<const Packet> DRR::Schedule() const {
    // get traffic class queues
    std::vector<TrafficClass*> queues = GetQueues();

    // check that there are queues to serve
    if (queues.size() == 0) {
        std::cout << "No queues to serve." << std::endl;
        return nullptr;
    }

    // reset to current deficit
    next_active_queue = active_queue;
    next_deficit_counter = deficit_counter;

    // check first that there are any packets
    uint32_t empty_count = 0;
    for (int i = 0; i < queues.size(); i++) {
        if (queues[i]->IsEmpty()) {
            empty_count++;
        }
    }
    if (empty_count == queues.size()) {
        std::cout << "All queues are empty." << std::endl;
        return nullptr;
    }

    // drr algorithm 
    while (true) {
        if (!queues[next_active_queue]->IsEmpty()) {
            next_deficit_counter[next_active_queue] = queues[next_active_queue]->GetWeight() + next_deficit_counter[next_active_queue];
            // std::cout << "Deficit counter for: " << next_active_queue << ": " << next_deficit_counter[next_active_queue] << std::endl;
            uint32_t packet_size = queues[next_active_queue]->Peek()->GetSize();
            if (packet_size <= next_deficit_counter[next_active_queue]) {
                // std::cout << "Packet size to remove: " << packet_size << std::endl;
                next_deficit_counter[next_active_queue] = next_deficit_counter[next_active_queue] - packet_size;
                return queues[next_active_queue]->Peek();
            }
        }
        next_active_queue = (next_active_queue + 1) % queues.size();
    }
    return queues[next_active_queue]->Peek();
}

// DRR overridden add queue method
void DRR::AddQueue(TrafficClass *q) {
    DiffServ::AddQueue(q);
    deficit_counter.push_back(0);
}

Ptr<Packet> DRR::DoDequeue() {
    Ptr<Packet> dequeued_packet = DiffServ::DoDequeue();
    if (dequeued_packet) {
        active_queue = next_active_queue;
        deficit_counter = next_deficit_counter;
        return dequeued_packet;
    }
    return nullptr;
}
