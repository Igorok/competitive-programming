/*
Задача о рюкзаке. Вор пробрался на склад, на котором есть n предметов. Для каждого предмета известны его вес w[i]​ и стоимость c[i]. У вора есть рюкзак, который вмещает суммарный вес не более W. Помогите вору набрать в рюкзак предметы максимальной суммарной стоимости.

Входные данные:
В первой строке содержатся два целых числа - n и W. Следующие n строк содержат описания предметов, каждый предмет задан в отдельной строке. Предмет описывается двумя натуральными числами - весом w[i] и стоимостью c[i].

Выходные данные:
В первой строке выведите максимальную суммарную стоимость.

Пример входных данных:
3 12
2 10
5 20
10 30

Пример выходных данных:
40

В качестве ответа введите максимальную суммарную стоимость предметов, помещающихся в рюкзак, для теста rucksack.in. Максимальная суммарная стоимость для примера из условия равна 40.
*/

#include <vector>
#include <functional>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

ifstream cin("rucksack.in");
ofstream cout("output.txt");

struct Thing
{
    int weight;
    int cost;
    int id;

    Thing(int _id, vector<int> t)
    {
        id = _id;
        weight = t[0];
        cost = t[1];
    }

    bool operator<(const Thing &t)
    {
        return id < t.id;
    }
};

struct BagManager
{
    int n;
    int W;
    vector<Thing> things;
    vector<vector<long long>> d;
    vector<int> r;
    vector<Thing> bag;

    BagManager(vector<vector<int>> data)
    {
        n = data[0][0];
        W = data[0][1];
        r = vector<int>(W + 1, -1);

        for (int i = 1; i < data.size(); i++)
        {
            things.push_back(Thing(i, data[i]));

            d.push_back(vector<long long>(W + 1, 0));
        }
    }

    /*
    3 12

    2 10
    5 20
    10 30

       1  2  3  4  5  6  7  8  9  10 11 12
    2  0  10 10 10 10 10 10 10 10 10 10 10
    5  0  10 10 10 20 20 30 30 30 30 30 30
    10 0  10 10 10 20 20 30 30 30 30 30 40
    */
    void calculate()
    {
        int lastWeight = -1;
        int maxPrice = 0;
        // calculation of price for every kilo
        for (int i = 0; i < n; i++)
        {
            // check every product
            for (int j = 0; j <= W; j++)
            {
                // set default value for kilo
                d[i][j] = 0;
                if (i > 0)
                {
                    d[i][j] = d[i - 1][j];
                }
                if (j > 0 && d[i][j - 1] > d[i][j])
                {
                    d[i][j] = d[i][j - 1];
                }

                // compare previous value with price of the thing and price of difference
                int diffWeight = j - things[i].weight;
                if (diffWeight >= 0)
                {
                    long long diffCost = 0;
                    if (diffWeight > 0 && i > 0)
                    {
                        diffCost = d[i - 1][diffWeight];
                    }

                    long long newCost = (long long)things[i].cost + diffCost;
                    if (newCost > d[i][j])
                    {
                        d[i][j] = newCost;
                        r[j] = i;
                        if (newCost > maxPrice)
                        {
                            maxPrice = newCost;
                            lastWeight = j;
                        }
                    }
                }
            }
        }

        out();
        outWay(lastWeight);

        int control = 0;
        sort(bag.begin(), bag.end());
        for (int i = 0; i < bag.size(); i++)
        {
            cout << bag[i].id << " ";
            control += bag[i].cost;
        }
        cout << endl
             << "Control: " << control << endl;
    }

    void out()
    {
        cout << "Total: " << d[n - 1][W] << endl;
    }

    void outWay(int i)
    {
        if (i < 0)
        {
            return;
        }
        if (r[i] == -1)
        {
            return outWay(i - 1);
        }

        Thing t = things[r[i]];
        bag.push_back(t);
        outWay(i - t.weight);
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
    vector<vector<int>> data = readFile();
    BagManager bm = BagManager(data);
    bm.calculate();

    return 0;
};
