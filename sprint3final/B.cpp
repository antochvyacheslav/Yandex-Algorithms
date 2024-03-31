//https://contest.yandex.ru/contest/23815/run-report/106065379/

/*
-- ПРИНЦИП РАБОТЫ --

1. создать структру и перегрузить для неё операторы сравнения в соответсвии с условиями
2. реализовать алгоритм in-place, согласно описанию в задаче

основная идея такая же, как для обычной быстрой сортировки
- выбрать опорный элемент
- с помощью двух указателай найти элементы слева и справа от опорного элемента, которые нарушают порядок
- поменять местами/упорядочить эти элементы слева и справа от опорного элемента
- затем рекурсивно вызвать метод для двух полученных частей слева и справа от опорного элемента

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --

пример с обычной быстрой сортировкой из 12 урока, которая использует дополнительную память
кстати, в примере ошибка, для работы надо исправить сигнатуру метода, например, так:
std::tuple<std::vector<int>, std::vector<int>, std::vector<int>> partition(std::vector<int>& array, int pivot) {
https://github.com/Yandex-Practicum/algorithms-theory-examples/blob/master/sprint3/By%20languages/C%2B%2B/lesson12code1.cpp

изначально пытался выбирать опорный элемент рандомно, как из примера в уроке, но он не укладывался в лимит по времени:
Student pivot = students[rand() % students.size()];
https://contest.yandex.ru/contest/23815/run-report/106065364/
поэтому переделал на выбор медианы, и такой вариант уложился по времени
Student pivot = students[(left + right) / 2];

на википедии при описании Схемы Хоара тоже говорится:
"логичнее в данном алгоритме выбирать в качестве опорного элемента среднее значение между начальным и конечным элементом"
pivot := A[(low + high) / 2]
https://ru.wikipedia.org/wiki/%D0%91%D1%8B%D1%81%D1%82%D1%80%D0%B0%D1%8F_%D1%81%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0#%D0%A1%D1%85%D0%B5%D0%BC%D0%B0_%D0%A5%D0%BE%D0%B0%D1%80%D0%B0

ещё пример с in-place быстрой сортировкой
https://forkettle.ru/vidioteka/programmirovanie-i-set/algoritmy-i-struktury-dannykh/108-sortirovka-i-poisk-dlya-chajnikov/1010-metod-khoara-bystraya-sortirovka-quick-sort

данная реализация не будет устойчивой, т.к. одинкаовые элементы могут меняться местами,
возможно сортировку можно сделать устойчивой, если перед обменом элементов добавить проверку, что они не равны
swap(students[i], students[j]);

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --

https://ru.wikipedia.org/wiki/%D0%91%D1%8B%D1%81%D1%82%D1%80%D0%B0%D1%8F_%D1%81%D0%BE%D1%80%D1%82%D0%B8%D1%80%D0%BE%D0%B2%D0%BA%D0%B0#%D0%9E%D1%86%D0%B5%D0%BD%D0%BA%D0%B0_%D1%81%D0%BB%D0%BE%D0%B6%D0%BD%D0%BE%D1%81%D1%82%D0%B8_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%B0
https://practicum.yandex.ru/learn/algorithms/courses/7f101a83-9539-4599-b6e8-8645c3f31fad/sprints/181000/topics/4a0eb007-5d71-4dda-bc54-df8c743f80ea/lessons/3687bb29-093f-448b-990f-b480783f1da4/
по аналогии с обычной быстрой сортировкой, в среднем работает за O(log n)
но можно подобрать такие входные данные - киллер-последовательностями (англ. killer-sequence), на который будет квадратичная сложность O(n^2)

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --

вектор, передаётся по ссылке, он не копируется, поэтому его размер O(n) не учитываем,
из дополнительно памяти есть локальные переменные и параметры метода на стеке - они занимают констаный объём памяти O(1),
но на каждом уровне рекурсии локальные переменны и параметры метода будут добавляться в стек вызовов,
т.е. дополнительная память зависит от глубины рекурсии, 
т.е. в среднем будет O(log n), но в очень редком худшем случае для killer-sequence глубина будет равна числу элементов O(n)
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

bool operator<(const Student& lh, const Student& rh) {
	return (lh.m_p > rh.m_p) || ((lh.m_p == rh.m_p) && (lh.m_f < rh.m_f)) || ((lh.m_p == rh.m_p) && (lh.m_f == rh.m_f) && (lh.m_login < rh.m_login));
}

bool operator>(const Student& lh, const Student& rh) {
	return (lh.m_p < rh.m_p) || ((lh.m_p == rh.m_p) && (lh.m_f > rh.m_f)) || ((lh.m_p == rh.m_p) && (lh.m_f == rh.m_f) && (lh.m_login > rh.m_login));
}

void quicksort(vector<Student>& students, int left, int right) {
	if (left >= right)
		return;
	// выбрать опорный элемент
	Student pivot = students[(left + right) / 2];
	// два указателя, которые изначально будут указывать на левый и правый концы отрезка соответственно
	int i = left;
	int j = right;
	while (i < j) {
		// двигать левый указатель вправо до тех пор, пока он указывает на элемент, меньший опорного
		while (students[i] < pivot)
			++i;
		// двигаем правый указатель влево, пока он стоит на элементе, превосходящем опорный
		while (students[j] > pivot)
			--j;
		// в итоге окажется, что что левее от i все элементы точно принадлежат первой группе, а правее от j — второй группе
		if (i <= j) {
			// элементы, на которых стоят указатели, нарушают порядок, поменяем их местами
			swap(students[i], students[j]);
			// продвинем указатели на следующие элементы
			++i;
			--j;
		}
	}
	if (i < right)
		quicksort(students, i, right);
	if (left < j)
		quicksort(students, left, j);
}

int main() {
	int n;
	cin >> n;
	vector<Student> students(n);
	for (int i = 0; i < n; ++i)
		cin >> students[i].m_login >> students[i].m_p >> students[i].m_f;
	quicksort(students, 0, n - 1);
	for (const auto& student : students)
		cout << student.m_login << endl;
}
