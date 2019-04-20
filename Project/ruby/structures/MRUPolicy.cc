#include "mem/ruby/structures/MRUPolicy.hh"

MRUPolicy::MRUPolicy(const Params * p)
    : AbstractReplacementPolicy(p)
{
}


MRUPolicy::~MRUPolicy()
{
}

MRUPolicy *
MRUReplacementPolicyParams::create()
{
    return new MRUPolicy(this);
}


void
MRUPolicy::touch(int64_t set, int64_t index, Tick time)
{
    assert(index >= 0 && index < m_assoc);
    assert(set >= 0 && set < m_num_sets);

    m_last_ref_ptr[set][index] = time;
}

int64_t
MRUPolicy::getVictim(int64_t set)
{
    Tick time, highest_time;
    int64_t highest_index = 0;
    highest_time = m_last_ref_ptr[set][0];

    for (unsigned i = 0; i < m_assoc; i++) {
        time = m_last_ref_ptr[set][i];

        if (time > highest_time) {
        	highest_index = i;
            highest_time = time;
        }
    }

    return highest_index;
}
