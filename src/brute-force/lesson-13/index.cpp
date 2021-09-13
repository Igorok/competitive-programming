#include <fstream>
#include <vector>

using namespace std;

ifstream cin("input.txt");
ofstream cout("output.txt");

int n;
vector<int> a;
vector<bool> used;

void out()
{
    for (int i = 0; i < n; i++)
    {
        if (i)
            cout << " ";
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
    for (int i = 1; i <= n; i++)
    {
        if (used[i])
        {
            continue;
        }
        a[idx] = i;
        used[i] = true;

        rec(idx + 1);
        used[i] = false;
    }
}

int main()
{
    cin >> n;
    a = vector<int>(n);
    used = vector<bool>(n + 1, false);
    rec(0);

    return 0;
}
