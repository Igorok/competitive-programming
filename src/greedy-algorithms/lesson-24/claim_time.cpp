
#include "claim_time.h"

using namespace ns1;

namespace ns1
{
    bool claim_time::operator<(const claim_time &ct) const
    {
        return end < ct.end;
    }

    int claim_time::sum()
    {
        return start + end;
    }

}
