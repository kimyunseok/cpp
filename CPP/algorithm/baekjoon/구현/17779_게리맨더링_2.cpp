/*
* 백준 17779번 게리맨더링 2
* https://www.acmicpc.net/problem/17779
* 구현 / 시뮬레이션 / 브루트포스 알고리즘
*/
#include <iostream>
#include <cstring>
using namespace std;

int widthHeight;
int pointX, pointY, lengthD1, lengthD2;
int city[21][21];
int totalPopulation;
int population[6];
int ans = 40001;

void go() {
	int checkX = pointX;
	int checkY = pointY;
	//1번 선거구
	for (int r = 1; r < pointX + lengthD1; r++) {
		for (int c = 1; c <= checkY; c++) {
			if (r == checkX && c == checkY) {
				checkX++;
				checkY--;
			}
			else {
				population[1] += city[r][c];
			}
		}
	}

	checkX = pointX + 1;
	checkY = pointY + 1;
	//2번 선거구
	for (int r = 1; r <= pointX + lengthD2; r++) {
		for (int c = checkY; c <= widthHeight; c++) {
			if (r == checkX && c == checkY) {
				checkX++;
				checkY++;
				continue;
			}
			else {
				population[2] += city[r][c];
			}
		}
	}

	checkX = pointX + lengthD1;
	checkY = pointY - lengthD1;
	//3번 선거구
	for (int r = pointX + lengthD1; r <= widthHeight; r++) {
		for (int c = 1; c <= checkY; c++) {
			if (r == checkX && c == checkY) {
				if (checkY != pointY - lengthD1 + lengthD2 - 1) {
					checkX++;
					checkY++;
				}
				break; // 여기 break문 중요. checkY가 계속 증가한다. 이게 틀린 이유.
			}
			else {
				population[3] += city[r][c];
			}
		}
	}

	checkX = pointX + lengthD2 + lengthD1;
	checkY = pointY + lengthD2 - lengthD1;
	//4번 선거구
	for (int r = widthHeight; r > pointX + lengthD2; r--) {
		for (int c = checkY; c <= widthHeight; c++) {
			if (r == checkX && c == checkY) {
				checkX--;
				checkY++;
				continue;
			}
			else {
				population[4] += city[r][c];
			}
		}
	}

	//5번 선거구
	population[5] = totalPopulation - population[1] - population[2] - population[3] - population[4];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> widthHeight;

	for (int i = 1; i <= widthHeight; i++) {
		for (int j = 1; j <= widthHeight; j++) {
			cin >> city[i][j];
			totalPopulation += city[i][j];
		}
	}

	for (int d1 = 1; d1 <= widthHeight; d1++) {
		for (int d2 = 1; d2 <= widthHeight; d2++) {
			for (int x = 1; x <= widthHeight; x++) {
				for (int y = 1; y <= widthHeight; y++) {

					if (x + d1 + d2 <= widthHeight && 1 <= y - d1 && y + d2 <= widthHeight) {

						memset(population, 0, sizeof(population));
						pointX = x;
						pointY = y;
						lengthD1 = d1;
						lengthD2 = d2;

						go();

						int largestCity = 0;
						int smallestCity = 40001;
						for (int i = 1; i <= 5; i++) {
							largestCity = max(largestCity, population[i]);
							smallestCity = min(smallestCity, population[i]);
						}

						ans = min(ans, largestCity - smallestCity);
					}

				}
			}
		}
	}

	cout << ans;
}