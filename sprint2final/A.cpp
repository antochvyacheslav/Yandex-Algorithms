//https://contest.yandex.ru/contest/22781/run-report/104342770/

/*
За основу взят пример со стеком из 9 урока
https://github.com/Yandex-Practicum/algorithms-theory-examples/blob/master/sprint2/By%20languages/C%2B%2B/lesson9code1.cpp

-- ПРИНЦИП РАБОТЫ --
head указывает на свободное место для добавления в начало дека;
tail указывает на свободное место для добавления в конец дека;
также как и вектор идёт от по возрастанию от 0 до max, так и head в деке идёт раньше tail, т.е. слева направо;
при создании дека head показывает на последний индекс, а tail на начало;
дек - deque — double ended queue - очередь с двумя концами - интерфейс, который позволяет и добавлять, и извлекать элементы с обоих концов;

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --
добавление в дек стоит O(1), потому что добавление в вектор стоит O(1);
извлечение из дека тоже стоит O(1);

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --
дек, содержащий n элементов, занимает O(n) памяти
*/

#include <iostream>
#include <vector>
#include <string>
#include <optional>

using namespace std;

class MyDeque {
    vector<int> m_deque;
    int m_max;
    int m_head;
    int m_tail;
    int m_size;

public:
    MyDeque(int n) {
        m_deque.resize(n);
        m_max = n;
        m_head = n - 1;
        m_tail = 0;
        m_size = 0;
    }

    bool isEmpty() const {
        return m_size == 0;
    }

    bool isFull() const {
        return m_size == m_max;
    }

    bool push_back(int value) {
        if (isFull())
            return false;
        m_deque[m_tail] = value;
        m_tail = (m_tail + 1) % m_max;
        m_size += 1;
        return true;
    }

    bool push_front(int value) {
        if (isFull())
            return false;
        m_deque[m_head] = value;
        m_head = (m_max + m_head - 1) % m_max;
        m_size += 1;
        return true;
    }

    optional<int> pop_back() {
        if (isEmpty())
            return nullopt;
        m_tail = (m_max + m_tail - 1) % m_max;
        int value = m_deque[m_tail];
        m_deque[m_tail] = 0;
        m_size -= 1;
        return value;
    }

    optional<int> pop_front() {
        if (isEmpty())
            return nullopt;
        m_head = (m_head + 1) % m_max;
        int value = m_deque[m_head];
        m_deque[m_head] = 0;
        m_size -= 1;
        return value;
    }
};


int main() {
    int n = 0;
    int m = 0;
    cin >> n;
    cin >> m;
    MyDeque deque(m);
    vector <string> result;
    for (int i = 0; i < n; ++i) {
        string command;
        cin >> command;
        if (command == "push_back") {
            int value;
            cin >> value;
            if (!deque.push_back(value))
                result.push_back("error");
        }
        else if (command == "push_front") {
            int value;
            cin >> value;
            if (!deque.push_front(value))
                result.push_back("error");
        }
        else if (command == "pop_back") {
            const auto pop = deque.pop_back();
            result.push_back(pop ? to_string(pop.value()) : "error");
        }
        else if (command == "pop_front") {
            const auto pop = deque.pop_front();
            result.push_back(pop ? to_string(pop.value()) : "error");
        }
    }
    for (const auto& s : result)
        cout << s << endl;
}
