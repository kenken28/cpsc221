File1 = hashDriver
File2 = genData

all: $(File1) $(File2)

hashDriver: $(File1).cpp
	g++ -o $(File1) $(File1).cpp

genData: $(File2).cpp
	g++ -o $(File2) $(File2).cpp