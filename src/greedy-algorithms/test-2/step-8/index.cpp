/*
Олимпиада. Вася участвует в олимпиаде, которая длится tt минут и на которой предлагается nn задач. Вася решает задачи последовательно, одну за другой, при этом порядок решения задач он может выбирать. Для каждой задачи известно время a_i, необходимое на ее решение. Вася хочет решить как можно больше задач. Кроме того, по итогам олимпиады начисляется штрафное время. Штрафное время для каждой решенной задачи определяется как номер минуты, на которой задача была сдана. За нерешенные задачи штрафное время не начисляется. Общее штрафное время вычисляется как сумма штрафного времени по всем задачам. Определите, какое наибольшее количество задач сможет решить Вася, и какое наименьшее штрафное время он наберет при оптимальном выборе решаемых задач и их порядка.

Входные данные:
В первой строке заданы два целых числа n и t - количество задач и длительность олимпиады. В следующей строке для каждой задачи задано время, за которое Вася ее решит.

Выходные данные:
Выведите два целых числа - наибольшее количество решенных задач и наименьшее штрафное время.

Пример входных данных:
3 60
30 40 20

Пример выходных данных:
2 70

Оптимальная стратегия Васи для примера: решать сначала третью задачу, потом - первую. Тогда он получит штрафное время 20 за третью задачу, и 20 + 30 = 50 за первую задачу, поскольку будет решать ее после третьей и сдаст только на 50-й минуте. Итого 70 минут штрафного времени. Другие варианты приводят в большему штрафному времени.
*/

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

ifstream cin("contest.in");

struct IssueManager
{
    int timeLimit;
    vector<int> timeList;

    int countSolved;
    int solvedTime;
    int penaltyTime;

    void calculateSolved()
    {
        for (int i = 0; i < timeList.size(); i++)
        {
            int t = timeList[i];
            if (solvedTime + t > timeLimit)
            {
                break;
            }
            countSolved++;
            solvedTime += t;
            penaltyTime += solvedTime;
        }
    }

    IssueManager(vector<vector<int>> data)
    {
        timeLimit = data[0][1];
        timeList = data[1];
        countSolved = 0;
        solvedTime = 0;
        penaltyTime = 0;
        sort(timeList.begin(), timeList.end());
    }
};

vector<vector<int>>
readFile()
{
    vector<vector<int>> fileData;
    string line;
    for (string line; getline(cin, line);)
    {
        stringstream ss(line);
        istream_iterator<int> begin(ss);
        istream_iterator<int> end;
        vector<int> vstrings(begin, end);
        fileData.push_back(vstrings);
    }

    return fileData;
};

int main()
{
    vector<vector<int>> data = readFile();
    IssueManager im = IssueManager(data);
    im.calculateSolved();

    return 0;
};