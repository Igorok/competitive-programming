/*
Дано множество из n элементов a 1 , a 2 , . . . , a n . Нужно для каждого из его подмножеств посчитать сумму элементов и уметь ее
быстро возвращать.
*/

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <bitset>

using namespace std;

ofstream cout("output.txt");

vector<int> a = vector<int>({10, 9, 8});
vector<int> sum;

void out()
{
    for (int i = 0; i < sum.size(); i++)
    {
        long long j = (long long)(i);
        string s = bitset<8>(j).to_string();

        cout << s << ": " << sum[i] << endl;
    }
}

void solutionBruteForce()
{
    int n = a.size();
    sum = vector<int>(1 << n, 0);

    for (int mask = 0; mask < (1 << n); mask++)
    {
        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
            {
                sum[mask] += a[i];
            }
        }
    }

    cout << "Brute force:" << endl;
    out();
}

void solutionDynamic()
{
    int n = a.size();
    sum = vector<int>(1 << n, 0);

    /*
    0 - 000
    1 - 001
    2 - 010
    3 - 011
    4 - 100
    5 - 101
    6 - 110
    7 - 111
    */
    for (int mask = 0; mask < (1 << n); mask++)
    {
        for (int i = 0; i < n; i++)
        {
            /*
            1 << 0 - 001
            1 << 1 - 010
            1 << 2 - 100
            */
            if (mask & (1 << i))
            {
                /*
                mask - 1 - 001
                i - 0
                1 << i - 001
                001 & 001 = 001
                001 ^ 001 = 000 = 0
                sum[0] = 0
                a[0] = 10
                sum[1] = 0 + 10 = 10
                break;

                mask - 2 - 010
                i - 0
                1 << i - 001
                010 & 001 = 000
                continue
                i - 1
                i << i = 010
                010 & 010 = 010
                010 ^ 010 = 000 = 0
                sum[0] = 0
                a[1] = 9
                s[2] = 0 + 9 = 9

                mask - 3 - 011
                i - 0
                1 << i - 001
                011 & 001 = 001
                011 ^ 001 = 010 = 2
                sum[2] = 9
                a[0] = 10
                sum[3] = 9 + 10 = 19

                mask - 4 - 100
                i - 0
                1 << i - 001
                100 & 001 = 0
                i - 1
                1 << i - 010
                100 & 010 = 0
                i - 2
                1 << i - 100
                100 & 100 = 100
                100 ^ 100 = 000
                sum[0] = 0
                a[2] = 8
                s[4] = 0 + 8 = 8
                */
                sum[mask] = sum[mask ^ (1 << i)] + a[i];
                break;
            }
        }
    }
    cout << "Dynamic:" << endl;
    out();
}

int main()
{
    solutionBruteForce();

    solutionDynamic();

    return 0;
};