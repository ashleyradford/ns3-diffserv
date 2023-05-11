#ifndef DRR_H
#define DRR_H

#include "diff_serv.h"

using namespace ns3;

class DRR : public DiffServ {
    public:
        DRR();

        Ptr<const Packet> Schedule() const override;
        void AddQueue(TrafficClass *q) override;

    protected:
        Ptr<Packet> DoDequeue() override;
        Ptr<Packet> DoRemove() override;

    private:
        uint32_t active_queue;
        mutable uint32_t next_active_queue;
        std::vector<uint32_t> deficit_counter;
        mutable std::vector<uint32_t> next_deficit_counter;
};

#endif // DRR_H
