
/*
Задача о бензоколонках. Вася хочет доехать на автомобиле из города С. в город Т. Путь между городами представляет собой прямолинейный отрезок, вдоль которого стоят бензоколонки. Известно расстояние от города С. до каждой бензоколонки. Известно также расстояние, которое может проехать автомобиль Васи с полным баком. Определите минимальное количество бензоколонок, на которых нужно заправляться, чтобы доехать из С. в Т. В начале пути бак полон.

Входные данные:
В первой строке заданы три целых числа - количество бензоколонок nn, расстояние между городами С. и Т. и расстояние, на которое хватает полного бака. Вторая строка содержит nn целых чисел - расстояния от города С. до бензоколонок. Все расстояния различны и заданы в порядке возрастания.

Выходные данные:
Выведите одно целое число - минимальное количество бензоколонок, на которых нужно заправляться.

Пример входных данных:
3 10 4
3 4 6

Пример выходных данных:
2
*/

#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

using namespace std;

ifstream cin("petrol2.in");

struct RoadManager
{
    int distance;
    int fuelCapacity;
    vector<int> gasStations;
    vector<int> visitedStations;
    int stopsCount = 0;

    RoadManager(int d, int fc, vector<int> gs)
    {
        distance = d;
        fuelCapacity = fc;
        gasStations = gs;
        gasStations.push_back(distance);
        sort(gasStations.begin(), gasStations.end());
    }

    /*
    10 100 25
    13 16 21 35 38 61 67 70 77 81
          25    25 25          25
    */
    void calculateRoadStops()
    {
        int lastDistance = 0;
        int lastCapacity = fuelCapacity;
        int stationCount = gasStations.size();

        for (int i = 0; i < stationCount - 1; i++)
        {
            int diffDistance = gasStations[i] - lastDistance;
            lastCapacity -= diffDistance;
            lastDistance = gasStations[i];

            int nextDiffDistance = gasStations[i + 1] - gasStations[i];
            if (nextDiffDistance > lastCapacity)
            {
                lastCapacity = fuelCapacity;
                visitedStations.push_back(gasStations[i]);
            }
        }

        stopsCount = visitedStations.size();
    }
};

RoadManager readFile()
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

    int distance = fileData[0][1];
    int fuelCapacity = fileData[0][2];
    vector<int> gasStations = fileData[1];

    RoadManager rm = RoadManager(distance, fuelCapacity, gasStations);

    return rm;
};

int main()
{
    RoadManager fileData = readFile();
    fileData.calculateRoadStops();

    return 0;
}
