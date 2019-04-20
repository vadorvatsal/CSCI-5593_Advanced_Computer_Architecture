#ifndef _MEM_RUBY_STRUCTURES_RANDOMPOLICY_HH_
#define _MEM_RUBY_STRUCTURES_RANDOMPOLICY_HH_

#include "mem/ruby/structures/AbstractReplacementPolicy.hh"
#include "params/RandomReplacementPolicy.hh"
//#include "debug/ACA.hh"

/* Simple true Random replacement policy */

class RandomPolicy: public AbstractReplacementPolicy {
public:
	typedef RandomReplacementPolicyParams Params;
	RandomPolicy(const Params * p);
	~RandomPolicy();

	void touch(int64_t set, int64_t way, Tick time);
	int64_t getVictim(int64_t set);
	int64_t randomVictim() const;

};
#endif // __MEM_RUBY_STRUCTURES_RANDOMPOLICY_HH__
