#include <iostream>

void issue1()
{
    for (char c1 = 'a'; c1 <= 'c'; c1++)
    {
        for (char c2 = 'a'; c2 <= 'c'; c2++)
        {
            for (char c3 = 'a'; c3 <= 'c'; c3++)
            {
                std::cout << c1 << c2 << c3 << std::endl;
            }
        }
    }
}

int main()
{
    issue1();

    if (__cplusplus == 201703L)
        std::cout << "C++17\n";
    else if (__cplusplus == 201402L)
        std::cout << "C++14\n";
    else if (__cplusplus == 201103L)
        std::cout << "C++11\n";
    else if (__cplusplus == 199711L)
        std::cout << "C++98\n";
    else
        std::cout << "pre-standard C++\n";

    return 0;
}