/*
Наибольшая возрастающая подпоследовательность. Дана последовательность целых чисел a[1], a[2], ..., a[n]. Нужно найти длину ее наибольшей возрастающей подпоследовательности (НВП), т.е. подпоследовательности наибольшей длины, числа в которой идут в порядке возрастания.

Входные данные:
В первой строке задано натуральное число nn - длина последовательности. Во второй строке содержатся элементы последовательности через пробел. Все числа в последовательности различны.

Выходные данные:
Выведите целое число - длину НВП.

Пример входных данных:
5
7 1 3 2 4

Пример выходных данных:
3
*/

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

ifstream cin("lis.in");
ofstream cout("output.txt");

struct Subsequence
{
    vector<int> a;
    vector<int> d;
    vector<int> r;
    vector<long long> c;

    Subsequence(vector<int> _a)
    {
        a = _a;
        d = vector<int>(a.size(), 1);
        r = vector<int>(a.size(), -1);
        c = vector<long long>(a.size(), 0);
    }
    void _calculate()
    {
        int ans = 0;
        long long qnt = 0;
        for (int i = 0; i < a.size(); i++)
        {
            d[i] = 1;
            c[i] = 1;
            for (int j = 0; j < i; j++)
                if (a[j] < a[i])
                {
                    if (d[j] + 1 > d[i])
                    {
                        d[i] = d[j] + 1;
                        c[i] = c[j];
                    }
                    else if (d[j] + 1 == d[i])
                    {
                        c[i] += c[j];
                    }
                }
            if (d[i] > ans)
            {
                ans = d[i];
                qnt = c[i];
            }
            else if (d[i] == ans)
                qnt += c[i];
        }
        cout << qnt << endl;
    }
    /*
    1 10 5 6 4
    1 2  2 3 2
    - -  - - -
    */
    void calculate()
    {
        for (int i = 0; i < a.size(); i++)
        {
            for (int j = i; j >= 0; j--)
            {
                int prev = a[j];
                int curr = a[i];

                if (prev < curr && d[i] < d[j] + 1)
                {
                    d[i] = d[j] + 1;
                    r[i] = j;
                }
            }

            for (int j = 0; j < i; j++)
            {
                /*
                3 2 1 4 6 5 7
                1 1 1 2 3 3 4
                1 1 1 4 1 1 1
                0 0 0 3 3 3 6

                3 4 6 7
                3 4 5 7
                2 4 6 7
                2 4 5 7
                1 4 6 7
                1 4 5 7

                2 16 12 1 8 15 14 11 9 5 10 7 3 4 6 13
                1 2  2  1 2  3  3  3 3 2 4  3 2 3 4 5
                0 1  1  0 2  3  3  2 2 2 2  2 2 2 2 4
                2 8 9 10 13
                1 8 9 10 13
                2 3 4 6 13
                1 3 4 6 13

                */
                if (a[j] < a[i] && d[i] == d[j] + 1)
                {
                    long long val = c[j];
                    if (val == 0)
                    {
                        val = 1;
                    }
                    c[i] += val;
                }
            }
        }
    }

    void writePath(int ind)
    {
        if (ind == -1)
        {
            return;
        }
        writePath(r[ind]);
        cout << a[ind] << " ";
    }

    void out()
    {
        int maxLength = 1;
        int maxInd = d.size() - 1;
        long long maxCount = 0;

        for (int i = d.size() - 1; i >= 0; i--)
        {
            if (d[i] > maxLength)
            {
                maxLength = d[i];
                maxInd = i;
            }
        }
        for (int i = 0; i < d.size(); i++)
        {
            if (d[i] == maxLength)
            {
                maxCount += c[i];
            }
        }

        /*
        cout << "d: ";
        for (int i = 0; i < d.size(); i++)
        {
            cout << d[i] << " ";
        }
        cout << endl;

        cout << "r: ";
        for (int i = 0; i < r.size(); i++)
        {
            cout << r[i] << " ";
        }
        cout << endl;

        cout << "c: ";
        for (int i = 0; i < c.size(); i++)
        {
            cout << c[i] << endl;
        }
        cout << endl;
        */

        cout << "Length: " << maxLength << " Last id: " << maxInd
             << " Max count: " << maxCount << endl;

        writePath(maxInd);
    }
};

vector<vector<int>>
readFile()
{
    vector<vector<int>> filea;
    string line;
    for (string line; getline(cin, line);)
    {
        stringstream ss(line);
        istream_iterator<int> begin(ss);
        istream_iterator<int> end;
        vector<int> vstrings(begin, end);
        filea.push_back(vstrings);
    }

    return filea;
};

int main()
{
    vector<vector<int>> a = readFile();
    Subsequence sb = Subsequence(a[1]);
    sb.calculate();
    sb.out();

    return 0;
};

/*
2724495360
1362247680
*/