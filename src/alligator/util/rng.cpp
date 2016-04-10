#include "rng.h"

std::shared_ptr<RNG> RNG::rng = nullptr;

void RNG::Initialize( uint32_t seed )
{
	RNG::rng = std::make_shared<RNG>(seed);
}

uint32_t RNG::nextInt(int max)
{
	return m_gen() % (max + 1);
}
