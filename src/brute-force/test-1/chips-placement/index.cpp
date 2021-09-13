#include <fstream>
#include <vector>

using namespace std;

ifstream cin("input.txt");
ofstream cout("output.txt");
int n;
int m;
vector<bool> ans;

void out()
{
    for (int i = 0; i < n; i++)
    {
        cout << string(ans[i] ? "*" : ".");
    }
    cout << endl;
}

void rec(int idx, int processed)
{
    if (idx == n)
    {
        if (processed == m)
        {
            out();
        }
        return;
    }

    if (idx == 0 || (processed != m && !ans[idx - 1]))
    {
        ans[idx] = true;
        rec(idx + 1, processed + 1);
    }

    ans[idx] = false;
    rec(idx + 1, processed);
}

int main()
{
    cin >> n >> m;
    ans = vector<bool>(n);
    rec(0, 0);
    return 0;
}
