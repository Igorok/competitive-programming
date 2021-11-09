/*
Шаблон. Задан шаблон, состоящий из строчных латинских букв от ‘a’ до ‘e’ и вопросительных знаков ‘?’. Будем говорить, что строка соответствует шаблону,  если она получается из шаблона заменой всех вопросительных знаков на строчные латинские буквы от ‘a’ до ‘e’. Если вопросительных знаков в шаблоне несколько, они могут быть заменены на разные буквы. Например, шаблону “a?b?” соответствуют строки “aabc”, “aebd”, “aaba” и др. Выведите все строки, соответствующие данному шаблону, в лексикографическом порядке.

Входные данные:
Шаблон - строка, состоящая из строчных латинских букв от ‘a’ до ‘e’ и вопросительных знаков ‘?’.

Выходные данные:
Выведите все строки, соответствующие шаблону, в лексикографическом порядке.

Пример входных данных:
ab?c

Пример выходных данных:
abac
abbc
abcc
abdc
abec

В качестве ответа на задание введите строку с номером 500 в лексикографическом порядке для следующего шаблона:
a??cab?d?ba

Строка должна содержать только строчные латинские буквы от ‘a’ до ‘e’ и ее длина должна совпадать с длиной шаблона, т.е. быть равна 11.  Для примера из условия строка с номером 4 имеет вид “abdc” (без кавычек).
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

string str = "?be?bdcb?dcb?debcd??bdad?ee";
string characters = "abcde";

void rec(string tpl, int ind)
{
    if (ind == tpl.size())
    {
        cout << tpl << endl;
        return;
    }

    if (tpl[ind] == '?')
    {
        for (int i = 0; i < characters.size(); i++)
        {
            string newTpl = tpl;
            newTpl[ind] = characters[i];
            rec(newTpl, ind + 1);
        }
    }
    else
    {

        rec(tpl, ind + 1);
    }
};

int main()
{
    rec(str, 0);

    return 0;
};