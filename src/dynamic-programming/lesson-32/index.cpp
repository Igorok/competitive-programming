/*
Имеется прямоугольное поле размера n × m. Поле разделено на единичные клетки. В левой верхней клетке сидит жучок. Он может перемещаться по полю ходами вправо или вниз на одну клетку. Для каждой клетки задано целое положительное число — количество бонусов, которое получит жучок при проходе через эту клетку. Нужно добраться в правую нижнюю клетку, собрав как можно больше бонусов. Бонусы в начальной и конечной клетках жучок тоже собирает
*/
#include <vector>
#include <fstream>

using namespace std;

ofstream cout("output.txt");

vector<vector<int>> a{
    {5, 3, 2, 2},
    {2, 1, 7, 3},
    {4, 3, 1, 2},
};

struct Bug
{
    vector<vector<int>> a;
    vector<vector<int>> d;
    vector<vector<int>> p;

    Bug(vector<vector<int>> arr)
    {
        a = arr;
        for (int i = 0; i < a.size(); i++)
        {
            d.push_back(vector<int>(a[i].size(), 0));
            p.push_back(vector<int>(a[i].size(), 0));
        }
    }

    void getScores()
    {
        int n = d.size();
        int m = d[0].size();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                d[i][j] = a[i][j];
                if (i > 0 && (d[i - 1][j] + a[i][j]) > d[i][j])
                {
                    d[i][j] = d[i - 1][j] + a[i][j];
                    p[i][j] = 0;
                }
                if (j > 0 && (d[i][j - 1] + a[i][j]) > d[i][j])
                {
                    d[i][j] = d[i][j - 1] + a[i][j];
                    p[i][j] = 1;
                }
            }
        }

        cout << d[n - 1][m - 1] << endl;
        recount(n - 1, m - 1);
        cout << endl;
    };

    void recount(int i, int j)
    {
        if (i == 0 && j == 0)
        {
            return;
        }
        if (p[i][j] == 0)
        {
            recount(i - 1, j);
            cout << "D";
        }
        if (p[i][j] == 1)
        {
            recount(i, j - 1);
            cout << "R";
        }
    }

    void out()
    {
        cout << "d" << endl;
        for (int i = 0; i < d.size(); i++)
        {
            for (int j = 0; j < d[i].size(); j++)
            {
                if (j != 0)
                {
                    cout << " ";
                }
                cout << d[i][j];
            }
            cout << endl;
        }

        cout << "p" << endl;
        for (int i = 0; i < p.size(); i++)
        {
            for (int j = 0; j < p[i].size(); j++)
            {
                if (j != 0)
                {
                    cout << " ";
                }
                cout << p[i][j];
            }
            cout << endl;
        }
    };
};

int main()
{
    Bug bug = Bug(a);
    bug.getScores();
    bug.out();

    return 0;
};
