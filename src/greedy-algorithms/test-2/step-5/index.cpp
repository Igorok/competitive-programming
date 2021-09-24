
#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

ifstream cin("cont2.in");

using namespace std;

struct Product
{
    int cost;
    int weight;
    int costForKilo;
    float partCost;
    float partWeight;

    bool operator<(const Product &pr)
    {
        return costForKilo < pr.costForKilo;
    }
    bool operator>(const Product &pr) const
    {
        return costForKilo > pr.costForKilo;
    }
    int setPartByWeight(int w)
    {
        float part = static_cast<float>(w) / static_cast<float>(weight);
        partCost = cost * part;
        partWeight = weight * part;
    }

    Product(int w, int c)
    {
        cost = c;
        weight = w;
        costForKilo = cost / weight;
        partCost = c;
        partWeight = w;
    }
};

struct BackpackManager
{
    int backpackWeight = 0;
    int selectedWeight = 0;
    int selectedCost = 0;
    vector<Product> products;
    vector<Product> selectedProducts{};

    void fillBackpack()
    {
        sort(products.begin(), products.end(), greater<>());

        for (int i = 0; i < products.size(); i++)
        {
            Product prod = products[i];
            if (selectedWeight + prod.weight >= backpackWeight)
            {
                prod.setPartByWeight(backpackWeight - selectedWeight);
                selectedWeight += prod.partWeight;
                selectedCost += prod.partCost;
                selectedProducts.push_back(prod);
                break;
            }
            selectedWeight += prod.weight;
            selectedCost += prod.cost;
            selectedProducts.push_back(prod);
        }
    }

    BackpackManager(vector<vector<int>> fileData)
    {
        backpackWeight = fileData[0][1];
        for (int i = 1; i < fileData.size(); i++)
        {
            int weight = fileData[i][0];
            int cost = fileData[i][1];
            products.push_back(Product(weight, cost));
        }
    }
};

vector<vector<int>>
readFile()
{
    vector<vector<int>> data;
    string line;

    for (string line; getline(cin, line);)
    {
        int weight = 0;
        int cost = 0;
        std::istringstream iss(line);
        if (!(iss >> weight >> cost))
        {
            continue;
        }
        data.push_back(vector<int>{weight, cost});
    }

    return data;
};

int main()
{
    vector<vector<int>> data = readFile();

    BackpackManager bm = BackpackManager(data);

    bm.fillBackpack();

    return 0;
};
