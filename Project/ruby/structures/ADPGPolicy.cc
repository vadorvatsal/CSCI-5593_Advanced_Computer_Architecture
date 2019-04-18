/*
 * Copyright (c) 2013 Advanced Micro Devices, Inc
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Derek Hower
 */

#include "mem/ruby/structures/ADPGPolicy.hh"
#include "debug/ACA.hh"
#include <random>
#include <vector>
#include<string>
using namespace std;

ADPGPolicy::ADPGPolicy(const Params * p) :
		AbstractReplacementPolicy(p) {
	DPRINTF(ACA, "Cache <sets,associativity>  = <%d,%d>in cache", m_num_sets,
			m_assoc);
	partition = getPartitions(m_num_sets);

	for (int i = 0; i < m_num_sets; i++) {
		cache[i] = new Cell[m_assoc];
		//sub[i] = 0;
	}

	for (int i = 0; i < PARTS; i++) {

		DPRINTF(ACA, "Set of Partition %d = %d - %d  \n", i,
				partition[i].getStartSet(), partition[i].getEndSet());

		DPRINTF(ACA, "For Partition %d PTR = %d , prePTR = %d \n", i,
				partition[i].getPtr(), partition[i].getPrePtr());

		DPRINTF(ACA,
				"------------------------------------------------------------------------------------------");

	}
}

ADPGPolicy::~ADPGPolicy() {
}

ADPGPolicy *
ADPGReplacementPolicyParams::create() {
	return new ADPGPolicy(this);
}

void ADPGPolicy::touch(int64_t set, int64_t index, Tick time) {
	assert(index >= 0 && index < m_assoc);
	assert(set >= 0 && set < m_num_sets);

	if (replace_flag) {
		if (skip_call_count == 1) {
			skip_call_count = 0;
			replace_flag = 0;
			return;
		} else {
			skip_call_count++;
			executeInsertion(set, index);

		}
	} else {
		executePromotion(set, index);
	}

	access_count++;

	DPRINTF(ACA, "##########Touched <Set,Index> = <%d,%d>\n", set, index);

	for (int i = 0; i < PARTS; i++) {
		partition[i].setPTR(cache, m_assoc);
	}
	setGTR();
	setState();

	DPRINTF(ACA, "Access Iteration = %d\n", access_count);

	for (int i = 0; i < PARTS; i++) {

		DPRINTF(ACA, "For Partition %d PTR = %d , prePTR = %d \n", i,
				partition[i].getPtr(), partition[i].getPrePtr());

	}

	DPRINTF(ACA, "GTR = %d , preGTR = %d \n", getGTR(), getPreGTR());

	DPRINTF(ACA, "State = %d\n", state);

	DPRINTF(ACA,
			"------------------------------------------------------------------------------------------");
	executeDemotion(set);
}

int64_t ADPGPolicy::getVictim(int64_t set) {
	//selection Policy
	int64_t victim = executeSelection(set);
	victim_count++;
	if (victim_count == 3) {
		replace_flag = 1;
		DPRINTF(ACA, "##########Replaced <Set,Index> = <%d,%d>\n", set, victim);
		victim_count = 0;
		//demote value here
		demote(set);
	}

	return victim;

}

//Insertion Policy
void ADPGPolicy::insertionPolicy(uint8_t priority, int64_t set, int64_t index) {
	//assert(priority >= 0 && priority <= 3);
	cache[set][index].priority = priority;
}

//Promotion Policy HP
void ADPGPolicy::highPriority(int64_t set, int64_t index) {
	cache[set][index].priority = 3;
}

//Promotion Policy FP
void ADPGPolicy::frequencyPriority(int64_t set, int64_t index) {
	if (cache[set][index].priority != 3)
		cache[set][index].priority++;
}

//Demotion Policy HOA
void ADPGPolicy::halfOfAverage(int64_t set) {
	sub[set] = 0;
	for (int i = 0; i < m_assoc; i++) {
		sub[set] += cache[set][i].priority;
	}
	sub[set] = sub[set] / m_assoc / 2;
}

//Demotion Policy AVE
void ADPGPolicy::average(int64_t set) {
	sub[set] = 0;
	for (int i = 0; i < m_assoc; i++) {
		sub[set] += cache[set][i].priority;
	}
	sub[set] = sub[set] / m_assoc;
}

//Demote Policy
void ADPGPolicy::demote(int64_t set) {
	for (int i = 0; i < m_assoc; i++) {
		if (cache[set][i].priority - sub[set] < 0) {
			cache[set][i].priority -= sub[set];
		}
	}
}

//Selection Policy LS
int64_t ADPGPolicy::leftSideSelection(int64_t set) {
	uint8_t min = 5;
	int64_t index = 0;

	for (int i = 0; i < m_assoc; i++) {
		if (cache[set][i].priority < min) {
			min = cache[set][i].priority;
			index = i;
		}
	}
	return index;
}

//Selection Policy RS

int64_t ADPGPolicy::randomSelection(int64_t set) {
	uint8_t min = 5, count = 0;

	for (int i = 0; i < m_assoc; i++)
		if (cache[set][i].priority < min)
			min = cache[set][i].priority;

	std::vector < int64_t > array;

	for (int i = 1; i < m_assoc; i++) {
		if (cache[set][i].priority == min) {
			array.reserve(++count);
			array.push_back(i);
		}
	}

	if (array.size() > 1) {

		std::random_device rd; // obtain a random number from hardware
		std::mt19937 eng(rd()); // seed the generator
		std::uniform_int_distribution<> distr(0, m_assoc - 1);

		return array[distr(eng)];

	} else {
		return array[0];
	}
}

void ADPGPolicy::executeInsertion(int64_t set, int64_t index) {
	switch (state) {
	case 1: {
		insertionPolicy(2, set, index);
		break;
	}
	case 2: {
		insertionPolicy(2, set, index);
		break;
	}
	case 3: {
		insertionPolicy(0, set, index);
		break;
	}
	case 4: {
		insertionPolicy(0, set, index);
		break;
	}
	}
}

void ADPGPolicy::executePromotion(int64_t set, int64_t index) {
	switch (state) {
	case 1: {
		highPriority(set, index);
		break;
	}
	case 2: {
		highPriority(set, index);
		break;
	}
	case 3: {
		frequencyPriority(set, index);
		break;
	}
	case 4: {
		frequencyPriority(set, index);
		break;
	}
	}
}

void ADPGPolicy::executeDemotion(int64_t set) {
	switch (state) {
	case 1: {
		halfOfAverage(set);
		break;
	}
	case 2: {
		halfOfAverage(set);
		break;
	}
	case 3: {
		halfOfAverage(set);
		break;
	}
	case 4: {
		halfOfAverage(set);
		break;
	}
	}
}

int64_t ADPGPolicy::executeSelection(int64_t set) {
	switch (state) {
	case 1: {
		return leftSideSelection(set);
	}
	case 2: {
		return leftSideSelection(set);
	}
	case 3: {
		return randomSelection(set);
	}
	case 4: {
		return randomSelection(set);
	}
	}
	return 0;
}
