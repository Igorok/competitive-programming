#include <fstream>
#include <vector>

using namespace std;

ifstream cin("input.txt");
ofstream cout("output.txt");

int n;
vector<int> a;
vector<bool> used;

void out(int idx)
{
    for (int i = 0; i < idx; i++)
    {
        if (i)
        {
            cout << " + ";
        }
        cout << a[i];
    }
    cout << endl;
}

void rec(int idx, int sum, int last)
{
    if (sum == n)
    {
        out(idx);
        return;
    }
    for (int i = last; i <= n - sum; i++)
    {
        a[idx] = i;
        rec(idx + 1, sum + i, i);
    }
}

int main()
{
    cin >> n;
    a = vector<int>(n);
    rec(0, 0, 1);

    return 0;
}
