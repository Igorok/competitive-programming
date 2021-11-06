#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

ofstream cout("output.txt");

/*
used
0 1 2 3 4
1 0 0 1 0

bit mask
4 3 2 1 0
0 1 0 0 1

x << y = x * 2^y;
x >> y = x / 2^y;
*/

int n = 3;

void calculate()
{
    /*
    1 << n = 1 * 2^n
    1 << 3 = 8

    1 << n - перебор всех смещений 1 бит
    mask: 0, 1, 2, 3, 4, 5, 6, 7
    0 = 000;
    1 = 001;
    2 = 010;
    3 = 011;
    4 = 100;
    5 = 101;
    6 = 110;
    7 = 111;

    первый цикл генерит все последовательности, 1 является флагом для числа
    */
    for (int mask = 0; mask < (1 << n); mask++)
    {
        for (int i = 0; i < n; i++)
        {
            /*
            1 << i
            1 << 0 = 001;
            1 << 1 = 010;
            1 << 2 = 100;

            второй цикл выводит строку, если в позиции 0, то она не выводится
            */
            if (mask & (1 << i))
            {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
    }
};

vector<int> seq = vector<int>(n + 1, 0);
void out(int id)
{
    for (int i = 1; i <= id; i++)
    {
        cout << seq[i] << " ";
    }
    cout << endl;
};

void recursion(int id, int num)
{
    if (id > n)
    {
        return;
    }

    for (int i = num; i <= n; i++)
    {
        seq[id] = i;
        out(id);

        recursion(id + 1, i + 1);
    }
};

void caclulateRecursion()
{

    cout << endl
         << "caclulate recursion" << endl;

    recursion(1, 1);
};

int main()
{
    calculate();

    caclulateRecursion();

    return 0;
};