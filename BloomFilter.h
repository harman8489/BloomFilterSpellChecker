#pragma once
#include "stdafx.h"
#include "HashProviders.h"

class BloomFilter
{
public:
	BloomFilter(int numItemsToAdd, double errorThreshold,
		std::shared_ptr<IHashProvider> spHashProvider = std::make_shared<Md5BasedHashProvider>())
		: m_numItemsToAdd(numItemsToAdd),
		m_errorThreshold(errorThreshold),
		m_spHashProvider(spHashProvider) {}

	void Initialize()
	{
		auto filterSize = GetFilterSize();
		m_bitArray.resize(filterSize, false);
		m_numHashes = GetHashCount();
	}

	void Add(std::string item)
	{
		auto& hashes = m_spHashProvider->GetHashes(item, m_numHashes);
		for (auto hash : hashes)
		{
			m_bitArray[hash % m_bitArray.size()] = true;
		}
	}

	bool FItemExists(std::string item)
	{
		auto& hashes = m_spHashProvider->GetHashes(item, m_numHashes);
		for (auto hash : hashes)
		{
			if (!m_bitArray[hash % m_bitArray.size()])
				return false;
		}

		return true;
	}

private:

	// If n is number of items to be added and p is the false positive probability
	// then the formula used here is as follows
	// filterSize  = -(n* log(p)) / (log(2)^2)
	// Reference: Wikipedia
	int GetFilterSize() const noexcept
	{
		try
		{
			return -(m_numItemsToAdd * log(m_errorThreshold)) / std::pow(log(2), 2);
		}
		catch (...)
		{
			std::cout << "GetFilterSize failed with positive false probability" << m_errorThreshold
				<< "and number of items" << m_numItemsToAdd;
		}
	}

	// If m is the size of the bit array and n is the number of items to be added
	// then the formula used here is as follows
	// hashCount = (m/n) * log(2)
	// Reference: Wikipedia
	int GetHashCount() const noexcept
	{
		try
		{
			return std::ceil((m_bitArray.size() / (double)m_numItemsToAdd) * log(2));
		}
		catch (...)
		{
			std::cout << "GetHashCount failed with bit array size" << m_bitArray.size()
				<< "and number of items" << m_numItemsToAdd;
		}
	}

	int m_numItemsToAdd;
	double m_errorThreshold;
	int m_numHashes = 3;
	std::vector<bool> m_bitArray;
	std::shared_ptr<IHashProvider> m_spHashProvider;
};