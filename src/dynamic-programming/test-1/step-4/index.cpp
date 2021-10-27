/*
Задача про жучка. Имеется прямоугольное поле размера n×m. Поле разделено на единичные клетки. В левой верхней клетке сидит жучок. Он может перемещаться по полю ходами вправо или вниз на одну клетку. Для каждой клетки задано целое положительное число - количество бонусов, которое получит жучок при проходе через эту клетку. Нужно добраться в правую нижнюю клетку, собрав как можно больше бонусов. Бонусы в начальной и конечной клетках жучок тоже собирает.

Входные данные:
В первой строке даны два натуральных числа n и m - размеры поля. Следующие n строк содержат по m натуральных чисел каждая - количества бонусов a[i][j].

Выходные данные:
В первой строке выведите максимальное количество бонусов, которое может собрать жучок. Во второй строке выведите путь жучка: строку из символов ‘R’ и ‘D’. Символ ‘R’ означает ход вправо, символ ‘D’ - вниз.

Пример входных данных:
3 4
5 3 2 2
2 1 7 3
4 3 1 2

Пример выходных данных:
22
RRDRD

Введите максимальное количество бонусов, которое соберет жучок, для теста из файла bug.in.
*/

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

ifstream cin("bug2.in");
ofstream cout("output.txt");

struct BugTravel
{
    vector<vector<int>> d;
    vector<vector<int>> p;
    vector<vector<int>> fields;
    int n;
    int m;
    string path;

    BugTravel(vector<vector<int>> f)
    {
        fields = f;
        n = fields.size();
        m = fields[0].size();
        for (int i = 0; i < n; i++)
        {
            d.push_back(vector<int>(m, 0));
            p.push_back(vector<int>(m, 0));
        }
    }

    void travel()
    {
        d[0][0] = fields[0][0];
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (i != n - 1)
                {
                    if (d[i + 1][j] < d[i][j] + fields[i + 1][j])
                    {
                        d[i + 1][j] = d[i][j] + fields[i + 1][j];
                        p[i + 1][j] = 0;
                    }
                }
                if (j != m - 1)
                {
                    if (d[i][j + 1] < d[i][j] + fields[i][j + 1])
                    {

                        d[i][j + 1] = d[i][j] + fields[i][j + 1];
                        p[i][j + 1] = 1;
                    }
                }
            }
        }

        savePath(n - 1, m - 1);

        cout << d[n - 1][m - 1] << endl;
        cout << path << endl;
    }

    void savePath(int i, int j)
    {
        if (i == 0 && j == 0)
        {
            return;
        }
        if (p[i][j] == 1)
        {
            savePath(i, j - 1);
            path += "R";
        }
        else
        {
            savePath(i - 1, j);
            path += "D";
        }
    }
};

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
    fileData.erase(fileData.begin());

    return fileData;
}

int main()
{
    vector<vector<int>> data = readFile();
    BugTravel bt = BugTravel(data);
    bt.travel();

    return 0;
};