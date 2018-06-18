#include "xorshf96.h"

unsigned long xorshf96::x = 123456789;
unsigned long xorshf96::y = 362436069;
unsigned long xorshf96::z = 521288629;

xorshf96::~xorshf96()
{
}

unsigned long long xorshf96::operator()()
{
	unsigned long t;


	x ^= x << 16;
	x ^= x >> 5;
	x ^= x << 1;

	t = x;
	x = y;
	y = z;
	z = t ^ x ^ y;

	return z;
}
