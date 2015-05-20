CC = g++
FLAGS = -o
File1 = Q2
File2 = Q3
File3 = CDate

all: $(File1) $(File2) $(File3)

Q2: $(File1).cpp
	$(CC) $(FLAGS) $(File1) $(File1).cpp

Q3: $(File2).cpp
	$(CC) $(FLAGS) $(File2) $(File2).cpp

CDate: $(File3).cpp $(File3).h
	$(CC) $(FLAGS) $(File3) $(File3).cpp $(File3).h
