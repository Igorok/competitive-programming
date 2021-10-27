/*
Требуется набрать заданную сумму s наименьшим числом монет номиналами a[1],a[2],...,a[n]. Можно использовать любое число монет каждого номинала.

Входные данные:
В первой строке заданы два натуральных числа n и s. Следующая строка содержит n различных натуральных чисел - номиналы монет.

Выходные данные:
Выведите одно целое число - наименьшее число монет, которыми можно набрать сумму s.

Пример входных данных:
4 39
1 2 5 10

Пример выходных данных:
6
*/

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

ifstream cin("change.in");
ofstream cout("output.txt");

vector<vector<int>> readFile()
{
    vector<vector<int>> fileData;
    string line;
    for (string line; getline(cin, line);)
    {
        stringstream ss(line);
        istream_iterator<int> begin(ss);
        istream_iterator<int> end;
        vector<int> vstrings(begin, end);
        fileData.push_back(vstrings);
    }

    return fileData;
};

struct CoinTerminal
{
    vector<int> coins;
    int sum;
    vector<int> d;
    vector<int> p;
    string values;

    CoinTerminal(vector<vector<int>> data)
    {
        coins = data[1];
        sum = data[0][1];
        d = vector<int>(sum + 1, sum + 1);
        p = vector<int>(sum + 1, 0);
        d[0] = 0;
    }

    /*
    1 2 5 10
    9
       1 2 3 4 5 6 7 8 9
    1  1 1 3 4 5 6 7 8 9
    2  0 1 2 2 3 3 4 4 5
    5  0 0 0 0 1 2 2 3 3
    10 0 0 0 0 0 0 0 0 0
    */
    void calculate()
    {
        for (int i = 1; i <= sum; i++)
        {
            for (int j = 0; j < coins.size(); j++)
            {
                int diff = i - coins[j];
                if (diff >= 0 && d[i] > d[diff] + 1)
                {
                    d[i] = d[diff] + 1;
                    p[i] = coins[j];
                }
            }
        }

        getCoins(sum);

        cout << d[sum] << endl;
        cout << values << endl;
    }
    void getCoins(int s)
    {
        if (s == 0)
        {
            return;
        }
        if (s != sum)
        {
            values += " ";
        }
        values += to_string(p[s]);
        getCoins(s - p[s]);
    }
};

int main()
{
    vector<vector<int>> data = readFile();
    CoinTerminal ct = CoinTerminal(data);
    ct.calculate();

    return 0;
};