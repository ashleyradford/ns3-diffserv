#ifndef SPQ_H
#define SPQ_H

#include "diff_serv.h"

using namespace ns3;

class SPQ : public DiffServ
{
    public:
        SPQ();

        Ptr<const Packet> Schedule() const override;
};

#endif // SPQ_H
