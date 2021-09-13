#include <fstream>
#include <vector>
#include <map>

using namespace std;

ifstream cin("input.txt");
ofstream cout("output.txt");
int n;
vector<char> ans;
vector<char> brackets{'(', ')', '[', ']'};
int corrVal = 0;
int iters = 0;

int getBalance(int idx)
{
    map<char, char> mappedBrackets{
        {')', '('},
        {']', '['},
    };
    vector<char> opens{};
    int bal = 0;
    for (int i = 0; i < idx; i++)
    {
        if (ans[i] == '(' || ans[i] == '[')
        {
            opens.push_back(ans[i]);
            bal++;
            continue;
        }

        if (opens.empty())
        {
            return -1;
        }
        char mapped = mappedBrackets.find(ans[i])->second;
        char opn = opens.back();

        if (mapped != opn)
        {
            return -1;
        }
        opens.pop_back();
        bal--;
    }
    return bal;
}

void out()
{
    for (int i = 0; i < n * 2; i++)
    {
        cout << ans[i];
    }
    cout << endl;
}

void rec(int idx)
{
    iters++;
    if (corrVal > 8233)
    {
        return;
    }

    if (idx == n * 2)
    {
        if (getBalance(idx) == 0)
        {
            corrVal++;
            out();
        }
        return;
    }

    if (getBalance(idx) < 0 || getBalance(idx) > n)
    {
        return;
    }

    for (int i = 0; i < brackets.size(); i++)
    {
        ans[idx] = brackets[i];
        rec(idx + 1);
    }
};

int main()
{
    cin >> n;
    ans = vector<char>(n * 2);
    rec(0);
    return 0;
}
