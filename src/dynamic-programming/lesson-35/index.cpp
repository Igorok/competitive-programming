/*
Задача о рюкзаке:
Имеется n предметов, для которых известны веса w i и стоимости c[i], i = 1, ..., n. Рюкзак вмещает вес не более W . Нужно набрать в него предметы максимальной суммарной стоимости.

Предположим, что мы можем использовать из n предметов только первые i (с индексами от 1 до i) и имеем рюкзак вместимости j, 0 <= i <= n, 0 <= j <= W.
Для каждой пары (i, j) будем считать величину d[i][j] — максимальную суммарную стоимость, которую можно набрать, если разрешается использовать только первые i предметов и рюкзак имеет вместимость j. Состоянием динамики будет пара чисел (i, j).

*/

/*
c= [10,20,30],w= [2,5,10],W= 12.

c/w
4, 5, 3

weight - 2 5, price - 10 + 20 = 30
weight - 2, 10, price - 10 + 30 = 40

*/

#include <vector>
#include <fstream>

using namespace std;

ofstream cout("output.txt");

struct BagManager
{
    int W;
    vector<int> w;
    vector<int> c;
    int n;
    vector<vector<int>> d;

    BagManager(int weightLimit, vector<int> weightList, vector<int> costList)
    {
        W = weightLimit;
        w = weightList;
        n = weightList.size();
        c = costList;
    }

    void fillBag()
    {

        d.push_back(vector<int>(W + 1, 0));
        // limit of stuff
        for (int i = 1; i < n; i++)
        {
            d.push_back(vector<int>(W + 1, 0));
            // limit of weight for bag
            for (int j = 0; j <= W; j++)
            {
                // set value from previous stuff
                d[i][j] = d[i - 1][j];
                /*
                j - w[i] - difference between weight limit and weight of thing
                d[i - 1][j - w[i]] - value for one thing less, and weight less by current thing
                */
                if (j - w[i] >= 0)
                {
                    // find max value for current thing + value from remaining weight
                    d[i][j] = max(d[i][j], d[i - 1][j - w[i]] + c[i]);
                }
            }
        }
    }

    /*
    vector<int> c{10, 20, 30};
    vector<int> w{2, 5, 10};
    int W = 12;

    1  2  3  4  5  6  7  8  9  10 11 12
    0  10 10 10 10 10 10 10 10 10 10 10
    0  10 10 10 20 20 30 30 30 30 30 30
    0  10 10 10 20 20 30 30 30 30 30 40
    */
    void fillBag1()
    {
        for (int i = 0; i < n; i++)
        {
            d.push_back(vector<int>(W + 1, 0));
            for (int j = 0; j <= W; j++)
            {
                int previousThingCost = 0;
                if (i != 0)
                {
                    previousThingCost = d[i - 1][j];
                }

                int thingWeight = w[i];
                int thingCost = c[i];
                int freeWeight = j - thingWeight;

                d[i][j] = previousThingCost;

                // can we put thing i in bag?
                if (freeWeight >= 0)
                {
                    int freeSpaceCost = 0;
                    // validation for first stuff
                    if (i != 0)
                    {
                        // get cost of free space, if we can put thing in bag
                        freeSpaceCost = d[i - 1][freeWeight];
                    }

                    // compare cost of thing and free place with cost of previous thing
                    if (thingCost + freeSpaceCost > previousThingCost)
                    {
                        d[i][j] = thingCost + freeSpaceCost;
                    }
                }
            }
        }
    }

    void fillBagForward()
    {
        d.push_back(vector<int>(W + 1, 0));
        for (int i = 0; i < n; i++)
        {
            d.push_back(vector<int>(W + 1, 0));
            for (int j = 0; j <= W; j++)
            {
                if (j + w[i + 1] <= W)
                {
                    d[i + 1][j + w[i + 1]] = max(d[i + 1][j + w[i + 1]], d[i][j] + c[i + 1]);
                }
                d[i + 1][j] = max(d[i + 1][j], d[i][j]);
            }
        }
    }
};

int main()
{
    vector<int> c{0, 30, 20, 10};
    vector<int> w{0, 10, 5, 2};
    int W = 12;

    BagManager bm1 = BagManager(W, w, c);
    bm1.fillBag();

    BagManager bm2 = BagManager(W, w, c);
    bm2.fillBagForward();

    // c = vector<int>{30, 20, 10};
    // w = vector<int>{10, 5, 2};
    c = vector<int>{10, 20, 30};
    w = vector<int>{2, 5, 10};
    BagManager bm3 = BagManager(W, w, c);
    bm3.fillBag1();

    return 0;
};