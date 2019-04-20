#ifndef __MEM_RUBY_STRUCTURES_MRUPOLICY_HH__
#define __MEM_RUBY_STRUCTURES_MRUPOLICY_HH__

#include "mem/ruby/structures/AbstractReplacementPolicy.hh"
#include "params/MRUReplacementPolicy.hh"

/* Simple true MRU replacement policy */

class MRUPolicy : public AbstractReplacementPolicy
{
  public:
    typedef MRUReplacementPolicyParams Params;
    MRUPolicy(const Params * p);
    ~MRUPolicy();

    void touch(int64_t set, int64_t way, Tick time);
    int64_t getVictim(int64_t set);
};

#endif // __MEM_RUBY_STRUCTURES_MRUPOLICY_HH__
