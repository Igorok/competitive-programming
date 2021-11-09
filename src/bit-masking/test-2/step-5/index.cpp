/*
Traveling Salesman Problem:
formula from brute force:
g(i, s) = min(w[i][j] + g(j, s - j));
g(a, {b, c, d}) = min(w[a][b] + g(b, {c, d}));

https://www.youtube.com/watch?v=hh-uFQ-MGfw
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
ifstream cin("salesman2.in");

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

struct SalesManager
{

    vector<vector<int>> d;
    vector<vector<int>> r;
    vector<int> path;
    vector<vector<int>> a;
    int n;
    int inf;

    SalesManager(vector<vector<int>> data)
    {
        n = data[0][0];
        for (int i = 1; i < data.size(); i++)
        {
            a.push_back(data[i]);
        }

        inf = a[0][0];
        for (int i = 0; i < n; i++)
        {
            if (a[0][i] > inf)
            {
                inf = a[0][i];
            }
        }
        inf = inf * (n + 1);

        d = vector<vector<int>>((1 << n), vector<int>(n, inf));
        r = vector<vector<int>>((1 << n), vector<int>(n, -1));
    }

    /*
    Состояние динамики - список городов из которых выезжает торговец, и список посещенных городов.
    Будем считать что в список посещенных городов уже расчитан оптимально.
    */
    void calculate()
    {
        d[0][0] = 0;
        for (int mask = 0; mask < (1 << n); mask++)
        {
            for (int i = 0; i < n; i++)
            {
                if (d[mask][i] == inf)
                {
                    continue;
                }

                for (int j = 0; j < n; j++)
                {
                    if (mask & (1 << j))
                    {
                        continue;
                    }
                    int newMask = mask | (1 << j);

                    if (d[newMask][j] > d[mask][i] + a[i][j])
                    {
                        d[newMask][j] = d[mask][i] + a[i][j];

                        r[newMask][j] = i;
                    }
                }
            }
        }
    }

    /*
    К сожалению, ответ неверный. Советуем обратиться к лекции 4.4, в которой разбиралось решение задачи коммивояжера динамикой по битовым маскам. Восстановление сертификата в задачах на динамическое программирование разбиралось в лекциях 3.2 и 3.4.
    */
    void outPath(int mask, int ind)
    {
        if (r[mask][ind] == 0)
        {
            int control = 0;
            int prev = 0;

            cout << "0 ";
            if (path[0] < path[path.size() - 1])
            {
                for (int i = 0; i < path.size(); i++)
                {
                    control += a[prev][path[i]];
                    prev = path[i];
                    cout << path[i] << " ";
                }
            }
            else
            {
                for (int i = path.size() - 1; i >= 0; i--)
                {
                    control += a[prev][path[i]];
                    prev = path[i];
                    cout << path[i] << " ";
                }
            }

            cout << endl;
            cout << "Control: " << control + a[prev][0];

            return;
        }

        path.push_back(r[mask][ind]);

        int newMask = mask ^ (1 << ind);
        int newInd = r[mask][ind];

        outPath(newMask, newInd);
    }

    void out()
    {
        cout << "Min path: " << d[(1 << n) - 1][0] << endl;
        /*
        cout << "d:" << endl;

        for (int i = 0; i < (1 << n); i++)
        {
            cout << bitset<16>(i).to_string();
            for (int j = 0; j < n; j++)
            {
                cout << " ";
                if (d[i][j] == inf)
                {
                    cout << "i";
                }
                else
                {
                    cout << d[i][j];
                }
            }
            cout << endl;
        }

        cout << "r:" << endl;
        for (int i = 0; i < (1 << n); i++)
        {
            cout << bitset<16>(i).to_string() << " ";
            for (int j = 0; j < n; j++)
            {
                cout << " ";
                if (r[i][j] == -1)
                {
                    cout << "i";
                }
                else
                {
                    cout << r[i][j];
                }
            }
            cout << endl;
        }
        */
        outPath((1 << n) - 1, 0);
    }
};

int main()
{
    vector<vector<int>> data = readFile();
    SalesManager sm = SalesManager(data);
    sm.calculate();
    sm.out();

    return 0;
};
