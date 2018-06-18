
#pragma once
class xorshf96
{
public:
	xorshf96() = default;
	virtual ~xorshf96();
	unsigned long long operator()();

private:
	static unsigned long x;
	static unsigned long y;
	static unsigned long z;
};

