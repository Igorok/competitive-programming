
#include <vector>
#include <fstream>

using namespace std;

ofstream cout("output.txt");

int n = 10;
int ans = 0;
vector<int> solution;

void out(int idx)
{
    for (int i = 0; i < idx; i++)
    {
        if (i)
        {
            cout << " ";
        }
        cout << solution[i];
    }
    cout << endl;
};

void bruteForce(int idx, int sum)
{
    if (idx > n)
    {
        return;
    }
    if (sum == n)
    {
        out(idx);
        ans++;
        return;
    }
    solution[idx] = 1;
    bruteForce(idx + 1, sum + 1);

    solution[idx] = 2;
    bruteForce(idx + 1, sum + 2);
};

/*
for area 1 possible 1 solution
for area 2 possible 2 solutions
for area 3 possible 3 solutions
for area 4 possible 5 solutions
and after possible to see that count solutions for area n equal to
solution[n - 1] + solutions[n - 2], alike fibonacci
*/
void dynamic()
{
    vector<int> ansList = vector<int>(n - 1, 0);
    ansList[0] = 1;
    ansList[1] = 2;
    for (int i = 2; i < n; i++)
    {
        ansList[i] = ansList[i - 1] + ansList[i - 2];
    }
    ans = ansList[n - 1];
};

void bruteForceThree(int idx, int sum)
{
    if (idx > n)
    {
        return;
    }

    if (sum > n)
    {
        return;
    }

    if (sum == n)
    {
        out(idx);
        ans++;
        return;
    }
    solution[idx] = 1;
    bruteForceThree(idx + 1, sum + 1);

    solution[idx] = 3;
    bruteForceThree(idx + 1, sum + 3);
}

void dynamicThree()
{
    vector<int> ansList = vector<int>(n, 0);
    ansList[1] = 1; // |
    ansList[2] = 1; // ||
    ansList[3] = 2; // ---, |||
    // ansList[4] = 3; // ||||, |---, ---|
    // ansList[5] = 4; // |||||, ||---, |---|, ---||
    // ansList[6] = 6; // ||||||, |||---, ||---|, |---||, ---|||, ------
    // ansList[7] = 9; // |||||||, ||||---, |||---|, ||---||, |---|||, |------, ---||||, ---|---, ------|

    for (int i = 4; i <= n; i++)
    {
        ansList[i] = ansList[i - 1] + ansList[i - 3];
    }

    ans = ansList[n];
};

int main()
{
    solution = vector<int>(n, 0);
    // bruteForce(0, 0);

    // dynamic();

    bruteForceThree(0, 0);

    // dynamicThree();

    return 0;
};
