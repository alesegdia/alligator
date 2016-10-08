#pragma once

#include <random>
#include <memory>

class RNG
{
public:
	RNG(uint32_t seed) : m_gen(seed) {}

	static void Initialize( uint32_t seed );

	uint32_t nextInt( int min, int max )
	{
		uint32_t n = nextInt(max - min);
		return n + uint32_t(min);
	}

	uint32_t nextInt( int max );
	bool nextBool()
	{
		return nextInt(1) == 0;
	}

	static std::shared_ptr<RNG> rng;

private:
	std::mersenne_twister_engine<std::uint_fast32_t, 32, 624, 397, 31,
								 0x9908b0df, 11,
								 0xffffffff, 7,
								 0x9d2c5680, 15,
								 0xefc60000, 18, 1812433253> m_gen;
};
