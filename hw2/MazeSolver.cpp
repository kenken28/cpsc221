/* If file paths is not specified when running, the solver will solve a maze 
 * in the defaut file path "maze.txt".
 * To solve a maze file in a different file path, input the file path as a 
 * parameter when executing, e.g. if the file name is "myfile.txt", then:
 *
 * $ ./MazeSolver myfile.txt
 */
 
#include <iostream>
#include <fstream>
#include <string>

#define ARRAY_SIZE 15 // since we cannot declare array with non-constant size
				// we use a big enough global array M[15][15] to store the maze
using namespace std;

char M[ARRAY_SIZE][ARRAY_SIZE]; // the maze will be stored in this array

/* this function determins the next possible square 
 * given the cordinates of current square 
 */
void next_step( int y, int x, string path, int &pathNum) {
	/* the robot is now on square M[y][x], we mark the square 
	 * as # to indicate that it has been steped on already.
	 */
	M[y][x] = '#';
	
	/* check for square on the right to see if is the goal, 
	 * if it's the goal, print the full path. other wise, 
	 * check if it is a wall, if not, step onto it
	 */
	if ( M[y][x+1] == '?' ) {
		pathNum++;
		cout << "Path " << pathNum << ": " << path << endl;
	} else if ( M[y][x+1] != '#' ) {
		string path_Right (path);
		path_Right += ", ";
		path_Right += M[y][x+1];
		next_step( y, x+1, path_Right, pathNum );
	}
	
	/* check for square on the left, if it is not a wall, step onto it */
	if ( x > 0 && M[y][x-1] != '#' ) {
		string path_Left (path);
		path_Left += ", ";
		path_Left += M[y][x-1];
		next_step( y, x-1, path_Left, pathNum );
	}
	
	/* check for square on the bottom, if it is not a wall, step onto it */
	if ( M[y+1][x] != '#' ) {
		string path_Bottom (path);
		path_Bottom += ", ";
		path_Bottom += M[y+1][x];
		next_step( y+1, x, path_Bottom, pathNum );
	}
	
	/* check for square on the top, if it is not a wall, step onto it */
	if ( M[y-1][x] != '#' ) {
		string path_Top (path);
		path_Top += ", ";
		path_Top += M[y-1][x];
		next_step( y-1, x, path_Top, pathNum );
	}
}

/* this function finds all valid paths of the maze 
 * stored in the global array M[ARRAY_SIZE][ARRAY_SIZE]
 */
int generate_all_paths() {
	int y = 0, x = 0, yStarting = -1, pathNum = 0;
	char curretSquare;
	
	/* find starting point, print errot if there is no starting point*/
	while (y < ARRAY_SIZE) {
		if (M[y++][0] == 'S') {
			yStarting = y-1;
			break;
		}
	}
	if (yStarting == -1) {
		cout<< "Error: cannot find starting point." << endl;
		return -1;
	}
	y = yStarting;
	
	/* The robot will start from S and take a next step */
	string path("S");
	next_step( y, x, path, pathNum );
	
	return pathNum;
}

int main(int argc, char **argv) {
	int x=0, y=0 , pathsCount;
	char currentChar;
    ifstream mazefile;
	
    /* when running, first parameter is the file path, if no
     * parameter specified, "maze.txt" is the defaut file path
     */
    if (argc<2) {
        mazefile.open("maze.txt");
    } else {
        mazefile.open(argv[1]);
    }
	
	/* initialize all elements of the 2D array into '?' */
	for (int i=0; i<ARRAY_SIZE; i++){
		for (int j=0; j<ARRAY_SIZE; j++){
			M[i][j] = '?';
		}
	}
	
	/* open maze file and write it to global array M */
	cout << "Maze to solve:" << endl;
    if ( mazefile.is_open() ) {
		while ( !mazefile.eof() ) {
			mazefile.get(currentChar);
			cout << currentChar;
				if (currentChar == '\n'){
					y++;
					x = 0;
				} else {
					M[y][x++] = currentChar;
				}
		}
        mazefile.close();
    } else {
        cout << "Error, Unable to open file." << endl; 
		return -1;
	}
	
	/* call function to find all paths */
	pathsCount = generate_all_paths();
	
	if (pathsCount < 1) {		
		cout << "There is no valid path for this Maze." << endl;
	} else {
		cout << endl << "There are " << pathsCount 
			<< " valid path(s) for this maze." << endl;
	}

    return 0;
}
