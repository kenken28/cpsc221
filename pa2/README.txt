Yuxin Xu    37909090    m4j7
Rico Wen    32458119    w7c8

Note1: 

Note2: To use the constructor 'Hasher(char type, char crp, float lf, char* filename)',
       the input parameter 'filename' needs to be casted into (char*).
       e.g.:     Hasher('g', 'q', 0.25, (char*)"test.txt");

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


Table 1, Quadratic Probing
[HashFunction]  [LoadFactor]    [HashTableSize] [RowsInserted]  [ProbesPerInsert]   [ExpectedProbes]
Good            0.25            10000           2500            0.1264              1.15073
Good            0.5             10000           5000            0.4044              1.38629
Good            0.75            10000           7500            0.910933            1.84839
Poor            0.25            10000           2500            32.8244             1.15073
Poor            0.5             10000           5000            51.1108             1.38629
Poor            0.75            10000           7500            76.9445             1.84839

Table 2, Double Hash Probing
[HashFunction]  [LoadFactor]    [HashTableSize] [RowsInserted]  [ProbesPerInsert]
Good            0.25            10000           2500            0.124
Good            0.5             10000           5000            0.3792
Good            0.75            10000           7500            0.831467
Poor            0.25            10000           2500            1.134
Poor            0.5             10000           5000            1.4302
Poor            0.75            10000           7500            1.88987