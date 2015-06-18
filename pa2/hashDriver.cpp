// File hashDriver.cpp:
// Place your identifying information here CLEARLY.

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>


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
        int hashKey, hashKey2, newHashKey, probe = 0;
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

    // PRE:	Hash table is constructed using :
    // 		Hasher(char type, char crp, float lf, char* filename)
    // POST: N/A (Preconditions hold)
    void printTrial() {
        /* after printing out the table, some relevent parametes of the table
         * will be printed as well, note: if Load Factor is not specified, 
         * it will be equal to -1 
         */
        if (isGoodHash == true)
            std::cout << "[HashFunction: Good] ";
        else
            std::cout << "[HashFunction: Poor] ";
        
        std::cout << "[LoadFactor: " << loadFactor
                    << "] [HashTableSize: " << TABLE_SIZE
                    << "] [RowsInserted: " << numInserts 
                    << "] [ProbesPerInsert: " << (float)numProbes/(float)numInserts;
        
        if (isQuadProbe == true)
            std::cout << "] [ExpectedProbes: " 
                        << (1/loadFactor)*log(1/(1-loadFactor));
            
        std::cout << "]" << std::endl;
    }
    
    // Define any other necessary functions that are part of the public interface:
    
    // Destructor-- do not alter.
    ~Hasher() 
    {
        for (int i = 0; i < TABLE_SIZE; i++)
            if (table[i] != NULL)
                delete table[i];
        delete[] table;
    }
    
};



// **Sample** main function/driver-- THIS IS NOT A COMPLETE TEST SUITE
// YOU MUST WRITE YOUR OWN TESTS
// See assignment description.
int main( int argc, char* argv[])
{
    int subscript = -1;
    
    /*
    // Generate empty hash tables and test different functions using this table
    Hasher* goodHashRP1 = new Hasher('g', 'd');
    
    // insert ABCDEFGH
    if(goodHashRP1->insert("ABCDEFGH",213)) 
        std::cout << "Inserted" << std::endl;
    else
        std::cout << "Failed to insert" << std::endl;
    
    // insert AAAAAAAA
    if(goodHashRP1->insert("AAAAAAAA",32)) 
        std::cout << "Inserted" << std::endl;
    else
        std::cout << "Failed to insert" << std::endl;
    
    // insert HELLOMAN
    if(goodHashRP1->insert("HELLOMAN",181)) 
        std::cout << "Inserted" << std::endl;
    else
        std::cout << "Failed to insert" << std::endl;
    
    // seach for HELLOMAN
    if(goodHashRP1->search("HELLOMAN",subscript)) 
        std::cout << "Found at " << subscript << std::endl;
    else
        std::cout << "Failed to find" << std::endl;
    
    // remove AAAAAAAA
    if(goodHashRP1->remove("AAAAAAAA")) 
        std::cout << "Removed" << std::endl;
    else
        std::cout << "Not deleted/not found" << std::endl;
    
    // remove HELLOMAN
    if(goodHashRP1->remove("HELLOMAN")) 
        std::cout << "Removed" << std::endl;
    else
        std::cout << "Not deleted/not found" << std::endl;
    
    // insert HELLOMAN again with a different value
    if(goodHashRP1->insert("HELLOMAN",45)) 
        std::cout << "Inserted" << std::endl;
    else
        std::cout << "Failed to insert" << std::endl;
    
    // seach for ABCDEFGH
    if(goodHashRP1->search("ABCDEFGH",subscript)) 
        std::cout << "Found at " << subscript << std::endl;
    else
        std::cout << "Failed to find" << std::endl;
    
    // insert RAMDOMWD
    if(goodHashRP1->insert("RAMDOMWD",93)) 
        std::cout << "Inserted" << std::endl;
    else
        std::cout << "Failed to insert" << std::endl;
    
    // insert RAMDOMWD again
    if(goodHashRP1->insert("RAMDOMWD",168)) 
        std::cout << "Inserted" << std::endl;
    else
        std::cout << "Failed to insert" << std::endl;
    
    // remove ZZZBBZZZ which doesn't exist
    if(goodHashRP1->remove("ZZZBBZZZ")) 
        std::cout << "Removed" << std::endl;
    else
        std::cout << "Not deleted/not found" << std::endl;
    //print this table
    goodHashRP1->printTable();
    */
    
    
    //tests for result table 1
    Hasher* goodHashQ025 = new Hasher('g', 'q', 0.25, (char*)"test.txt");
    Hasher* goodHashQ050 = new Hasher('g', 'q', 0.50, (char*)"test.txt");
    Hasher* goodHashQ075 = new Hasher('g', 'q', 0.75, (char*)"test.txt");	
    Hasher* poorHashQ025 = new Hasher('b', 'q', 0.25, (char*)"test.txt");
    Hasher* poorHashQ050 = new Hasher('b', 'q', 0.50, (char*)"test.txt");
    Hasher* poorHashQ075 = new Hasher('b', 'q', 0.75, (char*)"test.txt");
    
    goodHashQ025->printTrial();
    goodHashQ050->printTrial();
    goodHashQ075->printTrial();
    poorHashQ025->printTrial();
    poorHashQ050->printTrial();
    poorHashQ075->printTrial();
    
    //tests for result table 2
    Hasher* goodHashD025 = new Hasher('g', 'd', 0.25, (char*)"test.txt");
    Hasher* goodHashD050 = new Hasher('g', 'd', 0.50, (char*)"test.txt");
    Hasher* goodHashD075 = new Hasher('g', 'd', 0.75, (char*)"test.txt");	
    Hasher* poorHashD025 = new Hasher('b', 'd', 0.25, (char*)"test.txt");
    Hasher* poorHashD050 = new Hasher('b', 'd', 0.50, (char*)"test.txt");
    Hasher* poorHashD075 = new Hasher('b', 'd', 0.75, (char*)"test.txt");
    
    goodHashD025->printTrial();
    goodHashD050->printTrial();
    goodHashD075->printTrial();
    poorHashD025->printTrial();
    poorHashD050->printTrial();
    poorHashD075->printTrial();
    
    return 0;
}