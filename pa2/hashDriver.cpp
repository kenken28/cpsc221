 /* File hashDriver.cpp:
  *
  * by passing a numerical argument when running the exacutable,
  * i.e.:    ./hashDriver [numberOfEntries]
  * the prcess will run the genData exacutable to generate a key list file named 
  * 'internal.txt' with specified number of entries. Then this file will be
  * processd using the test cases given in the assignment description.
  * 
  * if no argument was passed when executing, it will run a series 
  * of default test cases, including the ones specified in the 
  * assignment description, on a default file named 'example.txt'(10000 keys).
  * 
  * run makefile first to compile both genData.cpp and hashDriver.cpp, so that genData
  * could be used internally in hashDriver.
  */

#include <iostream>
#include <string.h>
#include <fstream>
#include <math.h>
#include <cstdlib>
#include <unistd.h>


class TableEntry {
private:
    std::string key;
    int value;
public:
    TableEntry(std::string key, int value) {
        this->key = key;
        this->value = value;
    }
    
    std::string getKey() { return key; }
    int getValue() { return value; }
    
};


#define TABLE_SIZE 10000 // Change as necessary
class Hasher {
private:
    TableEntry** table;
    
    int numProbes; // total number of probes after finishing a table
    int numInserts; // total number of insertion
    int numEntires; // total number of entries recorded in the table (i.e.: insertion - removal)
    float loadFactor;
    bool isGoodHash; // if true use Good Hashing, if false use Poor Hashing
    bool isQuadProbe; // if true use Quadratic Probing, if false use Double Hashing
    
    // Define any other necessary helper functions that are not part of the public interface:
    
    // PRE: the input parameter key needs to be type string
    // POST: generates a hash tag
    // this is the poor hash function
    int poorHash(std::string key) {
        int hash = 0;
        int keyLen = key.length();
        for (int i=0; i<keyLen; ++i) {
            hash += key[i];
        }
        return hash % TABLE_SIZE;
    }
    
    // PRE: the input parameter key needs to be type string
    // POST: generates a hash tag
    // this is the good hash function, it will be used in double hashing
    int goodHash(std::string key) {
        unsigned long hash = 0;
        int keyLen = key.length();
        for (int i=0; i<keyLen; ++i) {
            hash = hash * 131 + key[i];
        }
        return hash % TABLE_SIZE;
    }
    
    // PRE: the input parameter key needs to be type string
    // POST: generates a hash tag
    // this is another hash function which will be used in double hashing
    int goodHash2(std::string key) {
        unsigned long hash = 0;
        int keyLen = key.length();
        for (int i=0; i<keyLen; ++i) {
            hash = (hash * 278 + key[i]) % TABLE_SIZE;
        }
        return hash;
    }
    
    /*

    */
    // PRE: specified hash table is created, mode has to be either :
    //      'i', 's' or 'r'.
    // POST: if the target index is found, it will be stored in the
    //      parameter 'index'
    /* this function does the probing step, it operates in 3 modes:
     * insert(i), search(s), remove(r). by passing it different parameters,
     * it will run on different mode.
     * 
     * it returns the number of probs and the hashed index number for different mode
     */
    int probeEntry(std::string key, int& index, char mode) {
        unsigned long hashKey, hashKey2, newHashKey, probe = 0;
        bool isFound = false;
        std::string tempKey;
        
        if (isGoodHash == true)
            hashKey = goodHash(key);
        else
            hashKey = poorHash(key);
        
        newHashKey = hashKey;
        
        if (isQuadProbe == false)
            hashKey2 = goodHash2(key);
        
        do {            
            tempKey.assign(table[newHashKey]->getKey());
            
            if (mode == 'i') {
                if (tempKey.compare(key) == 0 || tempKey.empty() || tempKey.compare("Deleted") == 0) {
                    index = newHashKey;
                    return probe;
                }
            } else if (mode == 's' || mode == 'r') {
                if (tempKey.compare(key) == 0) {
                    index = newHashKey;
                    return probe;
                }
            } else {
                return -1; // the mode variable is incorrect, return -1
            }
            
            ++probe;
            /* Depends on the isQuadProbe flag, different probing 
             * methods will be used. if isQuadProbe is true, then
             * use quad-probing. if isQuadProbe is false, then use
             * double-hash probing.
             */
            if (isQuadProbe == true)
                newHashKey = (hashKey + probe*probe) % TABLE_SIZE;
            else
                newHashKey = (hashKey + probe*hashKey2) % TABLE_SIZE;
        }
        while (probe < TABLE_SIZE);
        
        return -1; // no space is left or entry is not found, return -1
    }
    
public:
    // Define the necessary constructors (be sure to initialize your table entries to NULL):
    
    // PRE: all input parameters are valid
    // POST: create a Hasher type object and initialize variables
    /* this function constructs an empty hash table and
     * initializes every variables
     */
    Hasher(char type, char crp) {
        table = new TableEntry*[TABLE_SIZE]();
        for (int i=0; i<TABLE_SIZE; ++i) {
            table[i] = new TableEntry("",0);
        }
        numProbes = 0;
        numInserts = 0;
        numEntires = 0;
        loadFactor = -1; // Load Factor is not specified, assign it a negative value
        
        if (type == 'g'||type == 'G')
            isGoodHash = true;
        else if (type == 'b'||type == 'B')
            isGoodHash = false;
        else
            std::cout << "Input ERROR: Invalid hash type." << std::endl;
        
        if (crp == 'q'||crp == 'Q')
            isQuadProbe = true;
        else if (crp == 'd'||crp == 'D')
            isQuadProbe = false;
        else
            std::cout << "Input ERROR: Invalid probe type." << std::endl;
    }
    
    // PRE: all input parameters are valid. note: filename must be casted
    //      into (char*), e.g. Hasher('g', 'q', 0.25, (char*)"test.txt");
    // POST: create a Hasher type object with specified data file inerted
    /* this function constructs a hash table, initializes every variables,
     * and then insert entries read from [filename] into the table
     * the load of the table will be determined by the Load Factor(lf)
     */
    Hasher(char type, char crp, float lf, char* filename) {
        std::ifstream dataFile(filename);
        std::string key;
        int value;
        
        table = new TableEntry*[TABLE_SIZE]();
        for (int i=0; i<TABLE_SIZE; ++i) {
            table[i] = new TableEntry("",0);
        }
        numProbes = 0;
        numInserts = 0;
        numEntires = 0;
        loadFactor = lf;
        
        if (type == 'g'||type == 'G')
            isGoodHash = true;
        else if (type == 'b'||type == 'B')
            isGoodHash = false;
        else
            std::cout << "Input ERROR: Invalid hash type." << std::endl;
        
        if (crp == 'q'||crp == 'Q')
            isQuadProbe = true;
        else if (crp == 'd'||crp == 'D')
            isQuadProbe = false;
        else
            std::cout << "Input ERROR: Invalid probe type." << std::endl;
        
        if (dataFile.is_open()) {
            while (dataFile >> key >> value)
            {
                if (isFull()){
                    std::cout << "Number of entries reached TABLE_SIZE*loadFactor, stop inserting." << std::endl;
                    break;
                }
                insert(key,value);
            }
            dataFile.close();
        } else {
            std::cout << "ERROR opening file: ." << filename << std::endl;
        }
    }
    
    // Define the following functions:
    
    // PRE: specified hash table is constructed
    // POST: subscribe the index of the key if it exists
    /* this function search for specified key, returns
     * true if key is found, returns false otherwise
     */ 
    bool search(std::string key, int& subscript) {
        int hashIndex, probe = 0;
        
        probe = probeEntry(key, hashIndex, 's');
        
        if (probe == -1)
            return false;
        
        subscript = hashIndex;
        return true;
    }
    
    // PRE: specified hash table is constructed
    // POST: insert key if there is a space available
    /* this function insert a specified key and value, it 
     * returns true if key is inserted, returns false otherwise
     */ 
    bool insert(std::string key, int value) {
        int hashIndex, probe = 0;
        
        probe = probeEntry(key, hashIndex, 'i');
        
        if (probe == -1)
            return false;
        else
            numProbes += probe;
        
        table[hashIndex] = new TableEntry(key,value);
        ++numInserts;
        ++numEntires;
        
        return true;
    }
    
    // PRE: specified hash table is constructed
    // POST: delete key if it exists, else do nothing
    /* this function search for specified key and remove that entry,
     * it returns true if key is removed, returns false otherwise
     */ 
    bool remove(std::string key) {
        int hashIndex, probe = 0;
        
        probe = probeEntry(key, hashIndex, 'r');
        
        if (probe == -1)
            return false;
        
        table[hashIndex] = new TableEntry("Deleted",0);
        --numEntires;
        
        return true;
    }
    
    bool isFull() {
        return (numEntires >= int(TABLE_SIZE*loadFactor)) ?  true : false;
    }
    
    // Simply outputs the current contents of the table and the indices (you can write a loop
    // that just prints out the underlying array):
    // E.g.
    //    table->printTable() might generate:
    //        25  HBZEJKGA   1
    //        32  RHJMIVTA   2
    //
    void printTable() {
        for (int i=0; i<TABLE_SIZE; ++i) {
            std::cout << i << "  ";
            if (table[i]->getKey().compare(0,6,"Deleted") == 0)
                std::cout << table[i]->getKey() << "Deleted";
            else if (!table[i]->getKey().empty())
                std::cout << table[i]->getKey() << "  " << table[i]->getValue();
            std::cout << std::endl;
        }
    }

    // PRE: Hash table is constructed using :
    //          Hasher(char type, char crp, float lf, char* filename)
    // POST: N/A (Preconditions hold)
    void printTrial() {
        /* after printing out the table, some relevent parametes of the table
         * will be printed as well, note: if Load Factor is not specified, 
         * it will be equal to -1 
         */
        if (isGoodHash == true)
            std::cout << "[Good Hash]  ";
        else
            std::cout << "[Poor Hash]  ";
        
        std::cout << std::fixed << loadFactor << "      " 
                    << TABLE_SIZE << "             " 
                    << numInserts << "           " 
                    << (float)numProbes/(float)numInserts <<  "         ";
        
        if (isQuadProbe == true)
            std::cout << std::fixed << (1/loadFactor)*log(1/(1-loadFactor));
            
        std::cout << std::endl;
    }
    
    // Define any other necessary functions that are part of the public interface:
    /** Returns the key stored at given subscript. */
    const std::string getKey(const int subscript) {
        return table[subscript]->getKey();
    }
    
    /** Returns the data value at given subscript. */
    const int getValue(const int subscript) {
        return table[subscript]->getValue();
    }
    
    /** Returns the number of probes. */
    const int getProbes(void) {
        return numProbes;
    }
    
    /** Returns the hashTableSize. */
    const int getCapacity(void) {
        return TABLE_SIZE;
    }
    
    /** Returns the number of non-empty elements. */
    const int getSize(void) {
        return numEntires;
    }
    

    // Destructor-- do not alter.
    ~Hasher() 
    {
        for (int i = 0; i < TABLE_SIZE; i++)
            if (table[i] != NULL)
                delete table[i];
        delete[] table;
    }
    
};




/* this function finds current filepath
 * it is for locating and executing genData
 */
std::string getexepath () {
    char result[100];
    ssize_t count = readlink("/proc/self/exe", result, 100);
    return std::string( result, (count > 0) ? count : 0 );
}

// PRE: the 'filename' file is in correct key list format
/* this function is a series of test cases given in the assignment.
 * To use testCase bundle, pass the filename of the data Key list
 * e.g.   testCases((char*)"example.txt");
 */
void testCasesBundle (char* filename) {
    //tests for result table 1
    std::cout << std::endl << "========== Quadratic Probing HashKey file [" 
                << filename << "] ==========" << std::endl;
    Hasher* goodHashQ025 = new Hasher('g', 'q', 0.25, filename);
    Hasher* goodHashQ050 = new Hasher('g', 'q', 0.50, filename);
    Hasher* goodHashQ075 = new Hasher('g', 'q', 0.75, filename);
    Hasher* poorHashQ025 = new Hasher('b', 'q', 0.25, filename);
    Hasher* poorHashQ050 = new Hasher('b', 'q', 0.50, filename);
    Hasher* poorHashQ075 = new Hasher('b', 'q', 0.75, filename);
    
    std::cout << "            [LoadFactor] [HashTableSize] [RowsInserted] [ProbesPerInsert] [ExpectedProbes]" << std::endl;
    goodHashQ025->printTrial();
    goodHashQ050->printTrial();
    goodHashQ075->printTrial();
    poorHashQ025->printTrial();
    poorHashQ050->printTrial();
    poorHashQ075->printTrial();
    
    //tests for result table 2
    std::cout << std::endl << "========= Double Hash Probing HashKey file [" 
                << filename << "] =========" << std::endl;
    Hasher* goodHashD025 = new Hasher('g', 'd', 0.25, filename);
    Hasher* goodHashD050 = new Hasher('g', 'd', 0.50, filename);
    Hasher* goodHashD075 = new Hasher('g', 'd', 0.75, filename);
    Hasher* poorHashD025 = new Hasher('b', 'd', 0.25, filename);
    Hasher* poorHashD050 = new Hasher('b', 'd', 0.50, filename);
    Hasher* poorHashD075 = new Hasher('b', 'd', 0.75, filename);
    
    std::cout << "            [LoadFactor] [HashTableSize] [RowsInserted] [ProbesPerInsert]" << std::endl;
    goodHashD025->printTrial();
    goodHashD050->printTrial();
    goodHashD075->printTrial();
    poorHashD025->printTrial();
    poorHashD050->printTrial();
    poorHashD075->printTrial();
}

// test case function for insert
void testInsert (Hasher* hasher, std::string key, int val) {
    if(hasher->insert(key,val)) 
        std::cout << key << " Inserted" << std::endl;
    else
        std::cout << "Failed to insert " << key << std::endl;
}
// test case function for seach
void testSearch (Hasher* hasher, std::string key, int& index) {
    if(hasher->search(key,index)) 
        std::cout << key << " Found at " << index << std::endl;
    else
        std::cout << "Failed to find " << key << std::endl;
}

// test case function for remove
void testRemove (Hasher* hasher, std::string key) {
    if(hasher->remove(key)) 
        std::cout << key << " Removed" << std::endl;
    else
        std::cout << "Cannot delete/cannot find " << key << std::endl;
}




// **Sample** main function/driver-- THIS IS NOT A COMPLETE TEST SUITE
// YOU MUST WRITE YOUR OWN TESTS
// See assignment description.
int main( int argc, char* argv[])
{
    int subscript = -1;
    const char* charPath;
    std::string path;
    pid_t pid;
    
    /* if a numeric argument is passed to the exacutable, a new key list 
     * file 'internal.txt' will be generated and will be processed.
     * 
     * else run tests on default file 'example.txt'
     */
    if (argc > 1) {
        // first get the file path of genData
        path.assign(getexepath());
        path.erase(path.length()-10, 10);
        path.append("genData");
        charPath = path.c_str();
        
        pid = fork(); // create a child process to run genData
        switch (pid) {
            case -1: // failed to fork
                std::cout << "ERROR: fork() failed." << std::endl;
                exit(1);
            case 0: // in child process, run genData
                execl(charPath, charPath, argv[1], "internal.txt", NULL); /* Execute the program */
                std::cout << "ERROR: execl() failed!" << std::endl; /* execl doesn't return unless there's an error */
                exit(1);
            default: // in parent process, run test cases bundle on the generated file
                usleep( 10000 ); // wait for some time so the file is fully generated
                std::cout<< std::endl << "Generated Key list 'internal.txt' with " 
                            << atoi(argv[1]) << " entries. Start processing..." << std::endl;
                testCasesBundle((char*)"internal.txt");
        }
    } else { 
        std::cout << std::endl << "=================== Test Individual Functions ===================" << std::endl;
        // construct an empty hash tables and test different functions using this table
        Hasher* goodHashRP1 = new Hasher('g', 'd');
        
        testInsert(goodHashRP1,"ABCDEFGH",11); // insert ABCDEFGH
        
        testInsert(goodHashRP1,"AAAAAAAA",22); // insert AAAAAAAA
        
        testSearch(goodHashRP1,"AAAAAAAA",subscript); // seach for AAAAAAAA
        
        testRemove(goodHashRP1,"AAAAAAAA"); // remove AAAAAAAA
        
        testSearch(goodHashRP1,"AAAAAAAA",subscript); // seach for AAAAAAAA
        
        testInsert(goodHashRP1,"RAMDOMWD",33); // insert RAMDOMWD
        
        testSearch(goodHashRP1,"RAMDOMWD",subscript); // seach for RAMDOMWD
        std::cout << goodHashRP1->getKey(subscript) << " now has value: " 
                    << goodHashRP1->getValue(subscript) <<std::endl;
        
        testInsert(goodHashRP1,"RAMDOMWD",44);// update RAMDOMWD with a new value
        
        testSearch(goodHashRP1,"RAMDOMWD",subscript);// seach for the new RAMDOMWD
        std::cout << goodHashRP1->getKey(subscript) << " now has value: " 
                    << goodHashRP1->getValue(subscript) <<std::endl;
        
        testRemove(goodHashRP1,"ZZZZZZZZ");// remove ZZZBBZZZ which doesn't exist
        
        testSearch(goodHashRP1,"ABCDEFGH",subscript);// seach for ABCDEFGH
        
        
        /* in order to see the full talble after running hashDriver, 
         * make the TABLE_SIZE smaller, e.g. 20
         */ 
        //goodHashRP1->printTable(); // print this table
        
        
        testCasesBundle((char*)"example.txt"); // Process default file.
    }
    
    return 0;
}