CPSC221 Programming Assignment 1

[Name]		[Student#]		[Lab section]	[4-char ID]
Yuxin Xu	37909090		L0C				m4j7
Rico Wen	32458119		L0C				w7c8

Since there is only on starting point and no loop in the maze, we can see the paths of the maze as a tree. To find all possible path from the root to the leaves which are at the rightmost edge of the maze, we use a recursive function that calls itself when advancing down each branch. When reaching a leaf is located at the rightmost edge of the maze, the path taken to reach the leaf will be printed.
