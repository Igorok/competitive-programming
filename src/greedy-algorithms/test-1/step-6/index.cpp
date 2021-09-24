#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

ifstream cin("request2.in");

struct Request
{
    int start;
    int end;

    bool operator<(const Request &r) const
    {
        return end < r.end;
    }
    bool operator>(const Request &r) const
    {
        return end > r.end;
    }

    Request(int s, int e)
    {
        start = s;
        end = e;
    }
};

vector<Request>
readFile()
{
    vector<Request> requests;
    string line;
    for (string line; getline(cin, line);)
    {
        int start = 0;
        int end = 0;
        std::istringstream iss(line);
        if (!(iss >> start >> end))
        {
            continue;
        }
        requests.push_back(Request(start, end));
    }

    return requests;
};

vector<Request> filterRequests(vector<Request> requests)
{
    sort(requests.begin(), requests.end());
    Request last = requests[0];
    vector<Request> filtered{last};

    for (int i = 1; i < requests.size(); i++)
    {
        Request req = requests[i];
        if (req.start >= last.end)
        {
            filtered.push_back(req);
            last = req;
        }
    }

    return filtered;
};

int main()
{
    vector<Request> requests = readFile();
    vector<Request> filtered = filterRequests(requests);
    int count = filtered.size();

    return 0;
}