/*
Биномиальные коэффициенты
Введите ответ на задачу для n = 50, k = 20.
*/
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iterator>

using namespace std;

ofstream cout("output.txt");

/*
k = 2
n = 3
c[0][n] = 1
c[n][n] = 1
c[k][n] = 3
c[k][n] = c[k-1][n-1] + c[k][n-1]

c[2][3] = c[1][2] + c[2][2] = c[0][1] + c[1][1] + 1 = 1 + 1 + 1

  0 1 2 3
0 1 1 1 1
1 - 1 2
2 - - 1

*/

void calculate()
{
    int k = 20;
    int n = 50;

    vector<vector<long long>> d(k + 1, vector<long long>(n + 1, 0));

    for (int i = 0; i <= k; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == i)
            {
                d[i][j] = 1;
                continue;
            }
            if (j < 1)
            {
                continue;
            }

            d[i][j] = d[i - 1][j - 1] + d[i][j - 1];
        }
    }

    long long ans = d[k][n];
};

int main()
{
    calculate();

    return 0;
};
