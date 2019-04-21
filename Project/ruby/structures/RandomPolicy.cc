#include "mem/ruby/structures/RandomPolicy.hh"
#include "debug/ACA.hh"

RandomPolicy::RandomPolicy(const Params * p) :
		AbstractReplacementPolicy(p) {
	DPRINTF(ACA, "Total number of sets in cache inside constructor== %s\n",
			m_num_sets);
}

RandomPolicy::~RandomPolicy() {
}

RandomPolicy *
RandomReplacementPolicyParams::create() {

	return new RandomPolicy(this);
}

void
RandomPolicy::touch(int64_t set, int64_t index, Tick time) {
	assert(index >= 0 && index < m_assoc);
	assert(set >= 0 && set < m_num_sets);
}

int64_t
RandomPolicy::getVictim(int64_t set) {
	return curTick() % m_assoc;
}
