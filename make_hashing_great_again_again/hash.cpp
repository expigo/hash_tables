#include "hash.h"
#include<iostream>
#include <algorithm>
#include <random>
#include <vector>

/* Ctor taking load factor and size of the hash table as parameters*/
Hash::Hash(double lf, size_t size) : hashTable(hashTableSize, 0), m_loadFactor(lf), hashTableSize(size)
{
}

/* method implementing insertion to the hash table*/
/* straight outta the pseudocode */
bool Hash::insert(item t)
{
	if (overloadProtector()) // overloadProtector takes care of fill rate of the hash table
	{
		for (int i = 0; i < hashTableSize; ++i)
		{
			item k = hashFunction(t, i);
			//std::cout << hashTable[k];
			if (hashTable[k] == 0)
			{
				hashTable[k] = t;
				++m_loadSentinel; // variable that protects the overload
				return true;
			}
		}

		return false;

	}

	else
	{
		std::cout << "Max Load reached!" << std::endl;
		return false;
	}
}

/* method implementing searching to the hash table*/
/* straight outta the pseudocode */
bool Hash::search(const item & t) const
{
	for (unsigned long i = 0; i < hashTableSize; ++i)
	{
		const item k = hashFunction(t, i);

		if (hashTable[k] == t)
			return true;
		else if (hashTable[k] == 0)
			return false;
	}
	return false;
}

/* method securing demaned table's load(fill)*/
bool Hash::overloadProtector() const
{
	if (m_loadSentinel % 100000 == 0)
		std::cout << m_loadSentinel << std::endl;
	return m_loadSentinel < m_loadFactor * hashTableSize;
}

auto Hash::getLoadPercentage() const ->  decltype(m_loadFactor*hashTableSize)
{
	return m_loadFactor * 100;
}

/* method that zeros the counters needed to obtain proper calculations*/
void Hash::zeroCounter() const
{
	m_functionInvokeCounter = 0;
	m_searchHit = 0;
	m_searchMiss = 0;
}

/* MOST IMPORTANT method for testin the hash table*/
void Hash::test(std::vector<item> &instance, std::vector<item> &randNums)
{

	// fill the hashTable with numbers
	std::vector<item> testHit;  // set for finding elements
	std::vector<item> testHitVec;
	//testHitVec.assign(testHit.begin(), testHit.end());

	int i = 0;

	// filling the hashTable with numbers
	while (insert(instance[i]))
	{
		testHit.push_back(instance[i]);				// inserted number stored in testHit vector to be searched later
		++i;
	}

	// the three lines below are C++17 method for shuffling the container filled with numbers
	// this is done to achieve 'more realistic' scenario when the inserted earlier numbers are NOT later being searched in the same order 
	// as they were actually inserted
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(testHit.begin(), testHit.end(), g);

	std::cout << "Hash table filled up to " << getLoadPercentage() << "%.\n"
		<< "Has function invoked " << m_functionInvokeCounter << " times" << std::endl;


	zeroCounter();

	//testing hit
	for (int i = 0; i < hashTableSize / 10; ++i)
	{
		if (search(testHit[i])) // checking if the numbers in testHit are stored in the hash table
								// and, as long as we assured that they are in line 92
								// we obtain 100% hit accuarcy
			m_searchHit++;
		else
			m_searchMiss++;
	}

	// so now we can calculate how many times, on average, was the hashing function called, to find the element in the hash table
	// that is for sure stored in it
	std::cout << "Search hit: \t" << m_searchHit << " (operations: " << m_functionInvokeCounter << ")" << std::endl;
	std::cout << "Search miss: \t" << m_searchMiss << std::endl;
	std::cout << "Average number of operations performed to find an element: \t"
		<< ((static_cast<double>(m_functionInvokeCounter) - m_searchMiss) / static_cast<double>(m_searchHit)) << std::endl; // FORMULA: (number of all hash function call - calls that didn't found nothing)/calls that returns searched value
	std::cout << std::endl;


	//std::vector<item> testMiss;

	//int it = 0;

	//for (auto i : instance)
	//{
	//	if (it < 200000) {
	//		if (std::find(testHit.begin(), testHit.end(), i) != testHit.end())
	//			testMiss.push_back(i);
	//	}
	//	else
	//		break;
	//}




	//testing miss
	zeroCounter();


	for (int i = 0; i < hashTableSize / 10; ++i)
	{
		if (search(randNums[i * 2])) // same as in :testing hits:, but now we are searching numbers that are not stored in the hash table,
									 // so that we can estimate the number of hash fuction calls to find out that the element is not stored
			m_searchHit++;
		else
			m_searchMiss++;
	}


	std::cout << "Search hit: \t" << this->m_searchHit << " (operations: " << m_functionInvokeCounter << ")" << std::endl;
	std::cout << "Search miss: \t" << this->m_searchMiss << std::endl;
	std::cout << "Average number of operations performed by the algorithm to find out that an element is stored in the table: \t"
		<< ((static_cast<double>(this->m_functionInvokeCounter) - m_searchHit) / this->m_searchMiss) << std::endl;
	std::cout << std::endl;

}

// ----------------- LINEAR PROBING ----------------

/* Concrete class Ctor taking load factor and size of the hash table as parameters*/
LinearProbing::LinearProbing(double lf, size_t size) : Hash(lf, size)
{
	setMethodName("Linear Probing");

}

const unsigned long LinearProbing::hashFunction(const item &t, short i) const
{
	++m_functionInvokeCounter;

	size_t tableSize = this->getSize();

	//const unsigned long value = ((x% tableSize) + i) % tableSize;

	return ((t % tableSize) + i) % tableSize;
}



// ----------------- DOUBLE HASHING ----------------
/* Concrete class Ctor taking load factor and size of the hash table as parameters*/
DoubleHashing::DoubleHashing(double lf, size_t size) : Hash(lf, size)
{
	setMethodName("Double Hashing");
}


const unsigned long DoubleHashing::hashFunction(const item & x, short i) const
{
	++m_functionInvokeCounter;


	size_t tableSize = this->getSize();


	unsigned long h1 = ((x % tableSize) + i);
	unsigned long h2 = ((static_cast<int>(0.5 * x) % tableSize) + i);
	//unsigned long h2 = ((static_cast<int>(0.616161 * x)) + i);

	unsigned long key = (h1 + i * h2) % getSize();

	//std::cout << key << std::endl;
	return key;
}
