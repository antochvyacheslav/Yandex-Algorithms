//https://contest.yandex.ru/contest/25070/run-report/110521360/

/*
-- ПРИНЦИП РАБОТЫ --

Используется алгоритм Прима на очереди с приоритетами
https://github.com/Yandex-Practicum/algorithms-theory-examples/blob/master/sprint6/By%20lessons/lesson10code1/lesson10code1.kt

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --

Используется Алгоритм Прима на очереди с приоритетами (Спринт 6/8 → Тема 1/2: Графы → Урок 10/13)

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --

Алгоритму требуется число шагов, пропорциональное количеству вершин.
На каждом шаге надо найти минимальное по весу ребро.
Для хранения рёбер используется очередь с приоритетом, поэтому на вершине всегда лежит максимальный элемент.
Поиска максимального ребра занимает О(log(V)) времени, где V - количество вершин в графе.
Если вместе с ребром в подграф добавляется новая вершина, то это ребро добавляется в остов.
Если ребро соединяет две вершины, уже присутствующее в подмножестве остова, то оно отбрасывается из дальнейшего рассмотрения и из кучи в том числе.
Благодаря приоритетной очереди сложность алгоритма Прима O(E*log(V)), где E - количество рёбер в графе, V - количество вершин.

https://www.geeksforgeeks.org/analysis-of-time-and-space-complexity-of-stl-containers/
https://www.geeksforgeeks.org/set-vs-unordered_set-c-stl/

Цикл по всем вершинам:
- в этом цикле для связного графа будет просмотрены все вершины (иначе NotAdded останется не пустым)
1. Извлечь максимальное ребро из приоритетной очереди с рёбрами O(1)
2. Удалить это ребро из приоритетной очереди O(log(E))
3. Поиск вершины в unordered_set O(1)
Цикл по инцидентным вершинам для вершины из верхнего цикла:
- в этом цикле для связного графа должны быть пройдены все рёбра (в соответсвии с алгоритмом на поиск максимального ребра)
1. Удаление вершины из unordered_set O(1)
2. Поиск вершины в unordered_set O(1)
3. Добавление ребра в приоритетную очередь O(log(E))

На каждом шаге в массиве рёбер, исходящих из остовного дерева будут только 
рёбра для вершин которые не вошли в остов + новые рёбра исходящие из текущий вершины, 
но которые не соединяет уже посещёные вершины, поэтому сложность поиска макисального ребра O(V).

В итоге будут просмотрены все рёбра и все вершины, т.е. сложность O(V) + O(E*log(V)).
Итоговая временная сложность: O(E*log(V))

time complexity remains O(E Log V) as there will be at most O(E) vertices in priority queue and O(Log E) is same as O(Log V)
https://www.geeksforgeeks.org/prims-algorithm-using-priority_queue-stl/

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --

Таблица для хранения взвешенного неориентированного графа - O(V*V)
Хеш таблица для хранения вершин не добавленных в остов, изначально все вершины - O(V)
Массив рёбер исходящих из остовного дерева, в худшем случае все рёбра - O(E)
V+E сильно меньше V+E сильно меньше V^2, поэтомe,
итоговая пространственная сложность: O(V^2)
*/

#include <algorithm>
#include <iostream>
#include <optional>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

struct Edge {
	int m_first;
	int m_second;
	int m_weight;
};

bool operator<(const Edge& lhs, const Edge& rhs) {
	return lhs.m_weight < rhs.m_weight;
}

unordered_set<int> NotAdded;// Множество вершин, ещё не добавленных в остов.
priority_queue<Edge> Edges;// Массив рёбер, исходящих из остовного дерева.

void addVertex(vector<unordered_map<int, int>>& graph, int v) {
	NotAdded.erase(v);
	// Добавляем все рёбра, которые инцидентны v, но их конец ещё не в остове.
	//
	// Вершины notAdded стоит хранить в таком контейнере,
	// чтобы проверка (end in notAdded) выполнялась эффективно.
	//
	// Для этого подойдёт, например, хеш-таблица.
	// Также в некоторых языках программирования имеется контейнер set.
	for (const auto& [u, w] : graph[v]) {
		if (NotAdded.find(u) != NotAdded.end()) {
			Edges.push({ v, u, w });
		}
	}
}

optional<int> findMST(vector<unordered_map<int, int>>& graph) {
	for (int i = 1; i < graph.size(); ++i) {
		NotAdded.insert(i);
	}
	// Берём первую попавшуюся вершину.
	addVertex(graph, 1);
	// Вес максимального остновго дерева MST.
	int maximumWeightSpanningTree = 0;
	while (!NotAdded.empty() && !Edges.empty()) {
		// Подразумеваем, что extractMaximum извлекает максимальное ребро
		// из массива рёбер и больше данного ребра в массива не будет.
		const auto e = Edges.top();
		Edges.pop();
		if (NotAdded.find(e.m_second) != NotAdded.end()) {
			maximumWeightSpanningTree += e.m_weight;
			addVertex(graph, e.m_second);
		}
	}
	// Исходный граф несвязный return nullopt
	return NotAdded.empty() ? maximumWeightSpanningTree : optional<int>(nullopt);
}

int main() {
	int n, m;
	cin >> n >> m;
	vector<unordered_map<int, int>> graph(n + 1);
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		w = max(w, graph[u][v]);
		graph[u][v] = w;
		graph[v][u] = w;
	}
	if (const auto weight = findMST(graph)) {
		cout << weight.value();
	}
	else {
		cout << "Oops! I did it again";
	}
}
