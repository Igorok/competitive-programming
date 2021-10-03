/*
Задача о размене:
Имеются монеты n номиналов a1 , a2, ..., an и сумма s. Нужно набрать эту сумму наименьшим количеством монет. Можно использовать любое число монет каждого номинала.

i - сумма
d[i] - минимальное число монет, необходимое, чтобы набрать сумму i.
d[i] = min(d[i - a[j]]) + 1

a
1, 6, 8, 10
d
1 2 3 4 5 6 7 8 9 10
1 2 3 4 5 6 2 3 2 3
          1   1   1

d1 = min(d[1-1]) + 1 = 1 ???
d2 = min(d[2 - 1]) + 1 = d[1] + 1 = 2 ???
d3 = min(d[3 - 1]) + 1 = d[2] + 1 = 3 ???
...
d6 = min(d[6 - 1]) + 1 = d[5] + 1 = 6
d6 = min(d[6 - 6]) + 1 = d[0] + 1 = 1

d7 = min(d[7 - 1]) + 1 = d[6] + 1 = 2

d8 = min(d[8 - 1]) + 1 = d[7] + 1 = 3
d8 = min(d[8 - 8]) + 1 = d[0] + 1 = 1

d8 = min(d[9 - 1]) + 1 = d[8] + 1 = 2

d8 = min(d[10 - 1]) + 1 = d[9] + 1 = 3
d8 = min(d[10 - 10]) + 1 = d[0] + 1 = 1
*/

#include <vector>
#include <fstream>

using namespace std;

ofstream cout("output.txt");

struct CoinTerminal
{
    int INF;
    int s;
    vector<int> a;
    vector<int> d;
    vector<int> p;

    CoinTerminal(vector<int> arr, int sum)
    {
        s = sum;
        INF = s + 1;
        a = arr;
        d = vector<int>(s + 1);
        d[0] = 0;
        p = vector<int>(s + 1);
    }

    void getCoins()
    {
        // calculate number of coin for every number from 0 to requested sum
        for (int i = 1; i <= s; i++)
        {
            // default value, bigger that possible from real coins
            d[i] = INF;
            // calculate sum for every coin
            for (int j = 0; j < a.size(); j++)
            {
                /*
                i - a[j] - difference between sum - i and coin - a[j]
                d[i - a[j]] + 1 - number of coins for difference + 1 current coin
                */
                if (i - a[j] >= 0 && d[i - a[j]] + 1 < d[i])
                {
                    // minimal number of coins for difference + 1 coin
                    d[i] = d[i - a[j]] + 1;
                    // last coin for sum - i
                    p[i] = a[j];
                }
            }
        }

        cout << d[s] << endl;

        recount(s);
    }

    void recount(int i)
    {
        if (i == 0)
        {
            return;
        }

        // repeat for difference between sum and biggest coin
        recount(i - p[i]);

        // write coin value
        if (i - p[i] > 0)
        {
            cout << "+";
        }
        cout << p[i];
    }
};

int main()
{
    int s = 25;
    vector<int> a{1, 6, 8, 10};
    CoinTerminal ct = CoinTerminal(a, s);
    ct.getCoins();

    return 0;
};