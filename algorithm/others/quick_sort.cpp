/* 퀵 정렬
* 평균 수행 복잡도 O(n * log n)
* 최악 수행 복잡도 O(n^2)
*/
#include <iostream>
#include <vector>

using namespace std;

void quickSort(vector<int>& vec, int startPos, int endPos) {
	if (startPos >= endPos) return;

	int pivot = vec[(startPos + endPos) / 2];
	int left = startPos;
	int right = endPos;	

	while (left <= right) {
		while (vec[left] < pivot) left++;
		while (vec[right] > pivot) right--;

		if (left <= right) {
			int tmp = vec[left];
			vec[left] = vec[right];
			vec[right] = tmp;
			left++;
			right--;
		}
	}

	quickSort(vec, startPos, right);
	quickSort(vec, left, endPos);
}

int main() {
	int numCnt;
	cin >> numCnt;
	vector<int> vec;
	
	int input;
	while (numCnt--) {
		cin >> input;
		vec.push_back(input);
	}

	quickSort(vec, 0, vec.size() - 1);

	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << '\n';
	}

	return 0;
}