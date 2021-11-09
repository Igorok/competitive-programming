/*
Паркет:
Имеется прямоугольное поле n × m. Нужно посчитать число способов замостить его доминошками размера 1 × 2. Доминошки могут быть повёрнуты горизонтально или вертикально, но они не должны перекрываться или выходить за пределы поля.
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

void calculate()
{
    d[0][0] = 1;
    for (int i = 0; i < m; i++)
    {
        for (int mask = 0; mask < (1 << n); mask++)
        {
            for (int new_mask = 0; new_mask < (1 << n); new_mask++)
            {
                if (can(mask, new_mask))
                {
                    d[i + 1][new_mask] += d[i][mask];
                }
            }
        }
    }

    cout << d[m][0] << endl;
};

int main(){};