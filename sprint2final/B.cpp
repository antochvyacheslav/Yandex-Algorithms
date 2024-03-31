//https://contest.yandex.ru/contest/22781/run-report/104351751/

/*
на этот сайт наткнулся, когда искал, как убрать кучу ифов и сделать мапу функций)
https://www.geeksforgeeks.org/cpp-map-of-functions/
эти сайты использовал, чтобы красиво реализовать математическое целочисленное деление, чтобы округление было вниз
https://ilyachalov.livejournal.com/343124.html
https://microkontroller.ru/programmirovanie-mikrokontrollerov-avr/pryamoy-obratnyiy-dopolnitelnyiy-kod-dvoichnogo-chisla/
https://stackoverflow.com/questions/39304681/division-with-negative-dividend-but-rounded-towards-negative-infinity

-- ПРИНЦИП РАБОТЫ --
1. Обработка входного символа:
- Если на вход подан операнд, он помещается на вершину стека.
- Если на вход подан знак операции, то эта операция выполняется над требуемым количеством значений, взятых из стека в порядке добавления. Результат выполненной операции помещается на вершину стека.
2. Если входной набор символов обработан не полностью, перейти к шагу 1.
3. После полной обработки входного набора символов результат вычисления выражения находится в вершине стека. Если в стеке осталось несколько чисел, то надо вывести только верхний элемент.

Когда а отрицательное, то для "математического целочисленного деления", которое называется "евклидово деление" в коде используется хитрый приём ~(~a / b),
~a - интвентирование всех бит, отрицательные числа в памяти представлены в дополнительном коде, это инвертированный код плюс 1, т.е. если было число -15, то станет 14, если было 15, станет -16

например, -15 / 5 для Евклидова деления должно быть -3
a=-15, b=5
~a=14
~a/b=2
~(~a/b)=-3

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
перебор строки - O(n)
добавление в стек - O(1)
извлечение из стека - O(1)
арифметическая операция - O(1)

итоговая временная сложность будет линейно зависеть от размера входной строки, поэтому O(n)

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
статическая память: 
для хранения мапы из 4 элементов это O(1)
память на стеке:
строка на n символов O(n)
строковый поток для обработки строки O(n)
стек на m элементов O(m)

итоговая пространственная сложность будет линейно зависеть от размера входной строки, поэтому O(n)
*/

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <stack>

using namespace std;

using Operation = int(*)(int, int);

static const map<string, Operation> Operations {
    { "+", [](int a, int b) { return a + b; } },
    { "-", [](int a, int b) { return a - b; } },
    { "/", [](int a, int b) { return a >= 0 ? a / b : ~(~a / b); } },
    { "*", [](int a, int b) { return a * b; } }
};

int calculate(const string& str) {
    stack<int> numbers;
    stringstream ss(str);
    string word;
    while (ss >> word) {
        if (const auto& operation = Operations.find(word); 
            Operations.end() != operation) {
            int num2 = numbers.top();
            numbers.pop();
            int num1 = numbers.top();
            numbers.pop();
            numbers.push(operation->second(num1, num2));
        }
        else {
            numbers.push(stoi(word));
        }
    }
    return numbers.top();
}

int main() {
    string input;
    getline(cin, input);
    cout << calculate(input) << endl;
}
