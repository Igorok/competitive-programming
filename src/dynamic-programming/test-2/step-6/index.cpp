/*
Наибольшая общая подпоследовательность. Даны две последовательности чисел. Нужно найти их наибольшую общую подпоследовательность.

Входные данные:
Первые две строки содержат описание первой последовательности. В первой строке дано количество элементов последовательности, во второй строке через пробел заданы ее элементы. В следующих двух строках аналогично задана вторая последовательность.

Выходные данные:
Выведите одно целое число - длину наибольшей общей подпоследовательности.

Пример входных данных:
7
3 2 4 2 1 7 6
9
4 2 5 3 1 6 5 2 3

Пример выходных данных:
4

Наибольшая общая подпоследовательность для примера: 4 2 1 6.
*/

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>

using namespace std;

ifstream cin("seq2.in");
ofstream cout("output.txt");

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

struct SeqManager
{
    vector<int> a;
    vector<int> b;
    vector<vector<int>> d;

    SeqManager(vector<vector<int>> data)
    {
        a = data[1];
        b = data[3];

        for (int i = 0; i < a.size(); i++)
        {
            d.push_back(vector<int>(b.size()));
        }
    }

    /*
    - 4 2 5 3 1 6 5 2 3
    3 0 0 0 1 1 1 1 1 1
    2 0 1 1 1 1 1 1 2 2
    4 1 1 1 1 1 1 1 2 2
    2 1 2 2 2 2 2 2 2 2
    1 1 2 2 2 3 3 3 3 3
    7 1 2 2 2 3 3 3 3 3
    6 1 2 2 2 3 4 4 4 4
    */
    void calculate()
    {
        for (int i = 0; i < a.size(); i++)
        {
            for (int j = 0; j < b.size(); j++)
            {
                int prevI = 0;
                int prevJ = 0;
                int prevIJ = 0;

                if (i > 0)
                {
                    prevI = d[i - 1][j];
                }
                if (j > 0)
                {
                    prevJ = d[i][j - 1];
                }
                if (i > 0 && j > 0)
                {
                    prevIJ = d[i - 1][j - 1];
                }

                d[i][j] = prevI;
                if (prevJ > d[i][j])
                {
                    d[i][j] = prevJ;
                }
                if (a[i] == b[j] && prevIJ + 1 > d[i][j])
                {
                    d[i][j] = prevIJ + 1;
                }
            }
        }
    }

    void out()
    {
        cout << "Sum: " << d[a.size() - 1][b.size() - 1] << endl;
    }
};

int main()
{
    vector<vector<int>> data = readFile();
    SeqManager sm = SeqManager(data);
    sm.calculate();
    sm.out();

    return 0;
};