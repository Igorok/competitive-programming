#include <fstream>
#include <vector>

using namespace std;

ifstream cin("input.txt");
ofstream cout("output.txt");

int n;
vector<char> s;
vector<bool> used;

void out()
{
    for (int i = 0; i < 2 * n; i++)
    {
        cout << s[i];
    }
    cout << endl;
}

void rec(int idx, int bal)
{
    if (idx == 2 * n)
    {
        if (bal == 0)
        {
            out();
        }
        return;
    }

    s[idx] = '(';
    rec(idx + 1, bal + 1);

    if (bal == 0)
    {
        return;
    }

    s[idx] = ')';
    rec(idx + 1, bal - 1);
}

int main()
{
    cin >> n;
    s = vector<char>(2 * n);
    rec(0, 0);

    return 0;
}
