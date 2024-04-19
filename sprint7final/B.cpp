//https://contest.yandex.ru/contest/25597/run-report/111379751/

/*
-- ПРИНЦИП РАБОТЫ --

https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D1%80%D0%B0%D0%B7%D0%B1%D0%B8%D0%B5%D0%BD%D0%B8%D1%8F_%D0%BC%D0%BD%D0%BE%D0%B6%D0%B5%D1%81%D1%82%D0%B2%D0%B0_%D1%87%D0%B8%D1%81%D0%B5%D0%BB#%D0%A1%D0%BF%D0%B5%D1%86%D0%B8%D0%B0%D0%BB%D1%8C%D0%BD%D1%8B%D0%B9_%D1%81%D0%BB%D1%83%D1%87%D0%B0%D0%B9_%D0%B7%D0%B0%D0%B4%D0%B0%D1%87%D0%B8_%D0%BE_%D1%81%D1%83%D0%BC%D0%BC%D0%B5_%D0%BF%D0%BE%D0%B4%D0%BC%D0%BD%D0%BE%D0%B6%D0%B5%D1%81%D1%82%D0%B2
https://en.wikipedia.org/wiki/Pseudopolynomial_time_number_partitioning

dp(i, j) принимает значение True, если среди { x1, ..., xj } существует такое подмножество, элементы которого в сумме дают i и False в противном случае.
Тогда dp(sum/2, n) принимает значение True тогда и только тогда, когда существует подмножество S, сумма которого равна [sum/2].
Цель алгоритма — вычислить dp(sum/2, n).
Для достижения этого используеются следующие рекуррентные формулы:
dp(i, j) принимает значение True, если либо dp(i, j − 1) принимает значение True, либо dp(i − xj, j − 1) принимает значение True
dp(i, j) принимает значение False в противном случае

-- ДОКАЗАТЕЛЬСТВО КОРРЕКТНОСТИ --

Cуществует некоторое подмножество S, сумма которого равна i для чисел x1, ..., xj тогда и только тогда, когда одно из двух верно:
существует подмножество { x1, ..., xj-1 }, дающее сумму i;
существует подмножество { x1, ..., xj-1 }, дающее сумму i − xj, поскольку xj + сумма этого подмножества=i.

-- ВРЕМЕННАЯ СЛОЖНОСТЬ --

Алгоритм работает за время O(K*N), где K — сумма элементов во входном множестве, N — число элементов во входном множестве

-- ПРОСТРАНСТВЕННАЯ СЛОЖНОСТЬ --

Используется дополнительная память под матрицу dp размером K/2, O(1/2*K)=O(K)
Поэтому итоговая пространственная сложность: O(K), K — сумма элементов во входном множестве
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool isEqualSum(vector<int>& v) {
	int sum = 0;
	for_each(v.begin(), v.end(), [&sum](int n) { sum += n; });
	if (sum % 2 != 0) {
		return false;
	}
	int k = sum / 2;
	vector<bool> dp(k + 1);
	dp[0] = true;
	for (int i = 0; i < v.size(); ++i) {
		for (int j = k; j >= v[i]; --j) {
			dp[j] = dp[j] || dp[j - v[i]];
		}
	}
	return dp[k];
}

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
	}
	cout << static_cast<string>(isEqualSum(v) ? "True" : "False");
}
