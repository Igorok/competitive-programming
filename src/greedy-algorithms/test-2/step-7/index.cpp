/*
Задача о выборе заявок с бесконечным числом аудиторий. Рассмотрим модифицированный вариант задачи о выборе заявок. Имеется бесконечное число аудиторий и nn заявок на проведение занятий в них. Каждая заявка - это временной интервал [l_i, r_i), причем левая граница включается в интервал, а правая - нет. Нужно распределить по аудиториям все заявки, чтобы занятия в каждой аудитории не пересекались по времени, и при этом использовалось наименьшее число аудиторий.

Входные данные:
В первой строке задано целое число nn - количество заявок. Следующие nn строк описывают заявки: ii-я строка содержит два целых числа - l_i и r_ir, l_i < r_i.
Выходные данные:
Выведите одно целое число - наименьшее число аудиторий, достаточное для удовлетворения всех заявок.
Пример входных данных:
3
1 5
3 6
5 7
Пример выходных данных:
2

53884
*/

#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

ifstream cin("request2.in");

using namespace std;

struct Request
{
    int start;
    int end;

    bool operator<(const Request &r) const
    {
        return start < r.start;
    }

    Request(int s, int e)
    {
        start = s;
        end = e;
    }
};

struct RequestManager
{
    vector<vector<Request>> queue;
    vector<vector<Request>> timeTables;
    int countTimeTables;

    RequestManager(vector<vector<int>> data)
    {
        countTimeTables = 0;

        vector<Request> requests{};
        for (int i = 0; i < data.size(); i++)
        {
            requests.push_back(Request(data[i][0], data[i][1]));
        }
        sort(requests.begin(), requests.end());

        queue.push_back(requests);
    }

    void generateTimeTable()
    {
        while (!queue.empty())
        {
            vector<Request> requests = queue.back();
            queue.pop_back();
            Request last = requests[0];
            vector<Request> timeTable{last};
            vector<Request> rejected{};

            for (int j = 1; j < requests.size(); j++)
            {
                if (requests[j].start >= last.end)
                {
                    last = requests[j];
                    timeTable.push_back(last);
                }
                else
                {
                    rejected.push_back(requests[j]);
                }
            }

            timeTables.push_back(timeTable);

            if (rejected.size() != 0)
            {
                queue.push_back(rejected);
            }
        }

        countTimeTables = timeTables.size();
    }
};

vector<vector<int>>
readFile()
{
    vector<vector<int>> data;
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
        data.push_back(vector<int>{start, end});
    }

    return data;
};

int main()
{

    vector<vector<int>> data = readFile();
    RequestManager rm = RequestManager(data);
    rm.generateTimeTable();

    return 0;
};
