#pragma once
#include "stdafx.h"
#include <fstream>

class SpellChecker
{
public:
	void InitializeDictionary()
	{
		std::vector<std::string> dict;
		std::fstream file;
		std::string fileName = "localDict.txt";
		file.open(fileName.c_str());
		std::string word;
		while (file >> word)
		{
			dict.emplace_back(word);
		}

		m_spBloomFilter = std::make_shared<BloomFilter>(dict.size(), m_errorThreshold);
		m_spBloomFilter->Initialize();
		for (auto& item : dict)
		{
			m_spBloomFilter->Add(item);
		}
	}

	bool FCheckSpelling(std::string str)
	{
		return m_spBloomFilter->FItemExists(str);
	}

private:
	std::shared_ptr<BloomFilter> m_spBloomFilter;
	double m_errorThreshold = 0.05;
};