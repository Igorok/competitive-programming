/*
Имеется поле n*m, разбитое на единичные клетки, и qq запросов. В клетках записаны целые числа. Каждый запрос - это некоторый прямоугольник со сторонами, параллельными осям координат. Нужно для каждого прямоугольника определить сумму чисел в нем.

Входные данные:
В первой строке заданы два целых числа n и m - размеры поля. Следующие n строк содержат описание поля. В каждой строке заданы m чисел, разделенных одиночными пробелами. В следующей строке задано число q - количество запросов. В следующих q строках заданы запросы. Каждый запрос описывается четверкой чисел x[1], x[2], y[1], y[2], разделенных пробелами (1 <= x1 <= x2 <= n, 1 <= y1 <= y2 <= m. В рассматриваемый прямоугольник входят клетки (x, y) с номерами строк x и номерами столбцов y, для которых выполняются неравенства x1 <= x <= x2, y1 <= y <= y2.

Выходные данные:
Выведите одно целое число - сумму ответов на запросы.

Пример входных данных:
5 6
1 3 7 -1 7 11
2 6 5 1 1 3
-3 0 2 0 3 8
5 1 3 1 4 7
6 1 -2 2 1 0
3
2 3 2 3
1 1 5 6
3 5 3 6

Пример выходных данных:
60

Ответы на запросы для примера: 13, 18 и 29.

Введите ответ для теста из файла rectangle.in.
*/

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

ifstream cin("rectangle.in");
ofstream cout("output.txt");

struct RectagleManager
{
    int n;
    int m;
    vector<vector<long long>> a;
    vector<vector<long long>> r;
    vector<vector<long long>> sumVector;
    string answers;

    RectagleManager(vector<vector<long long>> data)
    {
        int check;
        for (int i = 0; i < data.size(); i++)
        {
            vector<long long> row = data[i];
            if (row.size() == 2)
            {
                check = 0;
                n = row[0];
                m = row[1];
                continue;
            }
            else if (row.size() == 1)
            {
                check = 1;
                continue;
            }

            if (check == 0)
            {
                a.push_back(row);
            }
            else
            {
                r.push_back(row);
            }
        }
    }

    void calculateSum()
    {
        for (int i = 0; i < n; i++)
        {
            sumVector.push_back(vector<long long>(m, 0));
            for (int j = 0; j < m; j++)
            {
                long long prevI = 0;
                long long prevJ = 0;
                long long prevIJ = 0;
                if (i > 0)
                {
                    prevI = sumVector[i - 1][j];
                }
                if (j > 0)
                {
                    prevJ = sumVector[i][j - 1];
                }
                if (i > 0 && j > 0)
                {
                    prevIJ = sumVector[i - 1][j - 1];
                }

                sumVector[i][j] = a[i][j] + prevI + prevJ - prevIJ;
            }
        }
    }

    void calculateSimple()
    {
        cout << "Simple:" << endl;

        for (int i = 0; i < r.size(); i++)
        {
            int x1 = r[i][0] - 1;
            int x2 = r[i][1] - 1;
            int y1 = r[i][2] - 1;
            int y2 = r[i][3] - 1;
            long long sum = 0;

            cout << endl;
            cout << x1 << " " << x2 << " " << y1 << " " << y2 << ":" << endl;
            for (int x = x1; x <= x2; x++)
            {
                for (int y = y1; y <= y2; y++)
                {
                    sum += a[x][y];
                    cout << a[x][y] << " ";
                }
                cout << endl;
            }
            cout << "sum:" << sum << endl;
        }
    }

    void calculateDynamic()
    {
        long long ans = 0;
        for (int i = 0; i < r.size(); i++)
        {
            int x1 = r[i][0] - 1;
            int x2 = r[i][1] - 1;
            int y1 = r[i][2] - 1;
            int y2 = r[i][3] - 1;

            // cout << endl;
            // cout << x1 << " " << x2 << " " << y1 << " " << y2 << ":" << endl;

            long long horSum = 0;
            long long vertSum = 0;
            long long commSum = 0;
            if (x1 > 0)
            {
                horSum = sumVector[x1 - 1][y2];
            }
            if (y1 > 0)
            {
                vertSum = sumVector[x2][y1 - 1];
            }
            if (x1 > 0 && y1 > 0)
            {
                commSum = sumVector[x1 - 1][y1 - 1];
            }
            long long sum = sumVector[x2][y2] - horSum - vertSum + commSum;
            ans += sum;

            // cout << sum << endl;
        }
        cout << "Dynamic sum: " << ans << endl;
    }

    void outData()
    {
        cout << "a: " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << a[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl;
        cout << "sumVector: " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << sumVector[i][j] << " ";
            }
            cout << endl;
        }
    }
};

vector<vector<long long>>
readFile()
{
    vector<vector<long long>> filea;
    string line;
    for (string line; getline(cin, line);)
    {
        stringstream ss(line);
        istream_iterator<long long> begin(ss);
        istream_iterator<long long> end;
        vector<long long> vstrings(begin, end);
        filea.push_back(vstrings);
    }

    return filea;
};

int main()
{
    vector<vector<long long>> data = readFile();
    RectagleManager rm = RectagleManager(data);
    rm.calculateSum();
    // rm.outData();
    // rm.calculateSimple();
    rm.calculateDynamic();

    return 0;
};
