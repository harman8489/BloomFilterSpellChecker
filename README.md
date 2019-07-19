# BloomFilterSpellChecker
 
The main classes and interfaces are as follows:
1. SpellChecker : The main spell checking class exposes Spell Checking functionality via FCheckSpelling method. Internally uses bloom filter to provide spelling check.
2. Bloom Filter: Takes as an input the number of inputs to be added and the probability of false positive(range 0 to 1). Provides functionality to the user to provide its own hash functionality by accepting IHashProvider during construction.
3. We are currently using Md5 based hashing technique which is provided by the Md5BasedHashProvider. Md5BasedHashProvider uses an opensource implementation provided by Frank Thilo


