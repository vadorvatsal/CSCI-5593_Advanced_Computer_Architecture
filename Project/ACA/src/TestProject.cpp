//============================================================================
// Name        : TestProject.cpp
// Author      : Ranjan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <random>
using namespace std;
#define PARTS 6

struct Cell {
	uint8_t priority :2;

	Cell() :
			priority(0) {
	}
};

class Partition {
	int ptr, prePTR;
	int startSet, endSet;

public:

	void init(int startSet, int endSet) {
		this->startSet = startSet;
		this->endSet = endSet;
	}

	void setPTR(Cell **cache, int m_assoc) {

		prePTR = ptr;
		ptr = 0;
		for (int i = startSet; i <= endSet; i++) {
			for (int j = 0; j < m_assoc; j++) {
				ptr += cache[i][j].priority + 1;
			}
		}

	}

	bool getPTRFluctuation() {
		if (ptr > prePTR)
			return 1; //increment in partition
		else
			return 0; //equals or decrement in partition value
	}

	int getEndSet() const {
		return endSet;
	}

	int getStartSet() const {
		return startSet;
	}

	int getPtr() const {
		return ptr;
	}

	int getPrePtr() const {
		return prePTR;
	}
};

uint8_t incrementPriority(uint8_t priority) {

	switch (priority) {
	case 0:
		return 1;
	case 1:
		return 2;
	case 2:
		return 3;
	case 3:
		return 3;
	}

}

uint8_t decrementPriority(uint8_t priority) {

	switch (priority) {
	case 0:
		return 0;
	case 1:
		return 0;
	case 2:
		return 1;
	case 3:
		return 2;
	}

}

Partition * getPartitions(int m_num_sets) {
	int partValue = m_num_sets / PARTS;
	int startSetIndex = 0, endSetIndex = (partValue - 1), i;

	static Partition partition[PARTS];
	for (i = 0; i < PARTS - 1; i++) {

		partition[i].init(startSetIndex, endSetIndex);
		startSetIndex = endSetIndex + 1;
		endSetIndex += partValue;

	}

	partition[i].init(startSetIndex, m_num_sets - 1);

	return partition;
}

void setGTR(Partition *partition, int gTR, int preGTR, int maxGTR) {
// Remove params from definition
	preGTR = gTR;
	gTR = 0;

	for (int i = 0; i < PARTS; i++) {
		gTR += partition[i].getPtr();
	}

	if (maxGTR < gTR) {
		maxGTR = gTR;
	}
}

int getGTR(int gTR) {
	// remove param from definition
	return gTR;
}

int getPreGTR(int preGTR) {
	// remove param from definition
	return preGTR;
}

void changeStateSet1(int state) {
	switch (state) {
	case 1: {
		state = 2;
		break;
	}
	case 2: {
		state = 3;
		break;
	}
	}
}

void changeStateSet2(int state) {
	switch (state) {
	case 3: {
		state = 4;
		break;
	}
	case 4: {
		state = 1;
		break;
	}
	}
}

void setState(Partition *partition, int gTR, int preGTR, int maxGTR,
		int access_count, int state, int m_num_sets) {
	// remove all params from definitions
	if (access_count % (m_num_sets / 2) == 0) {
		access_count = 0;

		if ((preGTR - gTR) > (maxGTR / 32)) {
			bool flag = 1;
			for (int i = 0; i < PARTS; i++) {
				if (partition[i].getPTRFluctuation()) {
					flag = 0;
				}
			}

			if (flag) {
				changeStateSet1(state);
			}

		} else if ((gTR - preGTR) > (maxGTR / 64)) {
			changeStateSet2(state);
		}
	}
}

int main() {

	const int m_num_sets = 200, m_assoc = 16;
	Cell **cache = new Cell*[m_num_sets];
	int gTR = 0, preGTR = 0, maxGTR = 0; // GTR Registers
	int access_count = 0, state = 0;

	Partition *partition;

	for (int i = 0; i < m_num_sets; i++) {
		cache[i] = new Cell[m_assoc];
	}

	partition = getPartitions(m_num_sets);
	for (int i = 0; i < PARTS; i++) {
		partition[i].setPTR(cache, m_assoc);
	}
	setGTR(partition, gTR, preGTR, maxGTR);
	setState(partition, gTR, preGTR, maxGTR, access_count, state, m_num_sets);

	std::vector<int> array;

	for (int i = 1; i < 10; i++) {
		array.reserve(i);
		array.push_back(i);
		for (int j = 0; j < array.size(); j++) {
			cout << array[j];
		}
		cout << "\n";
	}

	for (int i = 0; i < PARTS; i++) {
		cout << "Starting Set of Partition " << i << " = "
				<< partition[i].getStartSet() << endl;
		cout << "Ending Set of Partition " << i << " = "
				<< partition[i].getEndSet() << endl;

		cout << "prePTR for Partition " << i << " = "
				<< partition[i].getPrePtr() << endl;
		cout << "pTR for Partition " << i << " = " << partition[i].getPtr()
				<< endl;
		cout << "GTR for Partition " << i << " = " << getGTR(gTR) << endl;
		cout << "preGTR for Partition " << i << " = " << getPreGTR(preGTR)
				<< endl;

		cout
				<< "------------------------------------------------------------------------------------------"
				<< endl;

	}
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 16);

	for (int i = 0; i < 20; i++) {
		//int num = (rand() % (100 - 0 + 1)) + 0;
		cout << "Random Number " << distr(eng) << endl;
	}

	return 0;
}
