//https://contest.yandex.ru/contest/26133/run-report/112106612/

/*
-- ПРИНЦИП РАБОТЫ --

Сначала допустимые к использованию слова добавляются в префиксное дерево.
Затем для проверки текста на разбиение слов из префиксного дерева используется динамическое программирование.

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --

dp - хранит признак, можно ли создать строку с данным индексом или же нет.
Для каждого индекса осуществяется проход по префиксному дереву.
dp(i) принимает значение True, если dp(i - 1) принимает значение True и для текущего слова из текста найдено слово в префиксном дереве.
Цель алгоритма — вычислить dp(T), где T - количество символов в тексте.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --

https://practicum.yandex.ru/learn/algorithms/courses/7f101a83-9539-4599-b6e8-8645c3f31fad/sprints/181005/topics/c83dc564-7573-4f64-8d1f-032c4206fac1/lessons/69512b36-47df-46e6-9983-3f921047654b/
1. Сложность построения префиксного дерева O(L), где L — суммарная длина слов во множестве.
2. Для хранения переходов по префиксному дереву используется хеш-таблица - ключом является символ, а значением — узел. 
Сложность поиска узла равна O(n) в среднем, где n - длина слова.
3. Сложность проверки разбития текста на слова O(T^2), где T - количество символов в тексте, который надо разбить на слова.
т.е. получается O(L + n + T^2), T^2 сильно больше, поэтому - 
Итоговая времення сложность будет O(T^2), где T - количество символов в тексте.

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --

Используется дополнительная память для хранения префиксного дерева O(L), где L - суммарная длина всех допустимых к использованию слов.
Также используется дополнительная память под вектор dp - O(T), где T - количество символов в тексте, который надо разбить на слова.
Итоговая пространственная сложность будет линейной: O(n), она будет зависеть от размера текста и количества допустимых к использованию слов.
*/

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct Node {
	unordered_map<char, shared_ptr<Node>> list;
	bool is_terminal = false;
};

void AddWordToTree(const shared_ptr<Node>& root, const string& word) {
	shared_ptr<Node> current_node = root;
	for (const auto& ch : word) {
		if (current_node->list.find(ch) == current_node->list.end()) {
			auto new_node = make_shared<Node>();
			current_node->list[ch] = new_node;
			current_node = new_node;
		}
		else {
			current_node = current_node->list[ch];
		}
	}
	current_node->is_terminal = true;
}

bool IsSplitWords(const string& text, const shared_ptr<Node>& root) {
	vector<bool> dp(text.size() + 1);
	dp[0] = true;
	for (int i = 0; i < dp.size(); ++i) {
		shared_ptr<Node> current_node = root;
		if (dp[i]) {
			for (int j = i; j < text.size(); ++j) {
				if (current_node->list.find(text[j]) == current_node->list.end()) {
					break;
				}
				current_node = current_node->list[text[j]];
				if (current_node->is_terminal) {
					dp[j + 1] = true;
				}
			}
		}
	}
	return dp.back();
}

int main() {
	string text;
	cin >> text;
	int n;
	cin >> n;
	auto root = make_shared<Node>();
	for (int i = 0; i < n; ++i) {
		string word;
		cin >> word;
		AddWordToTree(root, word);
	}
	cout << static_cast<string>(IsSplitWords(text, root) ? "YES" : "NO");
}