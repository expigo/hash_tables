#pragma once

#include<memory>
#include<string>
#include<limits>
#include<vector>
#include<iostream>

using item = unsigned long;


class Hash
{
public:
	static const size_t HASH_TABLE_SIZE = 1000003;


protected:
	double m_loadFactor = std::numeric_limits<double>::quiet_NaN();
	mutable int m_functionInvokeCounter = 0;
	mutable int m_searchMiss = 0;
	mutable int m_searchHit = 0;
	mutable int m_loadSentinel = 0;

private:
	//std::unique_ptr<item[]> hashTable{ nullptr };
	size_t hashTableSize = HASH_TABLE_SIZE;
	std::vector<item> hashTable;
	std::string method = "#NOVALUE";

private:
	virtual const unsigned long hashFunction(const item&, short i) const = 0;

public:
	explicit Hash(double lf, size_t size = HASH_TABLE_SIZE); //deafult size: 1000003 (first prime number above 1kk)
	//virtual void fillHashTable() final;
	bool insert(item);
	bool search(const item&) const;
	std::string getMethodName() const { return method; };
	void setMethodName(std::string s) { method = s; }
	size_t getSize() const { return hashTableSize; }
	bool overloadProtector() const;
	auto getLoadPercentage() const ->  decltype(m_loadFactor*hashTableSize);
	int getNoOfHashFunInvokes() const { return m_functionInvokeCounter; }
	void zeroCounter() const;

	void show() const
	{
		for (int i = 0; i < hashTableSize; ++i)
			std::cout << hashTable[i] << std::endl;
	}

	void test(std::vector<item>& instance, std::vector<item>& randNums);

	Hash() = delete;
	Hash(const item&) = delete;
	Hash(item&&) = delete;
	virtual ~Hash() = default;
};



class LinearProbing : public Hash
{
private:
	virtual const unsigned long hashFunction(const item&, short) const override final;

public:
	LinearProbing(double, size_t size = Hash::HASH_TABLE_SIZE);



	LinearProbing() = delete;
	LinearProbing(const LinearProbing&) = delete;
	LinearProbing(LinearProbing&&) = delete;

};


class DoubleHashing : public Hash
{
private:
	virtual const unsigned long hashFunction(const item&, short) const override final;

public:
	DoubleHashing(double, size_t size = Hash::HASH_TABLE_SIZE);
};