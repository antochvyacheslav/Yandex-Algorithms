//https://contest.yandex.ru/contest/24414/run-report/106539965/

/*
-- ПРИНЦИП РАБОТЫ --

для хранения данных используется вектор, который хранит двусвязный список, который хранит пару ключ-значение,
лист, он же двусвязные список используется для разрешения коллизии с помощью метода цепочек,
вектор создаётся по размеру ключа, чтобы не рассчитывать номер корзины, т.е. хеш будет соответсвовать номеру в корзине

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --

разрешение коллизии с помощью метода цепочек через лист, 
если для некоторых ключей рассчитан одинаковый хеш, то данные добавляются в конец двусвязного списка

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --

добавление, получение, удаление в среднем выполняются за константное время O(1), т.к. номер хеша соответсвует индексу в векторе,
в худшем случае при коллизии у них будет линейная сложность O(n), потому что нужно будет найти элемент в двусвязном списке,
будем считать коллизии с большим числом эелментов очень редким событием, поэтому:
итоговая временная сложность будет O(1)

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --

создаётся вектор по размеру ключей, т.е. будет O(n) памяти,
ещё в случае коллизии могут добавиться новые элементы в двусязный список, что будет равно числу элементов с коллизией, 
это тоже O(n), но сильно меньше, чем вектор по размеру ключей и очень редкое событие, поэтому:
итоговая пространственная сложность O(n)
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <optional>
#include <string>
#include <vector>

using namespace std;

// при любой последовательности команд, количество ключей в хеш-таблице не может превышать 10^5
const int MaxKeyCount = 100000;

class HashTable {
public:
	// размер корзины равен количеству ключей, чтобы хеш соответсовал индексу в корзине
	HashTable() : m_bucket(MaxKeyCount) {}

	// добавление пары ключ-значение, если заданный ключ уже есть в таблице, то соответствующее ему значение обновляется
	void put(int key, int value) {
		unsigned int hash = getHash(key);
		auto iter = find_if(m_bucket[hash].begin(), m_bucket[hash].end(), [key](const auto& p) { return p.first == key; });
		if (iter != m_bucket[hash].end()) {
			iter->second = value;
		}
		else {
			m_bucket[hash].push_back({ key, value });
		}
	}

	// получение значения по ключу, если ключа нет в таблице, то вывести «None». Иначе вывести найденное значение
	optional<int> get(int key) {
		unsigned int hash = getHash(key);
		auto iter = find_if(m_bucket[hash].begin(), m_bucket[hash].end(), [key](const auto& p) { return p.first == key; });
		if (iter != m_bucket[hash].end()) {
			return iter->second;
		}
		return nullopt;
	}

	// удаление ключа из таблицы, если такого ключа нет, то вывести «None», иначе вывести хранимое по данному ключу значение и удалить ключ
	optional<int> erase(int key) {
		unsigned int hash = getHash(key);
		auto iter = find_if(m_bucket[hash].begin(), m_bucket[hash].end(), [key](const auto& p) { return p.first == key; });
		if (iter != m_bucket[hash].end()) {
			int value = iter->second;
			m_bucket[hash].erase(iter);
			return value;
		}
		return nullopt;
	}

private:
	unsigned int getHash(int key) {
		// числа могут быть и отрицательными в том числе
		return static_cast<unsigned int>(key) % MaxKeyCount;
	}

private:
	// в таблице хранятся уникальные ключи
	// ключи и значения - целые числа
	// разрешение коллизии с помощью метода цепочек через лист
	// для простоты индекс в векторе (номер в корзине) - это хеш, т.е. хеш функция сразу возвращает номер в корзине
	// значение вектора - это лист из пар <ключ, значение>
	vector<list<pair<int, int>>> m_bucket;
};

int main() {
	int n;
	cin >> n;
	vector<string> result;
	HashTable hashTable;
	for (int i = 0; i < n; ++i) {
		string query;
		cin >> query;
		int key;
		cin >> key;
		if (query == "get") {
			const auto value = hashTable.get(key);
			result.push_back(value ? to_string(value.value()) : "None");
		}
		else if (query == "put") {
			int value;
			cin >> value;
			hashTable.put(key, value);
		}
		else if (query == "delete") {
			const auto value = hashTable.erase(key);
			result.push_back(value ? to_string(value.value()) : "None");
		}
	}
	for (const auto& s : result)
		cout << s << endl;
}
