#ifndef __GRID_H__
#define __GRID_H__

#define NUMBEROFCELLS 81
#define ROWSIZE 9
#define SQUARESIZE 3

class Grid {

public:
	Grid();
	~Grid();

	short getLinealPosition(short x, short y);
	void getMatrixPosition(short linealPosition, short &x, short &y);
	bool isCellFixed(short linealPosition);
	bool isCellCorrect(short linealPosition);
	short getCellNumber(short linealPosition);
	bool isTheGameWon();

	/*
	* Pre: the number can't be inserted in a fixed cell, the position
	* is inside the vector.
	* Insert a number in the grid, return true or false depending if
	* the number is in a correct position or not.
	*/
	bool insertNumber(short linealPosition, short number);

	void printGrid();

private:

	struct Cell {

			short number;
			bool isFixed;
			bool isCorrect;
		};

	Cell gridVector[NUMBEROFCELLS];	

	int numberOfCellsFillCorrectly;
	bool haveWeAlreadyWonTheGame;

	bool numberRepeatedInRow(short linealPosition, short number);	
	bool numberRepeatedInColumn(short linealPosition, short number);	
	bool numberRepeatedInSquare(short linealPosition, short number);	
};



#endif //__GRID_H__