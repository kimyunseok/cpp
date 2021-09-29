#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
* 인하대학교 12171608 컴퓨터공학과 김현석
* DB Project 과제 : B+ Tree 구현
* 점수 : 85 / 100
*/

#define  rc_c_ptr reinterpret_cast<char*> // bin에서 stream은 문자 중심이므로 문자 이외 데이터를 파일에 읽고 쓸 땐 char*로 형변환 해야함.

class IndexEntry { // 논리프용 인덱스
public:
	int key;
	int bid;
	IndexEntry(int key, int nextLevelBID) {
		this->key = key;
		this->bid = nextLevelBID;
	}
};

class DataEntry { // 리프노드용 데이터
public:
	int key;
	int value;
	DataEntry(int key, int value) {
		this->key = key;
		this->value = value;
	}
};

class NonLeafNode { // 논리프노드, 인덱스 저장
public:
	NonLeafNode* parentNode;
	int bid; // 이노드의 id
	int nextLevelBID; // 아래 단계에 있는 노드의 bid 저장
	int depth;
	vector<IndexEntry> indexList;
};

class LeafNode { // 리프노드, 데이터 저장
public:
	NonLeafNode* parentNode;
	int bid; // 이 노드의 id
	int nextLeafNodeBID; // 다음에 있는 리프 노드의 bid
	int depth;
	vector<DataEntry> dataList;
};

bool IndexEntyCompare(IndexEntry i1, IndexEntry i2) {
	return i1.key < i2.key;
}

bool DataEntyCompare(DataEntry d1, DataEntry d2) {
	return d1.key < d2.key;
}

class BPlusTree {
public:
	fstream fs;
	string binaryFileName;
	int blockSize, rootID, depth; // 헤더에 들어있는 정보
	int dataNum, blockNum;
	
	void create(string binaryFileName, int blockSize) { // bin파일 생성, file header에 순서대로 block size, 0(최초 rootID), 0(최초 Depth) 기록
		int tmp = 0; // 최초 rootID와 depth는 0이다
		fs.open(binaryFileName, ios::out | ios::binary); // 어차피 파일이 없으면 open 함수가 자동으로 생성해준다.
		fs.write(rc_c_ptr(&blockSize), sizeof(int));
		fs.write(rc_c_ptr(&tmp), sizeof(int));
		fs.write(rc_c_ptr(&tmp), sizeof(int));
		fs.close();
	}

	// bin 파일 읽어서 파일 헤더정보 가져오기
	void readBinaryFile(string binaryFileName) {
		this->binaryFileName = binaryFileName;
		fs.open(binaryFileName, ios::in | ios::out | ios::binary);
		fs.read(rc_c_ptr(&blockSize), sizeof(int));
		fs.read(rc_c_ptr(&rootID), sizeof(int));
		fs.read(rc_c_ptr(&depth), sizeof(int));
		fs.seekg(0, std::ios::end);
		int fileLength = fs.tellg();
		blockNum = (fileLength - 12) / blockSize;
		dataNum = ((blockSize - 4) / 8);
		fs.close();
	}

	void insert(int key, int value) {
		readBinaryFile(binaryFileName); // 파일정보 가져옴
		
		if (rootID == 0) { // rootID가 0, 즉 데이터 최초삽입
			makeLeaf(key, value); // 최초 루트노드는 리프노드임
		}
		else {
			LeafNode leaf = findLeaf(key);
			leaf.dataList.push_back(DataEntry(key, value));
			sort(leaf.dataList.begin(), leaf.dataList.end(), DataEntyCompare);
			if (leaf.dataList.size() <= dataNum) { // 사이즈가 괜찮다면, 그냥 block에 덮어씌운다.
				fs.open(binaryFileName, ios::in | ios::out | ios::binary);
				fs.seekp(12 + ((leaf.bid - 1) * blockSize)); // leaf의 id로 포인터 이동
				
				//데이터 덮어씌우는 반복문
				for (DataEntry dataEntry : leaf.dataList) {
					fs.write(rc_c_ptr(&(dataEntry.key)), sizeof(int));
					fs.write(rc_c_ptr(&(dataEntry.value)), sizeof(int));
				}

				//데이터 안채워진 부분 0으로 채우는 반복문
				for (int i = 1; i <= dataNum - leaf.dataList.size(); i++) {
					int tmp = 0;
					fs.write(rc_c_ptr(&tmp), sizeof(int));
					fs.write(rc_c_ptr(&tmp), sizeof(int));
				}
				fs.write(rc_c_ptr(&(leaf.nextLeafNodeBID)), sizeof(int));
				fs.close();
			}
			else { //leaf의 사이즈가 한도초과했다면 split 해야한다.
				splitLeaf(leaf);
			}
		}
		// 삽입 끝나면 Header 정보 업데이트
		fs.open(binaryFileName, ios::in | ios::out | ios::binary);
		fs.write(rc_c_ptr(&blockSize), sizeof(int));
		fs.write(rc_c_ptr(&rootID), sizeof(int));
		fs.write(rc_c_ptr(&depth), sizeof(int));
		fs.close();
	}

	//새로운 LeafNode 만들기. 첫 값 빼고 나머지에는 다 0 넣기
	void makeLeaf(int key, int value) {
		rootID = 1;
		fs.open(binaryFileName, ios::in | ios::out | ios::binary);
		fs.seekp(12 + ((rootID - 1) * blockSize));
		int tmp = 0;
		fs.write(rc_c_ptr(&key), sizeof(int)); // 맨 앞 key값
		fs.write(rc_c_ptr(&value), sizeof(int)); // 맨 앞 value값
		for (int i = 1; i < dataNum; i++) { // 
			fs.write(rc_c_ptr(&tmp), sizeof(int)); //key값 최초로 0
			fs.write(rc_c_ptr(&tmp), sizeof(int)); //value값 최초로 0
		}
		fs.write(rc_c_ptr(&tmp), sizeof(int)); // nextBID 최초 0
		fs.close();
	}

	//새로운 NonLeafNode 만들기. 1 <= dataCount + 1
	void makeNonLeaf(int leftNodeBlockID, int key, int rightNodeBlockID) {
		rootID = ++blockNum;
		depth++;
		fs.open(binaryFileName, ios::in | ios::out | ios::binary);
		fs.seekp(12 + ((rootID - 1) * blockSize));
		fs.write(rc_c_ptr(&leftNodeBlockID), sizeof(int)); // 좌측 leafnode bid 값
		fs.write(rc_c_ptr(&key), sizeof(int)); // key 값
		fs.write(rc_c_ptr(&rightNodeBlockID), sizeof(int)); // 우측 leafnode bid 값
		int tmp = 0;
		for (int i = 1; i <= dataNum - 1; i++) {
			fs.write(rc_c_ptr(&tmp), sizeof(int));
			fs.write(rc_c_ptr(&tmp), sizeof(int));
		}
		fs.close();
	}

	/*
	리프노드 찾기
	1. 논리프노드 일경우(depth != B+Tree의 depth) : 
	논리프 노드가 <BID, key, BID ...>의 형태이므로 BID를 최초로 읽고 data개수만큼 key, BID 읽음.
	2. 찾고자 하는 key가 접근하는 논리프 노드의 key보다 작다면 현재 저장된 BID로 넘어감.
	(크거나 같다면 현재 key의 bid를 저장하고 다음 key로 넘어간다.)
	3. 해당 과정을 리프노드로 갈때까지 반복.
	4. 리프노드일 경우 : 리프 노드는<key, value ... nextLeafBID>의 형태이므로, key, value를 data 개수만큼 읽는다.
	5. 데이터들을 저장하고 리턴시킨다.
	*/
	LeafNode findLeaf(int key) {
		LeafNode leafNode;
		int curID = rootID;
		int depth = 0;
		NonLeafNode* parNode = NULL;
		while (depth != this->depth) { // 리프노드를 찾을때 까지 while문 반복
			NonLeafNode* curNonLeafNode = new NonLeafNode();
			curNonLeafNode->bid = curID;
			curNonLeafNode->depth = depth;
			curNonLeafNode->parentNode = parNode;
			fs.open(binaryFileName, ios::in | ios::out | ios::binary);
			fs.seekg(12 + ((curID - 1) * blockSize)); // 현재ID 블럭위치 찾음
			
			int tmp_nextBID = 0;
			
			fs.read(rc_c_ptr(&tmp_nextBID), sizeof(int)); // 현재 블럭의 nextLevelBID read
			curNonLeafNode->nextLevelBID = tmp_nextBID;

			for (int i = 1; i <= dataNum; i++) { // 블럭당 data 개수만큼 key, value값 읽음 이 때 0이 아닐때만 read
				int key, bid;
				fs.read(rc_c_ptr(&key), sizeof(int));
				fs.read(rc_c_ptr(&bid), sizeof(int));
				if (key == 0) { continue; }
				curNonLeafNode->indexList.push_back(IndexEntry(key, bid));
			}
			fs.close();

			//key 포함되는 곳의 BID (key의 왼쪽에 있는 BID로 가야한다.)
			int nextBID = curNonLeafNode->nextLevelBID;
			int count = 0;
			for (IndexEntry indexEntry : curNonLeafNode->indexList) {
				if (key < indexEntry.key) {
					curID = nextBID;
					depth++;
					parNode = curNonLeafNode;
					break;
				}
				else {
					nextBID = indexEntry.bid;
					count++;
				}
				if (count == curNonLeafNode->indexList.size()) {
					curID = nextBID;
					depth++;
					parNode = curNonLeafNode;
					break;
				}
			}
		}
		if (depth == this->depth) {
			fs.open(binaryFileName, ios::in | ios::out | ios::binary);
			fs.seekg(12 + ((curID - 1) * blockSize)); // 현재ID 블럭위치 찾음
			leafNode.bid = curID;
			leafNode.parentNode = parNode;
			leafNode.depth = this->depth;
			for (int i = 1; i <= dataNum; i++) {
				int key, value;
				fs.read(rc_c_ptr(&key), sizeof(int));
				fs.read(rc_c_ptr(&value), sizeof(int));
				if (key == 0) { continue; }
				leafNode.dataList.push_back(DataEntry(key, value));
			}
			int nextLeafNodeBID;
			fs.read(rc_c_ptr(&nextLeafNodeBID), sizeof(int));
			leafNode.nextLeafNodeBID = nextLeafNodeBID;
			fs.close();
		}
		return leafNode;
	}

	//리프노드 스플릿, 기존 리프노드 오른쪽 방향에 새로운 리프노드를 만든다.
	void splitLeaf(LeafNode leftLeaf) {
		LeafNode rightNewLeaf;
		rightNewLeaf.bid = ++blockNum;
		rightNewLeaf.nextLeafNodeBID = leftLeaf.nextLeafNodeBID;
		leftLeaf.nextLeafNodeBID = rightNewLeaf.bid;

		//새로 만든 오른쪽 노드에 기존 노드의 맨 끝부터 data를 넣는다.

		int splitSize = (dataNum % 2 == 0) ? dataNum / 2 : dataNum / 2 + 1;
		for (int i = 1; i <= splitSize; i++) {
			DataEntry data = leftLeaf.dataList.back();
			leftLeaf.dataList.pop_back();
			rightNewLeaf.dataList.push_back(data);
		}

		sort(rightNewLeaf.dataList.begin(), rightNewLeaf.dataList.end(), DataEntyCompare);

		/*
		좌측(기존) 노드 작성
		*/
		fs.open(binaryFileName, ios::in | ios::out | ios::binary);
		fs.seekp(12 + ((leftLeaf.bid - 1) * blockSize)); // leaf의 id로 포인터 이동
		
		//데이터 덮어씌우는 반복문
		for (DataEntry dataEntry : leftLeaf.dataList) {
			fs.write(rc_c_ptr(&(dataEntry.key)), sizeof(int));
			fs.write(rc_c_ptr(&(dataEntry.value)), sizeof(int));
		}
		//데이터 안채워진 부분 0으로 채우는 반복문
		for (int i = 1; i <= dataNum - leftLeaf.dataList.size(); i++) {
			int tmp = 0;
			fs.write(rc_c_ptr(&tmp), sizeof(int));
			fs.write(rc_c_ptr(&tmp), sizeof(int));
		}
		fs.write(rc_c_ptr(&(leftLeaf.nextLeafNodeBID)), sizeof(int));
		fs.close();

		/*
		우측에 새 노드 작성
		*/
		fs.open(binaryFileName, ios::in | ios::out | ios::binary);
		fs.seekp(12 + ((rightNewLeaf.bid - 1) * blockSize)); // leaf의 id로 포인터 이동
		
		//데이터 덮어씌우는 반복문
		for (DataEntry dataEntry : rightNewLeaf.dataList) {
			fs.write(rc_c_ptr(&(dataEntry.key)), sizeof(int));
			fs.write(rc_c_ptr(&(dataEntry.value)), sizeof(int));
		}
		//데이터 안채워진 부분 0으로 채우는 반복문
		for (int i = 1; i <= dataNum - rightNewLeaf.dataList.size(); i++) {
			int tmp = 0;
			fs.write(rc_c_ptr(&tmp), sizeof(int));
			fs.write(rc_c_ptr(&tmp), sizeof(int));
		}
		fs.write(rc_c_ptr(&(rightNewLeaf.nextLeafNodeBID)), sizeof(int));
		fs.close();

		int keyForNonLeaf = rightNewLeaf.dataList.front().key; // 논리프에 나타낼 key값
		//만일 기존 노드가 root 노드 였을 경우, 새로운 root노드를 만들어준다.
		if (leftLeaf.bid == rootID) {
			makeNonLeaf(leftLeaf.bid, keyForNonLeaf, rightNewLeaf.bid);
		}
		else { // 아니라면 좌측(기존) 노드의 부모에게 정보 전달
			NonLeafNode* parNode = leftLeaf.parentNode;
			parNode->indexList.push_back(IndexEntry(keyForNonLeaf, rightNewLeaf.bid));
			sort(parNode->indexList.begin(), parNode->indexList.end(), IndexEntyCompare);

			if (parNode->indexList.size() <= dataNum) { // 부모노드 사이즈 괜찮으면 그냥 덮어씌움.
				fs.open(binaryFileName, ios::in | ios::out | ios::binary);
				fs.seekp(12 + ((parNode->bid - 1) * blockSize));
				
				fs.write(rc_c_ptr(&parNode->nextLevelBID), sizeof(int)); // 좌측 포인터 먼저 적어줌

				for (IndexEntry indexEntry : parNode->indexList) {
					fs.write(rc_c_ptr(&(indexEntry.key)), sizeof(int));
					fs.write(rc_c_ptr(&(indexEntry.bid)), sizeof(int));
				}

				for (int i = 1; i <= dataNum - parNode->indexList.size(); i++) {
					int tmp = 0;
					fs.write(rc_c_ptr(&tmp), sizeof(int));
					fs.write(rc_c_ptr(&tmp), sizeof(int));
				}
				fs.close();
			}
			else { // 부모노드 사이즈 초과 시, split해 줘야 한다.
				splitNonLeaf(parNode);
			}
		}
	}

	// 논리프 스플릿. 오른쪽 방향에 하나 더 만든다.
	void splitNonLeaf(NonLeafNode* leftNonLeaf) {
		NonLeafNode* rightNonLeaf = new NonLeafNode();
		rightNonLeaf->bid = ++blockNum;
		int splitSize = (dataNum % 2 == 0) ? dataNum / 2 : dataNum / 2 + 1;

		for (int i = 1; i <= splitSize; i++) {
			IndexEntry index = leftNonLeaf->indexList.back();
			leftNonLeaf->indexList.pop_back();
			rightNonLeaf->indexList.push_back(index);
		}

		sort(rightNonLeaf->indexList.begin(), rightNonLeaf->indexList.end(), IndexEntyCompare);

		//좌측(기존) NonLeaf 먼저 작성
		fs.open(binaryFileName, ios::in | ios::out | ios::binary);
		fs.seekp(12 + ((leftNonLeaf->bid - 1) * blockSize));
		fs.write(rc_c_ptr(&leftNonLeaf->nextLevelBID), sizeof(int)); // 좌측 포인터 먼저 적어줌
		for (IndexEntry indexEntry : leftNonLeaf->indexList) {
			fs.write(rc_c_ptr(&(indexEntry.key)), sizeof(int));
			fs.write(rc_c_ptr(&(indexEntry.bid)), sizeof(int));
		}
		for (int i = 1; i <= dataNum - leftNonLeaf->indexList.size(); i++) {
			int tmp = 0;
			fs.write(rc_c_ptr(&tmp), sizeof(int));
			fs.write(rc_c_ptr(&tmp), sizeof(int));
		}
		fs.close();

		//우측 새 노드는 맨 왼쪽에 원래 들어있던 key(최소값)의 bid만 필요함(최소값은 root로 올라간다.)
		int keyForNonLeaf = rightNonLeaf->indexList.front().key;
		rightNonLeaf->nextLevelBID = rightNonLeaf->indexList.front().bid;
		rightNonLeaf->indexList.erase(rightNonLeaf->indexList.begin());

		//우측 NonLeaf 작성
		fs.open(binaryFileName, ios::in | ios::out | ios::binary);
		fs.seekp(12 + ((rightNonLeaf->bid - 1) * blockSize));
		fs.write(rc_c_ptr(&rightNonLeaf->nextLevelBID), sizeof(int)); // 좌측 포인터 먼저 적어줌
		for (IndexEntry indexEntry : rightNonLeaf->indexList) {
			fs.write(rc_c_ptr(&(indexEntry.key)), sizeof(int));
			fs.write(rc_c_ptr(&(indexEntry.bid)), sizeof(int));
		}
		for (int i = 1; i <= dataNum - rightNonLeaf->indexList.size(); i++) {
			int tmp = 0;
			fs.write(rc_c_ptr(&tmp), sizeof(int));
			fs.write(rc_c_ptr(&tmp), sizeof(int));
		}
		fs.close();
		//루트일 경우, 새로운 nonLeaf 생성(root 생성)
		if (leftNonLeaf->bid == rootID) {
			makeNonLeaf(leftNonLeaf->bid, keyForNonLeaf, rightNonLeaf->bid);
		}
		else { // 아니라면 기존의 부모에게 정보 전달
			NonLeafNode* parNode = leftNonLeaf->parentNode;
			parNode->indexList.push_back(IndexEntry(keyForNonLeaf, rightNonLeaf->bid));
			sort(parNode->indexList.begin(), parNode->indexList.end(), IndexEntyCompare);

			if (parNode->indexList.size() <= dataNum) { // 부모노드 사이즈 괜찮으면 그냥 덮어씌움.
				fs.open(binaryFileName, ios::in | ios::out | ios::binary);
				fs.seekp(12 + ((parNode->bid - 1) * blockSize));
				
				fs.write(rc_c_ptr(&parNode->nextLevelBID), sizeof(int)); // 좌측 포인터 먼저 적어줌

				for (IndexEntry indexEntry : parNode->indexList) {
					fs.write(rc_c_ptr(&(indexEntry.key)), sizeof(int));
					fs.write(rc_c_ptr(&(indexEntry.bid)), sizeof(int));
				}

				for (int i = 1; i <= dataNum - parNode->indexList.size(); i++) {
					int tmp = 0;
					fs.write(rc_c_ptr(&tmp), sizeof(int));
					fs.write(rc_c_ptr(&tmp), sizeof(int));
				}
				fs.close();
			}
			else { // 부모노드 사이즈 초과 시, split해 줘야 한다.
				splitNonLeaf(parNode);
			}
		}

	}

	//point search 메서드
	void search(int key, string outputFileName) {
		readBinaryFile(binaryFileName);
		LeafNode leaf = findLeaf(key);
		fs.open(binaryFileName, ios::in | ios::out | ios::binary);
		fs.seekg(12 + ((leaf.bid - 1) * blockSize));
		fstream out(outputFileName, ios::app);
		for (int i = 0; i < dataNum; i++) {
			int _key = 0;
			int _value = 0;
			fs.read(rc_c_ptr(&_key), sizeof(int));
			fs.read(rc_c_ptr(&_value), sizeof(int));
			if (_key == key) {
				out << _key << "," << _value << "\n";
			}
		}
		fs.close();
		out.close();
	}

	//range search
	void rangeSearch(int start, int end, string outputFileName) {
		readBinaryFile(binaryFileName); 
		LeafNode leaf = findLeaf(start);
		fs.open(binaryFileName, ios::in | ios::out | ios::binary);
		fs.seekg(12 + ((leaf.bid - 1) * blockSize));
		fstream out(outputFileName, ios::app);
		int _key = 0;
		int _value = 0;
		int idx = 1;
		int nextBID = 0;
		fs.read(rc_c_ptr(&_key), sizeof(int));
		fs.read(rc_c_ptr(&_value), sizeof(int));
		while (_key < start || _key == 0) {
			if (idx == dataNum) {
				idx = 1;
				fs.read(rc_c_ptr(&nextBID), sizeof(int));
				fs.seekg(12 + ((nextBID - 1) * blockSize));
				fs.read(rc_c_ptr(&_key), sizeof(int));
				fs.read(rc_c_ptr(&_value), sizeof(int));
			} else {
				idx++;
				fs.read(rc_c_ptr(&_key), sizeof(int));
				fs.read(rc_c_ptr(&_value), sizeof(int));
			}
		}
		while (_key >= start && _key <= end) {
			out << _key << "," << _value << "\t";
			if (idx == dataNum) {
				idx = 1;
				fs.read(rc_c_ptr(&nextBID), sizeof(int));
				fs.seekg(12 + ((nextBID - 1) * blockSize));
				fs.read(rc_c_ptr(&_key), sizeof(int));
				fs.read(rc_c_ptr(&_value), sizeof(int));
			}
			else {
				idx++;
				fs.read(rc_c_ptr(&_key), sizeof(int));
				fs.read(rc_c_ptr(&_value), sizeof(int));
			}
			if (_key == 0) {
				while (idx < dataNum) {
					idx++;
					fs.read(rc_c_ptr(&_key), sizeof(int));
					fs.read(rc_c_ptr(&_value), sizeof(int));
				}
				idx = 1;
				fs.read(rc_c_ptr(&nextBID), sizeof(int));
				fs.seekg(12 + ((nextBID - 1) * blockSize));
				fs.read(rc_c_ptr(&_key), sizeof(int));
				fs.read(rc_c_ptr(&_value), sizeof(int));
			}
		}
		out << "\n";
		fs.close();
		out.close();
	}

	void print(string outputFileName) {
		readBinaryFile(binaryFileName);
		fs.open(binaryFileName, ios::in | ios::out | ios::binary);
		fs.seekg(12 + ((rootID - 1) * blockSize));
		fstream out(outputFileName, ios::app);
		out << "<0>\n\n";
		if (this->depth == 0) {
			for (int i = 1; i <= dataNum; i++) {
				int _key = 0;
				int _value = 0;
				fs.read(rc_c_ptr(&_key), sizeof(int));
				fs.read(rc_c_ptr(&_value), sizeof(int));
				if (_key == 0) { continue; }
				if (i == 1) { out << _key; }
				else { out << ", " << _key; }
			}
		}
		else {
			int _key = 0;
			int _value = 0;
			int _bid = 0;
			fs.read(rc_c_ptr(&_bid), sizeof(int));
			vector<int> level_one_bid;
			level_one_bid.push_back(_bid);			
			for (int i = 1; i <= dataNum; i++) {
				fs.read(rc_c_ptr(&_key), sizeof(int));
				fs.read(rc_c_ptr(&_bid), sizeof(int));
				if (_key == 0) { continue; }
				if (i == 1) { out << _key; }
				else { out << ", " << _key; }
				level_one_bid.push_back(_bid);
			}
			out << "\n\n<1>\n\n";
			for (int i = 0; i < level_one_bid.size(); i++) {
				fs.seekg(12 + ((level_one_bid[i] - 1) * blockSize));
				for (int j = 1; j <= dataNum; j++) {
					if (this->depth > 1) {
						fs.read(rc_c_ptr(&_bid), sizeof(int));
					}
					fs.read(rc_c_ptr(&_key), sizeof(int));
					fs.read(rc_c_ptr(&_value), sizeof(int));
					if (_key == 0) { continue; }
					if (i == 0 && j == 1) { out << _key; }
					else { out << ", " << _key; }
				}
			}
		}
		fs.close();
		out.close();
	}
};

/*
command line으로 매개변수를 바로 넘기는 것은 argc와 argv를 사용하는것. 
argc는 매개변수의 개수. argv는 매개변수가 chgr형으로 저장되는 변수
*/
int main(int argc, char* argv[]) {
	char command = argv[1][0];
	fstream fs;
	BPlusTree bpt;
	switch (command)
	{
	case 'c':// bin 파일 생성
		bpt.create(argv[2], stoi(argv[3]));
		break;
	case 'i': // 삽입
		fs.open(argv[3]);
		bpt.binaryFileName = argv[2];
		if (fs.is_open()) {
			char* input = new char[24];
			while (fs >> input) {
				int key = stoi(strtok(input, ","));
				int value = stoi(strtok(NULL, " "));
				bpt.insert(key, value);
			}
		}
		fs.close();
		break;
	case 's':// 키와 VALUE값 탐색
		fs.open(argv[3]);
		bpt.binaryFileName = argv[2];
		if (fs.is_open()) {
			char* input = new char[24];
			while (fs >> input) {
				bpt.search(stoi(input), argv[4]);
			}
		}
		fs.close();
		break;
	case 'r':// 범위탐색
		fs.open(argv[3]);
		bpt.binaryFileName = argv[2];
		if (fs.is_open()) {
			char* input = new char[24];
			while (fs >> input) {
				int start = stoi(strtok(input, ","));
				int end = stoi(strtok(NULL, " "));
				bpt.rangeSearch(start, end, argv[4]);
			}
		}
		break;
	case 'p': // 프린트
		fs.open(argv[3]);
		bpt.binaryFileName = argv[2];
		bpt.print(argv[3]);
		break;
	}
	return 0;
}