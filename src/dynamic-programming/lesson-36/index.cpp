/*
Наибольшая общая подпоследовательность:
Даны две последовательности. Нужно найти их наибольшую общую подпоследовательность, то есть совпадающую подпоследовательность наибольшей длины.
*/

#include <vector>
#include <fstream>

using namespace std;

vector<int> a{3, 2, 4, 2, 1, 7, 6};
vector<int> b{4, 2, 5, 3, 1, 6, 5, 2, 3};

// ofstream cout("output.txt");

struct SequenceManager
{
    vector<int> a;
    vector<int> b;
    vector<vector<int>> d;

    vector<int> pi;
    vector<int> pj;

    SequenceManager(vector<int> arr1, vector<int> arr2)
    {
        a = arr1;
        b = arr2;

        d.push_back(vector<int>(b.size() + 1, 0));
        for (int i = 0; i < a.size(); i++)
        {
            d.push_back(vector<int>(b.size() + 1, 0));
        }

        pi = vector<int>(a.size(), -1);
        pj = vector<int>(b.size(), -1);
    }

    /*
    vector<int> a{3, 2, 4, 2, 1, 7, 6};
    vector<int> b{4, 2, 5, 3, 1, 6, 5, 2, 3};

       0  4  2  5  3  1  6  5  2  3
    0  0  0  0  0  0  0  0  0  0  0
    3  0  0  0  0  1  1  1  1  1  1
    2  0  0  1  1  1  1  1  1  2  2
    4  0  1  1  1  1  1  1  1  2  2
    2  0  1  2  2  2  2  2  2  2  2
    1  0  1  2  2  2  3  3  3  3  3
    7  0  1  2  2  2  3  3  3  3  3
    6  0  1  2  2  2  3  4  4  4  4

    */
    void compare()
    {
        int as = a.size();
        int bs = b.size();

        for (int i = 1; i <= a.size(); i++)
        {
            for (int j = 1; j <= b.size(); j++)
            {
                d[i][j] = max(d[i - 1][j], d[i][j - 1]);
                if (a[i - 1] == b[j - 1])
                {
                    if (d[i - 1][j - 1] + 1 > d[i][j])
                    {
                        d[i][j] = d[i - 1][j - 1] + 1;

                        pi[i - 1] = d[i][j];
                        pj[j - 1] = d[i][j];
                    }
                }
            }
        }
    }

    void findPath()
    {
        int n = d.size();
        int m = d[0].size();

        int last = d[n - 1][m - 1];
    }
};

int subArray()
{
    vector<int> a = {1, 4, 2, 5, 6, 3, 7};
    int n = a.size();
    vector<int> d(n, 0);
    vector<int> last(n, -1);

    d[0] = 1;
    last[0] = -1; //База динамики

    for (int i = 1; i < n; ++i)
    { // Правило перехода динамики
        int max = 0;
        last[i] = -1;
        for (int k = i - 1; k >= 0; --k)
        {
            if (d[k] > max && a[k] < a[i])
            {
                max = d[k];
                last[i] = k; //Запоминаем номер предпоследнего
            }                //элемента НВП
        }
        d[i] = max + 1;
    }

    return d[n - 1];
};

int main()
{

    // a = vector<int>{1, 2, 3, 4};
    // b = vector<int>{3, 1, 4, 5, 3, 1, 2, 4};

    SequenceManager sm = SequenceManager(a, b);
    sm.compare();

    // int ans = subArray();

    return 0;
};

/*
a = vector<int>{1, 2, 3, 4};
b = vector<int>{3, 1, 4, 5, 3, 1, 2, 4};

- 3 1 4 5 3 1 2 4
1 0 1 1 1 1 1 1 1
2 0 1 1 1 1 1 2 2
3 1 1 1 1 2 2 2 2
4 1 1 2 2 2 2 2 3


- - 3 1 4 5 3 1 2 4
- - 1 2 3 4 5 6 7 8
1 1 0 1 0 0 0 1 0 0
2 2 0 0 0 0 0 0 2 0
3 3 1 0 0 0 2 0 0 0
4 4 0 0 2 0 0 0 0 3

*/