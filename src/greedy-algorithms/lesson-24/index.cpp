#include <vector>
#include <algorithm>
#include "claim_time.h"

using namespace std;
using namespace ns1;

vector<claim_time> resultTable;
vector<claim_time> timeTable;

void calculate()
{
    int last = 0;
    sort(timeTable.begin(), timeTable.end());
    resultTable.push_back(timeTable[0]);
    for (int i = 1; i < timeTable.size(); i++)
    {
        if (timeTable[i].start >= timeTable[last].end)
        {
            resultTable.push_back(timeTable[i]);
            last = i;
        }
    }
}

int main()
{

    timeTable.push_back(claim_time({1, 5}));
    timeTable.push_back(claim_time({3, 6}));
    timeTable.push_back(claim_time({5, 7}));

    calculate();
    return 0;
}
