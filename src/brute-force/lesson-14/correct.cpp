#include <fstream>
#include <vector>

using namespace std;

ifstream cin("input-correct.txt");
ofstream cout("output-correct.txt");

bool correct(string line)
{
    vector<char> opens{};
    int bal = 0;
    for (int i = 0; i < line.size(); i++)
    {
        char item = line.at(i);
        if (item == '(' || item == '[')
        {
            opens.push_back(item);
            bal++;
        }

        if (item == ')')
        {
            char opn = opens.back();
            if (opn == '(')
            {
                bal--;
            }
            else
            {
                return false;
            }

            opens.pop_back();
        }

        if (item == ']')
        {
            char opn = opens.back();
            if (opn == '[')
            {
                bal--;
            }
            else
            {
                return false;
            }
            opens.pop_back();
        }
    }
    return bal == 0;
}

int main()
{
    for (string line; getline(cin, line);)
    {
        string isCor(correct(line) ? string("true") : string("false"));
        isCor = " - " + isCor;
        cout << line << isCor << endl;
    }

    return 0;
}
