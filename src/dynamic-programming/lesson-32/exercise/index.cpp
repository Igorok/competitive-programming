
#include <vector>
#include <fstream>

using namespace std;

ofstream cout("output.txt");

vector<vector<int>> a{
    {1, 4, 1, 2, 3},
    {2, 3, 2, 1, 4},
    {1, 1, 1, 2, 4},
    {2, 5, 1, 7, 1},
};

struct Bug
{
    vector<vector<int>> fields;
    vector<vector<int>> summarized;
    int n;
    int m;

    Bug(vector<vector<int>> f)
    {
        fields = f;

        n = fields.size();
        m = fields[0].size();

        for (int i = 0; i < n; i++)
        {
            summarized.push_back(vector<int>(m, 0));
        }
    }

    void walking()
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                summarized[i][j] = fields[i][j];
                if (i > 0 && summarized[i - 1][j] + fields[i][j] > summarized[i][j])
                {
                    summarized[i][j] = summarized[i - 1][j] + fields[i][j];
                }

                if (j > 0 && summarized[i][j - 1] + fields[i][j] > summarized[i][j])
                {
                    summarized[i][j] = summarized[i][j - 1] + fields[i][j];
                }
            }
        }
        cout << summarized[n - 1][m - 1] << endl;

        out();

        outWay(n - 1, m - 1);
        cout << endl;
    }

    void outWay(int i, int j)
    {
        if (i == 0 && j == 0)
        {
            return;
        }

        if (i == 0)
        {
            cout << "R";
            return outWay(i, j - 1);
        }
        if (j == 0)
        {
            cout << "D";
            return outWay(i - 1, j);
        }

        if (summarized[i - 1][j] > summarized[i][j - 1])
        {
            outWay(i - 1, j);
            cout << "D";
        }
        else
        {
            outWay(i, j - 1);
            cout << "R";
        }
    }

    void out()
    {
        cout << "summarized" << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (j != 0)
                {
                    cout << " ";
                }
                cout << summarized[i][j];
            }
            cout << endl;
        }
    }
};

int main()
{
    Bug bug = Bug(a);
    bug.walking();

    return 0;
};