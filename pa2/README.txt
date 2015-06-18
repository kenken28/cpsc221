Yuxin Xu    37909090    m4j7
Rico Wen    32458119    w7c8


Note1: by passing a numerical argument when running the exacutable,
       i.e.:    ./hashDriver [numberOfEntries]
       the prcess will run the genData exacutable to generate a key list file named 
       'internal.txt' with specified number of entries. Then this file will be
       processd using the test cases given in the assignment description.
       
       if no argument was passed when executing, it will run a series 
       of default test cases, including the ones specified in the 
       assignment description, on a default file named 'example.txt'(10000 keys).
       
       run makefile first to compile both genData.cpp and hashDriver.cpp, so that genData
       could be used internally in hashDriver.

Note2: To use the constructor 'Hasher(char type, char crp, float lf, char* filename)',
       the input parameter 'filename' needs to be casted into (char*).
       e.g.:     Hasher('g', 'q', 0.25, (char*)"test.txt");



Assignment Questions:

1. For the poor hash function we used the method provided in the assignment description. 
   For the 2 good has functions we searched on Google for "hash function for string", 
   then we tested some of the decent looking results (Fowler–Noll–Vo hash function was 
   a good one, but we found better functions) by puting them in our finished code and 
   chose the best one in terms of probes per insertion. The load factor we used is as 
   requested in the assignment description, and the probes per insertion value we get 
   is in fact smaller than the expected value calculated using Donald Knuth's estimates.

2. As the load factor increases, the quality of the hash function drops. This is because 
   at the later stage of insertion, most cells will be filled with data, so the collision 
   rate of a insertion will be high, and for every next insertion, the collision rate will 
   be higher.

3. Our good hashing has better performance than the Knuth estimates. With a high load 
   factor (i.e. 0.75), it is 2 times as  efficient as the Knuth estimates; and at a low 
   load factor (i.e. 0.25), it is 10 times as efficient as the Knuth estimates. 


================= Table 1, Quadratic Probing ==================
[HashFunction]  [LoadFactor]    [HashTableSize] [RowsInserted]  [ProbesPerInsert]   [ExpectedProbes]
 Good            0.25            10000           2500            0.126400            1.15073
 Good            0.5             10000           5000            0.404400            1.38629
 Good            0.75            10000           7500            0.910933            1.84839
 Poor            0.25            10000           2500            32.824402           1.15073
 Poor            0.5             10000           5000            51.110802           1.38629
 Poor            0.75            10000           7500            76.944534           1.84839

================= Table 2, Double Hash Probing ==================
[HashFunction]  [LoadFactor]    [HashTableSize] [RowsInserted]  [ProbesPerInsert]
 Good            0.25            10000           2500            0.124000
 Good            0.5             10000           5000            0.379200
 Good            0.75            10000           7500            0.831467
 Poor            0.25            10000           2500            1.134000
 Poor            0.5             10000           5000            1.430200
 Poor            0.75            10000           7500            1.889867