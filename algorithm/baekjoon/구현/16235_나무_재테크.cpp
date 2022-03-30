/*
* 백준 16235번 나무 재테크
* https://www.acmicpc.net/problem/16235
* 문제 유형
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Tree {
public:
	int r;
	int c;
	int age;
	Tree(int r, int c, int age) {
		this->r = r;
		this->c = c;
		this->age = age;
	}
};

int	widthHeight, firstTreeCnt, maxYear;
int currentFeed[11][11];
int feed[11][11];
int result;
queue<Tree> currentTreeQ[1012];
vector<Tree> deadTreeVec;
pair<int, int> direction[8] = {
	{-1, 0},
	{-1, 1},
	{0, 1},
	{1, 1},
	{1, 0},
	{1, -1},
	{0, -1},
	{-1, -1}
};

void spring() {
	vector<Tree> treeVec;
	for (int i = 1; i <= 1011; i++) {
		while (!currentTreeQ[i].empty()) {

			Tree tree = currentTreeQ[i].front();
			currentTreeQ[i].pop();
			int r = tree.r;
			int c = tree.c;

			if (currentFeed[r][c] < tree.age) {
				deadTreeVec.push_back(tree);
				continue;
			}
			else {
				currentFeed[r][c] -= tree.age;
				tree.age++;
				treeVec.push_back(tree);
			}
		}
	}

	for (Tree tree : treeVec) {
		currentTreeQ[tree.age].push(tree);
	}

}

void summer() {
	for (Tree tree : deadTreeVec) {
		int r = tree.r;
		int c = tree.c;
		int feed = tree.age / 2;

		currentFeed[r][c] += feed;
	}
	deadTreeVec.clear();
}

void fall() {
	for (int i = 1; i <= 1011; i++) {
		int size = currentTreeQ[i].size();
		while (size--) {
			Tree tree = currentTreeQ[i].front();
			currentTreeQ[i].pop();
			currentTreeQ[i].push(tree);
			if (tree.age % 5 != 0) {
				continue;
			}

			for (pair<int, int> dir : direction) {
				int newR = tree.r + dir.first;
				int newC = tree.c + dir.second;

				if (newR < 1 || newR > widthHeight || newC < 1 || newC > widthHeight) {
					continue;
				}

				currentTreeQ[1].push(Tree(newR, newC, 1));
			}
		}
	}
}

void winter() {
	for (int i = 1; i <= widthHeight; i++) {
		for (int j = 1; j <= widthHeight; j++) {
			currentFeed[i][j] += feed[i][j];
		}
	}
}

void fourSeason(int year) {
	if (year > maxYear) { return; }

	spring();
	summer();
	fall();
	winter();

	fourSeason(year + 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> widthHeight >> firstTreeCnt >> maxYear;

	for (int i = 1; i <= widthHeight; i++) {
		for (int j = 1; j <= widthHeight; j++) {
			cin >> feed[i][j];
			currentFeed[i][j] = 5;
		}
	}

	int x, y, age;

	for (int i = 1; i <= firstTreeCnt; i++) {
		cin >> x >> y >> age;
		currentTreeQ[age].push(Tree(x, y, age));
	}

	fourSeason(1);

	for (int i = 1; i <= 1011; i++) {
		result += currentTreeQ[i].size();
	}

	cout << result;

	return 0;
}