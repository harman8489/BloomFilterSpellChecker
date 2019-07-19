#pragma once
#include "stdafx.h"
#include "md5.h"

class __declspec(novtable) IHashProvider
{
public:
	virtual std::vector<int> GetHashes(const std::string& input, int numHashes) = 0;
	virtual ~IHashProvider() noexcept {};
};

class Md5BasedHashProvider : public IHashProvider
{
public:
	std::vector<int> GetHashes(const std::string& input, int numHashes) override
	{
		std::vector<int> resultantHashes;
		resultantHashes.reserve(numHashes);
		auto hash = md5(input);
		int hashStringLength = hash.length() / numHashes;
		int start = 0;
		for (int i = 0; i < numHashes - 1; i++)
		{
			resultantHashes.emplace_back(atoi(hash.substr(start, hashStringLength).c_str()));
			start += hashStringLength;
		}

		resultantHashes.emplace_back(atoi(hash.substr(start).c_str()));
		return resultantHashes;
	}
};
