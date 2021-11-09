/*
Даны целые числа a[1], a[2], ..., a[n]. Нужно для каждого числа определить количество единичных битов в его двоичном представлении.

Входные данные:
В первой строке дано количество чисел n. Следующая строка содержит целые неотрицательные числа a[1], a[2], ..., a[n], разделенные одиночными пробелами.

Выходные данные:
Выведите nn чисел, разделенных одиночными пробелами, - количества единичных битов в двоичных представлениях данных чисел.

Пример входных данных:
3
5 13 0
Пример выходных данных:
2 3 0

Двоичные представления для чисел из примера: 5 = 101(2), 13 = 1101(2), 0 = 0(2).
В качестве ответа на задание введите искомую последовательность для теста из файла ones.in. Последовательность должна состоять из целых чисел, разделенных одиночными пробелами, без пробелов в начале и в конце. Для примера из условия искомая последовательность имеет вид “2 3 0” (без кавычек).
*/

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <bitset>

using namespace std;

ofstream cout("output.txt");
ifstream cin("ones.in");

vector<vector<long long>>
readFile()
{
    vector<vector<long long>> filea;
    string line;
    for (string line; getline(cin, line);)
    {
        stringstream ss(line);
        istream_iterator<long long> begin(ss);
        istream_iterator<long long> end;
        vector<long long> vstrings(begin, end);
        filea.push_back(vstrings);
    }

    return filea;
};

void calculate(vector<vector<long long>> data)
{
    vector<long long> numbers = data[1];

    for (int i = 0; i < numbers.size(); i++)
    {
        long long count = 0;
        long long num = numbers[i];
        while (num > 0)
        {
            if (num & 1)
            {
                count++;
            }
            num = num >> 1;
        }

        if (i != 0)
        {
            cout << " ";
        }
        cout << count;
    }
    cout << endl;
};

int main()
{
    vector<vector<long long>> data = readFile();

    calculate(data);

    return 0;
};

/*
8 15 16 17 15 16 17 15



*/
