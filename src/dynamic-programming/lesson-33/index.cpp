/*
Суммы в прямоугольниках
Имеется поле n × m, разбитое на единичные клетки. В клетках записаны числа. Нам поступают запросы. Каждый запрос — это некоторый прямоугольник со сторонами, параллельными осям координат. Нужно для каждого прямоугольника определить сумму чисел в нём (см. пример на рис. 1).
*/

#include <vector>

using namespace std;

vector<vector<int>> a{
    {1, 3, 7, -1, 7, 11},
    {2, 6, 5, 1, 1, 3},
    {-3, 0, 2, 0, 3, 8},
    {5, 1, 3, 1, 4, 7},
    {6, 1 - 2, 2, 1, 0},
};

vector<int> la{1, 2, -1, 3, 1, -2};

struct LineFields
{
    vector<int> a;
    vector<int> s;

    LineFields(vector<int> a)
    {
        s.push_back(a[0]);
        for (int i = 1; i < a.size(); i++)
        {
            s.push_back(a[i] + s[i - 1]);
        }
    }

    int getSum(int i, int j)
    {
        return s[j] - s[i - 1];
    }
};

struct SquareFields
{
    vector<vector<int>> scores;
    vector<vector<int>> sum;

    /*
    1 1 1
    1 1 1
    1 1 1

    1 2 3
    2 5 9
    3 9 18

    1 2 3
    2 4 6
    3 6 9
    */
    void initializeField(int i, int j)
    {
        if (i == 0 && j == 0)
        {
            sum[i][j] = scores[i][j];
            return;
        }
        if (i == 0)
        {
            sum[i][j] = sum[i][j - 1] + scores[i][j];
            return;
        }
        if (j == 0)
        {
            sum[i][j] = sum[i - 1][j] + scores[i][j];
            return;
        }

        /*
        prev row contain sum all numbers by horizontal
        prev column contain sum all numbers by vertical
        both values contain sum of square[i-1][j-1], so sum of square[i][j] increase by this value
        */
        sum[i][j] = sum[i - 1][j] + sum[i][j - 1] + scores[i][j] - sum[i - 1][j - 1];
    }

    SquareFields(vector<vector<int>> a)
    {
        scores = a;
        for (int i = 0; i < scores.size(); i++)
        {
            sum.push_back(vector<int>(scores[i].size(), 0));

            for (int j = 0; j < scores[i].size(); j++)
            {
                initializeField(i, j);
            }
        }
    }

    int getSum(int is, int js, int ie, int je)
    {
        int totalSum = sum[ie][je];

        int horSum = (is != 0) ? sum[is - 1][je] : 0;
        int verSum = (js != 0) ? sum[ie][js - 1] : 0;
        int bothSum = (is != 0 && js != 0) ? sum[is - 1][js - 1] : 0;

        return totalSum - (horSum + verSum - bothSum);
    }
};

int main()
{
    LineFields lf = LineFields(la);
    int sl = lf.getSum(0, 2);

    SquareFields sf = SquareFields(a);
    int ss = sf.getSum(1, 1, 2, 2);

    return 0;
};
