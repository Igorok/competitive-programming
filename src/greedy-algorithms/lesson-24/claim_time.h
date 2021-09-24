#ifndef CLAIM_TIME_H
#define CLAIM_TIME_H
#endif

namespace ns1
{
    struct claim_time
    {
        int start;
        int end;
        bool operator<(const claim_time &ct) const;
        int sum();
    };
}