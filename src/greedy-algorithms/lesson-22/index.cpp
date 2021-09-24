#include <vector>

using namespace std;

const int TMAX = 1e3;
/*
vector<int> deadlineList{
    2,
    2,
    5,
    1,
    3,
};
vector<int> costList{
    5,
    4,
    3,
    2,
    1,
}; // sorted by price
*/

vector<int> deadlineList{
    2,
    2,
    1,
    7,
    5,
    5,
    4,
    7,
    7,
    5,
};
vector<int> costList{
    92,
    80,
    66,
    55,
    55,
    38,
    35,
    19,
    16,
    2,
}; // sorted by price

vector<int> used(costList.size() + 1, 0);

long long calculate()
{
    long long sum = 0;
    for (int i = 0; i < costList.size(); i++)
    {
        int day = deadlineList[i];
        while (day >= 1 && used[day])
        {
            day--;
        }
        if (day == 0)
        {
            continue;
        }
        used[day] = costList[i];
        sum += costList[i];
    }

    return sum;
}

int main()
{
    long long sum = calculate();
    return 0;
}