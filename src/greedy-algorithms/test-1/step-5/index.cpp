#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

ifstream cin("schedule2.in");

struct Order
{
    int deadline;
    int price;

    bool operator<(const Order &o) const
    {
        return price < o.price;
    }
    bool operator>(const Order &o) const
    {
        return price > o.price;
    }

    Order(int d, int p)
    {
        deadline = d;
        price = p;
    }
};

vector<Order> readFile()
{
    vector<Order> orders;
    string line;
    for (string line; getline(cin, line);)
    {
        int deadline = 0;
        int price = 0;
        std::istringstream iss(line);
        if (!(iss >> deadline >> price))
        {
            continue;
        }
        orders.push_back(Order(deadline, price));
    }

    return orders;
}

long getTotalPrice(vector<Order> orders)
{
    sort(orders.begin(), orders.end(), greater<>());

    long total = 0;
    vector<int> used(orders.size() + 1, 0);
    for (int i = 0; i < orders.size(); i++)
    {
        Order order = orders[i];
        for (int j = order.deadline; j > 0; j--)
        {
            if (used[j] == 0)
            {
                used[j] = order.price;
                total += order.price;
                break;
            }
            else
            {
                continue;
            }
        }
    }
    // 2305658251934
    return total;
}

int main()
{
    vector<Order> orders = readFile();
    long total = getTotalPrice(orders);

    return 0;
}
