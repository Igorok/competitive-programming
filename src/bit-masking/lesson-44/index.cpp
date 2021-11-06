/*
Задача коммивояжёра:
Коммивояжёр хочет объехать n городов и вернуться в исходный город. Каждые два города соединены между собой дорогами. Известны длины всех дорог. Нужно найти путь коммивояжера минимальной длины.
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

// 10
vector<vector<int>> a{
    {0, 1, 4, 6},
    {1, 0, 5, 2},
    {4, 5, 0, 3},
    {6, 2, 3, 0},
};
int n = a.size();
int INF = 1000;

vector<vector<int>> d((1 << n), vector<int>(n, INF));

void calculateBit()
{

    // путь из 0 в 0 равен 0
    d[0][0] = 0;

    // Далее будем перебирать состояния и делать из них переходы «вперёд»:
    for (int mask = 0; mask < (1 << n); mask++)
    {
        for (int i = 0; i < n; i++)
        {
            /*
            Проверим, если для данного состояния (mask, i) значение d равно «бесконечности», то такое состояние недопустимо, и мы пропускаем его:
            */
            if (d[mask][i] == INF)
            {
                cout << "d[" << bitset<8>(mask).to_string() << "][" << i << "] == INF" << endl
                     << "continue;" << endl;
                continue;
            }

            /*
            Иначе нужно перебрать переходы. В цикле по j перебираем номер города, в который поедет коммивояжёр из города i:
            */
            for (int j = 0; j < n; j++)
            {
                if ((mask & (1 << j)))
                {
                    cout << "mask & (1 << j) " << bitset<8>(mask).to_string() << " & 1 << " << j << endl
                         << "continue;" << endl;
                }
                if (!(mask & (1 << j)))
                {
                    cout << "d[" << bitset<8>(mask).to_string() << " ^ (1 << " << j << ")][" << j << "] = "
                         << "min(d[" << bitset<8>(mask ^ (1 << j)).to_string() << "][" << j << "], "
                         << "d[" << bitset<8>(mask).to_string() << "][" << i << "] + a[" << i << "][" << j << "])"
                         << " = min(" << d[mask ^ (1 << j)][j] << ", " << d[mask][i] + a[i][j]
                         << ")" << endl;

                    /*
                    Сформируем новую маску посещённых городов, которая образуется после добавления j-го города: mask ^ (1 << j). Для добавления к маске j-го бита можно вместо операции XOR использовать OR. Далее обновляется значение d для нового состояния:
                    */
                    d[mask ^ (1 << j)][j] = min(d[mask ^ (1 << j)][j], d[mask][i] + a[i][j]);
                }
            }
        }
    }

    cout << d[(1 << n) - 1][0] << endl;
};

void calculate(){};

void out()
{
    for (int i = 0; i < d.size(); i++)
    {
        string mask = bitset<8>(i).to_string();
        cout << mask << " ";

        for (int j = 0; j < d[j].size(); j++)
        {
            if (d[i][j] == INF)
            {
                cout << " I"
                     << " ";
            }
            else
            {
                if (d[i][j] < 10)
                {
                    cout << " ";
                }
                cout << d[i][j] << " ";
            }
        }
        cout << endl;
    };
}

int main()
{
    calculateBit();

    out();

    return 0;
};

/*
0 1 4 6
1 0 5 2
4 5 0 3
6 2 3 0

          0  1  2  3
00000000  0  I  I  I
00000001  0  I  I  I
00000010  I  1  I  I
00000011  2  1  I  I
00000100  I  I  4  I
00000101  8  I  4  I
00000110  I  9  6  I
00000111 10  9  6  I
00001000  I  I  I  6
00001001 12  I  I  6
00001010  I  8  I  3
00001011  9  8  I  3
00001100  I  I  9  7
00001101 13  I  9  7
00001110  I  9  6  9
00001111 10  9  6  9
*/