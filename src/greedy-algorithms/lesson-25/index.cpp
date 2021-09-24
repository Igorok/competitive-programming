
#include <vector>
#include <functional>
#include <algorithm>

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

    Product(int c, int w)
    {
        cost = c;
        weight = w;
        costForKilo = cost / weight;
        partCost = c;
        partWeight = w;
    }
};

vector<Product> fillBackpack(vector<Product> products, int weight)
{
    int selectedWeight = 0;
    vector<Product> selectedProducts{};
    sort(products.begin(), products.end(), greater<>());

    for (int i = 0; i < products.size(); i++)
    {
        Product prod = products[i];
        if (selectedWeight + prod.weight >= weight)
        {
            prod.setPartByWeight(weight - selectedWeight);
            selectedWeight += prod.weight;
            selectedProducts.push_back(prod);
            break;
        }
        selectedWeight += prod.weight;
        selectedProducts.push_back(prod);
    }

    return selectedProducts;
}

int main()
{
    vector<Product> products = vector<Product>{};

    products.push_back(Product(30, 10));
    products.push_back(Product(10, 2));
    products.push_back(Product(20, 5));
    int weight = 12;

    vector<Product> selectedProducts = fillBackpack(products, weight);
    return 0;
}
