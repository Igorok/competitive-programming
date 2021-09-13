#include <fstream>
#include <vector>

using namespace std;

ifstream cin("input.txt");
ofstream cout("output.txt");

int n, m;
vector<int> a;

void out()
{
    for (int i = 0; i < n; i++)
    {
        if (i)
        {
            cout << string(" ");
        }
        cout << a[i];
    }
    cout << endl;
}

void rec(int idx)
{
    if (idx == n)
    {
        out();
        return;
    }
    for (int i = 1; i < m + 1; i++)
    {
        a[idx] = i;
        rec(idx + 1);
    }
}

int main()
{
    cin >> n >> m;

    a = vector<int>(n);
    rec(0);

    return 0;
}