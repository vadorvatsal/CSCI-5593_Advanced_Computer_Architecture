//============================================================================
// Name        : TestProject.cpp
// Author      : Ranjan
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
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

int main() {

	const int m_num_sets = 200, m_assoc = 16;
	Cell **cache = new Cell*[m_num_sets];
	int gTR, preGTR; // GTR Registers

	Partition *partition;

	for (int i = 0; i < m_num_sets; i++) {
		cache[i] = new Cell[m_assoc];
	}

	partition = getPartitions(m_num_sets);

	for (int i = 0; i < PARTS; i++) {
		cout << "Starting Set of Partition " << i << " = "
				<< partition[i].getStartSet() << endl;
		cout << "Ending Set of Partition " << i << " = "
				<< partition[i].getEndSet() << endl;
		partition[i].setPTR(cache, m_assoc);

		cout << "prePTR for Partition " << i << " = "
				<< partition[i].getPrePtr() << endl;
		cout << "pTR for Partition " << i << " = " << partition[i].getPtr()
				<< endl;

		cout
				<< "------------------------------------------------------------------------------------------"
				<< endl;

	}

	return 0;
}

