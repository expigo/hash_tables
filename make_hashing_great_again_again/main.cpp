#include"hash.h"
#include<iostream>
#include<memory>
#include<string>
#include<vector>
#include<algorithm>

#include"xorshf96.h"




int main()
{

	static const int INSTANCE_SIZE = 10000000; // first prime number above 1000000

	xorshf96 gen; // functor for creating random generated numbers

				  //auto instance = std::make_unique<int[]>(INSTANCE_SIZE);

	std::vector<unsigned long> instance(INSTANCE_SIZE);			// vector of numbers that will be inserted into te has table
	std::vector<unsigned long> missRandom(INSTANCE_SIZE);		// vector of numbers (assumedly all different than these above)
																// that are going to be used to test misses
	std::generate(instance.begin(), instance.end(), gen);		// generating random numbers for instance
	std::generate(missRandom.begin(), missRandom.end(), gen);	// generating random numbers for missRandom

	//auto pInstance = std::make_shared<std::vector<unsigned long>>(instance);



	LinearProbing lp{ 0.9, 1000003 };
	DoubleHashing dp{ 0.9 };

	lp.test(instance, missRandom);
	std::cout << std::endl;
	dp.test(instance, missRandom);

	std::cin.get();
	std::cin.get();

	return 0;
}


