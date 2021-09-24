#include <fstream>
#include <vector>

using namespace std;

int change(int n, vector<int> a, int s)
{
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        cnt += s / a[i];
        s = s % a[i];
    }
    return cnt;
}

int main()
{
    vector<int> a{10, 8, 6, 1};
    int s = 25;
    int n = a.size();
    int c = change(n, a, s);

    return 0;
}