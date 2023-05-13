#include "filter.h"

Filter::Filter() {}

/**
 * Adds a FilterElement to elements vector
 * \param elem FilterElement to add
 */
void
Filter::AddElement(FilterElement *elem)
{
    elements.push_back(elem);
}

/**
 * Matches a packet to each FilterElement in elements vector
 * \returns true if all FilterElements are a match, false otherwise
 */
bool
Filter::match(Ptr<Packet> p)
{
    for (FilterElement *elem : elements)
    {
        if (!elem->match(p))
        {
            return 0;
        }
    }
    return 1;
}
