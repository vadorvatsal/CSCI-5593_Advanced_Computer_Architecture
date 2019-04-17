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

ADPGPolicy::ADPGPolicy(const Params * p) :
		AbstractReplacementPolicy(p) {
	DPRINTF(ACA, "Total number of sets in cache inside constructor== %s",
			m_num_sets);
	partition = getPartitions(m_num_sets);

	for (int i = 0; i < m_num_sets; i++) {
		cache[i] = new Cell[m_assoc];
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

	DPRINTF(ACA, "##########Touched <Set,Index> = <%d,%d>\n", set, index);

	//access_count++;

	m_last_ref_ptr[set][index] = time;
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

}

int64_t ADPGPolicy::getVictim(int64_t set) {
	Tick time, smallest_time;
	int64_t smallest_index = 0;
	smallest_time = m_last_ref_ptr[set][0];

	for (unsigned i = 0; i < m_assoc; i++) {
		time = m_last_ref_ptr[set][i];

		if (time < smallest_time) {
			smallest_index = i;
			smallest_time = time;
		}
	}
	access_count++;

	return smallest_index;

}

