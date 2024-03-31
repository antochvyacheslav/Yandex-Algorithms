//https://contest.yandex.ru/contest/24810/run-report/108819538/

/*
-- ПРИНЦИП РАБОТЫ --

Используется неубывающая пирамида — это min-heap, у неё в корне минимум.
При добавлении элементов используется просеивание вверх.
При сортировке, когда извлекается очередной минимум из корня используется просевивание вниз
Код для пирамидальной сортировки взят из уроков:
Урок 10. Приоритетная очередь. Вставка и удаление
https://github.com/Yandex-Practicum/algorithms-theory-examples/blob/master/sprint5/By%20lessons/lesson10code1/lesson10code1.cpp
https://github.com/Yandex-Practicum/algorithms-theory-examples/blob/master/sprint5/By%20lessons/lesson10code2/lesson10code2.cpp
Урок 11. Куча. Пирамидальная сортировка. Алгоритм и его сложность
https://github.com/Yandex-Practicum/algorithms-theory-examples/blob/master/sprint5/By%20lessons/lesson11code1/lesson11code1.cpp

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --

Создать пустую бинарную неубывающую кучу (min-heap) и заполнить её элементами из массива, который надо отсортировать.
Используется бинарная неубывающая куча (min-heap), поэтому в корне всегда находится минимальный элемент, 
поэтому достаточно извлекать из корень - самый приоритетный элемент (т.е. минимум, с самым маленьким значением)
и удалять его из кучи.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --

Сложность пирамидальной сортировки в худшем случае O(n logn)

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --

Нужно выделить память под массив из n элементов, т.е. потребуется O(n) дополнительной памяти
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Student { // участник описывается тремя параметрами:
	string m_login = ""; // уникальным логином (строкой из маленьких латинских букв длиной не более 20)
	int m_p = 0; // числом решённых задач Pi — целые числа, лежащие в диапазоне от 0 до 109
	int m_f = 0; // штрафом Fi — целые числа, лежащие в диапазоне от 0 до 109
};

bool operator>(const Student& lh, const Student& rh) {
	return (lh.m_p < rh.m_p) || ((lh.m_p == rh.m_p) && (lh.m_f > rh.m_f)) || ((lh.m_p == rh.m_p) && (lh.m_f == rh.m_f) && (lh.m_login > rh.m_login));
}

template<class T>
void sift_up(vector<T>& heap, int index) {
	if (index == 1)
		return;
	int parentIndex = index / 2;
	// добавление элементов по уменьшению приоритета, т.е. в корне меньший элемент
	if (heap[parentIndex - 1] > heap[index - 1]) { 
		swap(heap[parentIndex - 1], heap[index - 1]);
		sift_up(heap, parentIndex);
	}
}

template<class T>
void heap_add(vector<T>& heap, T key) {
	int index = heap.size() + 1;
	heap.push_back(key);
	sift_up(heap, index);
}

template<class T>
void sift_down(vector<T>& heap, int index) {
	int left = 2 * index + 1;
	int right = 2 * index + 2;
	if (left >= heap.size())
		return;
	int indexSmallest = left;
	// поиск наименьшего элемента
	if (right < heap.size() && heap[left] > heap[right]) { 
		indexSmallest = right;
	}
	// поменять местами с наименьшим элементом
	if (heap[index] > heap[indexSmallest]) { 
		swap(heap[index], heap[indexSmallest]);
		sift_down(heap, indexSmallest);
	}
}

template<class T>
T pop_min(vector<T>& heap) {
	T result = heap[0];
	heap[0] = heap.back();
	heap.pop_back();
	sift_down(heap, 0);
	return result;
}

template<class T>
vector<T> heapsort(const vector<T>& array) {
	// Создадим пустую бинарную кучу.
	vector<T> heap;
	// Вставим в неё по одному все элементы массива, сохраняя свойства кучи.
	for (const auto& item : array) {
		heap_add(heap, item);
	}
	// Будем извлекать из неё наиболее приоритетные элементы, удаляя их из кучи.
	vector<T> sortedArray;
	while (!heap.empty()) {
		T max = pop_min(heap);
		sortedArray.push_back(max);
	}
	return sortedArray;
}

int main() {
	int n;
	cin >> n;
	vector<Student> students(n);
	for (int i = 0; i < n; ++i)
		cin >> students[i].m_login >> students[i].m_p >> students[i].m_f;
	for (const auto& student : heapsort(students))
		cout << student.m_login << endl;
}
