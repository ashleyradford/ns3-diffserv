#include "diff_serv.h"

// DiffServ constructor
DiffServ::DiffServ() {}

// DiffServ overridden enqueue method
bool DiffServ::Enqueue(Ptr<Packet> p) {
    bool added = DoEnqueue(p);
    // std::cout << "Added: " << added << std::endl;
    return added;
}

// DiffServ overridden dequeue method
Ptr<Packet> DiffServ::Dequeue() {
    Ptr<Packet> retrieved = DoDequeue();
    return retrieved;
}

// DiffServ overridden remove method
Ptr<Packet> DiffServ::Remove() {
    Ptr<Packet> removed = DoRemove();
    return removed;
}

// DiffServ overridden peek method
Ptr<const Packet> DiffServ::Peek() const {
    Ptr<const Packet> peeked = DoPeek();
    return peeked;
}

// DiffServ classify method
uint32_t DiffServ::Classify(Ptr<Packet> p) {
    uint32_t default_index = -1;
    for (int i = 0; i < q_class.size(); i++) {
        if (q_class[i]->match(p)) {
            return i;
        }
        if (q_class[i]->GetDefault()) {
            default_index = i;
        }
    }
    return default_index;
}

// DiffServ add queue method
void DiffServ::AddQueue(TrafficClass* q) {
    q_class.push_back(q);
}

// DiffServ get queues method
std::vector<TrafficClass*> DiffServ::GetQueues() const {
    return q_class;
}

// DiffServ do enqueue method
bool DiffServ::DoEnqueue(Ptr<Packet> p) {
    uint32_t index = Classify(p);
    if (index == -1) {
        return 0;
    }
    q_class[index]->Enqueue(p);
    return 1;
}

// DiffServ do dequeue method
Ptr<Packet> DiffServ::DoDequeue() {
    Ptr<const Packet> scheduled_packet = Schedule();

    // dequeue packet if not null
    if (scheduled_packet) {
        uint32_t index = Classify(scheduled_packet->Copy());
        return q_class[index]->Dequeue();
    }

    return nullptr;
}

// DiffServ do remove method
Ptr<Packet> DiffServ::DoRemove() {
    Ptr<const Packet> removed_packet = Schedule();

    // remove packet if not null
    if (removed_packet) {
        uint32_t index = Classify(removed_packet->Copy());
        return q_class[index]->Remove();
    }

    return nullptr;
}

// DiffServ do peek method
Ptr<const Packet> DiffServ::DoPeek() const {
    Ptr<const Packet> next_packet = Schedule()->Copy();
    return next_packet;
}
