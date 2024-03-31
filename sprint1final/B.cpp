//https://contest.yandex.ru/contest/22450/run-report/103986690/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const unsigned char MatrixSize = 4;
const unsigned char MaximumNumber = 9;

int GetNumberOfPoints(int k, const vector <string>& matrix) {
	int result = 0;
	vector <unsigned char> numCount(MaximumNumber, 0);
	unsigned char asciZero = '0';
	for (int i = 0; i < MatrixSize; ++i) {
		for (int j = 0; j < MatrixSize; ++j) {
			if ('.' != matrix[i][j])
				++numCount[matrix[i][j] - asciZero - 1];
		}
	}
	for (const auto& count : numCount) {
		if (count && count <= k * 2)
			++result;
	}
	return result;
}

int main() {
	int k;
	cin >> k;
	vector <string> matrix(MatrixSize, "");
	for (int i = 0; i < MatrixSize; ++i)
		cin >> matrix[i];
	cout << GetNumberOfPoints(k, matrix) << endl;
}
