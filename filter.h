#ifndef FILTER_H
#define FILTER_H

#include "filter_elements.h"

using namespace ns3;

class Filter {
    public:
        Filter();

        std::vector<FilterElement*> elements;

        void AddElement(FilterElement *elem);
        bool match(Ptr<Packet> p);
};

#endif // FILTER_H
