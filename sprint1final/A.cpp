//https://contest.yandex.ru/contest/22450/run-report/103388405/

#include <iostream>
#include <vector>

using namespace std;

vector <int> GetNearestZero(const vector <int>& numberList) {
	vector <int> result(numberList.size(), 0);
	int j = 0;
	for (int i = 0; i < numberList.size(); ++i, ++j) {
		if (!numberList[i])
			j = 0;
		result[i] = j;
	}
	for (int i = numberList.size() - j; i >= 0; --i, ++j) {
		if (!numberList[i])
			j = 0;
		if (j < result[i] || (i == result[i] && numberList.front()))
			result[i] = j;
	}
	return result;
}

void print(const vector <int>& result) {
	for (int x : result)
		cout << x << " ";
	cout << endl;
}

int main() {
	int n;
	cin >> n;
	vector <int> numberList(n);
	for (int i = 0; i < n; ++i)
		cin >> numberList[i];
	print(GetNearestZero(numberList));
}
