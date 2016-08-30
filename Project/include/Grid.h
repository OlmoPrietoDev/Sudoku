#ifndef __GRID_H__
#define __GRID_H__

#define NUMBEROFCELLS 81
#define ROWSIZE 9
#define SQUARESIZE 3

/* Return code */
#define MODIFIEDFIXEDPOSITION 1
#define DELETEDCELLNUMBER 2
#define NUMBERREPEATED 3
#define SUCCESS 4
#define UNDEFINED 5


class Grid {

public:

	struct MovementReturnValue {

		short cellID;
		int returnCode;
	};

	Grid();
	~Grid();

	short getLinealPosition(short x, short y);
	void getMatrixPosition(short linealPosition, short &x, short &y);
	bool isCellFixed(short linealPosition);
	short getCellNumber(short linealPosition);
	bool isTheGameWon();

	MovementReturnValue insertNumber(short linealPosition, short number);

	void printGrid();

private:

	struct Cell {

			short number;
			bool isFixed;
		};	

	Cell gridVector[NUMBEROFCELLS];	

	int numberOfCellsFillCorrectly;
	bool haveWeAlreadyWonTheGame;

	bool numberRepeatedInRow(short &linealPosition, short number);	
	bool numberRepeatedInColumn(short &linealPosition, short number);	
	bool numberRepeatedInSquare(short &linealPosition, short number);	
};



#endif //__GRID_H__