#include "filter.h"

// Filter constructor
Filter::Filter() {}

// Filter add method
void Filter::AddElement(FilterElement *elem) {
    elements.push_back(elem);
}

// Filter match method
bool Filter::match(Ptr<Packet> p) {
    for (FilterElement *elem : elements) {
        if (!elem->match(p)) {
            return 0;
        }
    }
    return 1;
}
