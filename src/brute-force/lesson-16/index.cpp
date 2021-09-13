#include <fstream>
#include <vector>

using namespace std;

ofstream cout("output.txt");
/*
vector<vector<int>> a{
    {
        0,
        1,
        4,
        6,
    },
    {1, 0, 5, 2},
    {4, 5, 0, 3},
    {6, 2, 3, 0},
};
*/
vector<vector<int>> a{
    {0, 41, 67, 0, 78, 5, 91, 4, 18, 67},
    {41, 0, 34, 69, 58, 45, 95, 2, 95, 99},
    {67, 34, 0, 24, 62, 81, 42, 53, 47, 35},
    {0, 69, 24, 0, 64, 27, 27, 92, 26, 94},
    {78, 58, 62, 64, 0, 61, 36, 82, 71, 3},
    {5, 45, 81, 27, 61, 0, 91, 21, 38, 11},
    {91, 95, 42, 27, 36, 91, 0, 16, 69, 22},
    {4, 2, 53, 92, 82, 21, 16, 0, 12, 33},
    {18, 95, 47, 26, 71, 38, 69, 12, 0, 73},
    {67, 99, 35, 94, 3, 11, 22, 33, 73, 0},
};

int n = a.size();
int INF = 1e3;
vector<int> p;
vector<int> minWay{};
vector<bool> used;
int ans = INF;

void walkVector()
{
    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            cout << a[i][j];
        }
        cout << endl;
    }
}

void out()
{
    for (int i = 0; i < n; i++)
    {
        if (i)
        {
            cout << " ";
        }
        cout << p[i];
    }
    cout << endl;
}

void rec(int idx, int len)
{

    int l = len + a[p[idx - 1]][0];
    if (l > ans)
    {
        return;
    }
    if (idx == n)
    {
        out();
        ans = min(ans, l);
        cout << l << endl;
        return;
    }
    for (int i = 1; i < n; i++)
    {
        if (used[i])
        {
            continue;
        }
        p[idx] = i;
        used[i] = true;
        rec(idx + 1, len + a[p[idx - 1]][i]);
        used[i] = false;
    }
}

int main()
{
    p = vector<int>(n);
    p[0] = 0;
    used = vector<bool>(n, false);

    rec(1, 0);

    cout << "ans " << ans << endl;
    return 0;
}

/*
{0, 1, 4, 6},
{1, 0, 5, 2},
{4, 5, 0, 3},
{6, 2, 3, 0},

0 1 2 3
15
1+5+3+6=15
0 1 3 2
10
1+2+3+4=10
0 2 1 3
17
4+5+2+6=17
0 2 3 1
10
4+3+2+1=10
0 3 1 2
17
6+2+5+4=17
0 3 2 1
15
6+3+5+1=15
*/
