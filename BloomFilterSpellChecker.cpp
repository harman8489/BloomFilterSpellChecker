// BloomFilterSpellChecker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HashProviders.h"
#include "BloomFilter.h"
#include "SpellChecker.h"

int main()
{
	SpellChecker spellChecker;
	spellChecker.InitializeDictionary();
	bool b = spellChecker.FCheckSpelling("armanda");
	std::cout << b;
	b = spellChecker.FCheckSpelling("nope");
	std::cout << b;
	getchar();
	return 0;
}

