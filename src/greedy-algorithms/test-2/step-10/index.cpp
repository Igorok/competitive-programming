/*
Мороженое. Имеется список сортов, которые будут представлены на фестивале мороженого. Известно, что этот список был составлен из списков от нескольких разных производителей: сначала идут сорта от первого производителя, потом - от второго и т.д. Сорта от каждого производителя различны, но в общем списке могут встречаться повторения. Ваша задача - определить минимально возможное количество производителей мороженого.

Входные данные:
В первой строке содержится целое число nn - количество элементов в списке сортов. В каждой из следующих nn строк содержится по одному наименованию сорта. Наименование сорта - непустая последовательность строчных латинских букв и цифр длиной не более 3030 символов и начинающаяся с буквы.

Выходные данные:
Выведите единственное целое число - минимально возможное количество производителей мороженого.

Пример входных данных:
8
vanilla20
pistachio
strawberry
blackberry
vanilla20
pistachio
pistachio
vanilla20

Пример выходных данных:
3

Поясним приведенный пример. Первые четыре сорта мороженого (vanilla20, pistachio, strawberry, blackberry) различны, так что они вполне могут изготавливаться одним производителем. Далее в списке вновь встречается vanilla20, и этот сорт уже не может быть изготовлен тем же производителем, так что нам придется предположить, что имеется еще один производитель. Поскольку к изготавливаемым вторым производителем сортам мы пока отнесли только vanilla20, ничто не мешает сделать аналогичное предположение относительно pistachio. Но в списке два мороженых pistachio подряд, значит, есть еще и третий производитель, который изготовил также последнее в списке мороженое vanilla20.
*/

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <map>

using namespace std;

ifstream cin("ice2.in");

vector<string>
readFile()
{
    vector<string> fileData;
    for (string line; getline(cin, line);)
    {
        string name;
        std::istringstream iss(line);
        if (!(iss >> name))
        {
            continue;
        }
        fileData.push_back(name);
    }

    fileData.erase(fileData.begin());

    return fileData;
};

struct DuplicatesManager
{
    vector<string> productList;
    int factories;
    DuplicatesManager(vector<string> pl)
    {
        factories = 1;
        productList = pl;
    }

    void calculateDuplications()
    {
        map<string, int> uniqProducts = map<string, int>{};
        for (int i = 0; i < productList.size(); i++)
        {
            string key = productList[i];
            int count = uniqProducts.count(key);

            if (count != 0)
            {
                uniqProducts = map<string, int>{};
                factories++;
            }

            uniqProducts.insert({key, 1});
        }
    }
};

int main()
{
    vector<string> fileData = readFile();
    DuplicatesManager dm = DuplicatesManager(fileData);
    dm.calculateDuplications();

    return 0;
};