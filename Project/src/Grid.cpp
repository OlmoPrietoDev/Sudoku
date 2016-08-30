#include "../include/Grid.h"
#include <iostream>

Grid::Grid(int typeOfSudoku) {

	haveWeAlreadyWonTheGame = false;

	switch (typeOfSudoku) {

		case 0:

		for (int i = 0; i < NUMBEROFCELLS; i++) {

			gridVector[i].number = 0;
			gridVector[i].isFixed = false;
		}

		numberOfCellsFillCorrectly = 0;
		
		break;

		case 1:
		{
		int v[] = {0,0,6,1,5,0,3,0,0,0,0,7,9,3,0,0,0,0,3,2,0,4,7,0,0,0,0,4,0,3,0,0,7,0,0,0,9,0,0,0,1,0,8,0,4,0,0,0,6,0,0,2,0,3,0,0,0,0,0,3,7,8,6,2,0,0,0,0,0,9,4,0,0,0,0,0,9,4,1,0,0};
		numberOfCellsFillCorrectly = 31;

		for (int i = 0; i < NUMBEROFCELLS; i++) {

			if (v[i] != 0) {

				gridVector[i].isFixed = true;
			}

			else {

				gridVector[i].isFixed = false;
			}

			gridVector[i].number = v[i];
		 }

		break;
		}
		case 2:
		{
		int v[] = {0,0,0,0,0,7,0,4,0,9,0,0,8,0,0,5,0,7,0,0,3,0,4,0,9,0,0,0,0,1,0,9,0,2,5,4,0,0,0,0,0,0,0,0,0,6,9,5,0,2,0,7,0,0,0,0,9,0,7,0,6,0,0,5,0,6,0,0,3,0,0,9,0,1,0,2,0,0,0,0,0};
		numberOfCellsFillCorrectly = 28;

		for (int i = 0; i < NUMBEROFCELLS; i++) {

			if (v[i] != 0) {

				gridVector[i].isFixed = true;
			}

			else {

				gridVector[i].isFixed = false;
			}

			gridVector[i].number = v[i];
		 }

		break;
		}

		case 3:
		{
		int v[] = {0,0,0,0,8,0,1,0,0,0,0,3,0,0,0,2,0,4,4,0,0,2,0,0,0,0,7,0,9,0,5,0,0,0,0,0,5,0,0,8,0,3,0,7,1,0,8,4,0,0,0,0,5,6,0,0,7,3,0,0,0,1,0,0,6,9,0,0,1,8,0,0,0,0,0,0,4,0,0,0,0};
		numberOfCellsFillCorrectly = 27;

		for (int i = 0; i < NUMBEROFCELLS; i++) {

			if (v[i] != 0) {

				gridVector[i].isFixed = true;
			}

			else {

				gridVector[i].isFixed = false;
			}

			gridVector[i].number = v[i];
		 }

		break;
		}

		case 4:
		{
		
		int v[] = {0,7,2,4,8,9,1,3,5,9,5,3,6,1,7,2,8,4,4,1,8,2,3,5,6,9,7,7,9,1,5,6,4,3,2,8,5,2,6,8,9,3,4,7,1,3,8,4,1,7,2,9,5,6,8,4,7,3,2,6,5,1,9,2,6,9,7,5,1,8,4,3,1,3,5,9,4,8,7,6,2};
		numberOfCellsFillCorrectly = 80;

		for (int i = 0; i < NUMBEROFCELLS; i++) {

			if (v[i] != 0) {

				gridVector[i].isFixed = true;
			}

			else {

				gridVector[i].isFixed = false;
			}

			gridVector[i].number = v[i];
		 }

		break;
		}
	}

	std::cout << "Generating Sudoku template" << std::endl;
}

short Grid::getLinealPosition(short x, short y) {

	return y * ROWSIZE + x;
}


void Grid::getMatrixPosition(short linealPosition, short &x, short &y) {

	y = linealPosition / 9;
	x = linealPosition % 9;
}

bool Grid::isCellFixed(short linealPosition) {

	return gridVector[linealPosition].isFixed;
}

short Grid::getCellNumber(short linealPosition) {

	return gridVector[linealPosition].number;
}

bool Grid::isTheGameWon()  {

	return haveWeAlreadyWonTheGame;
}

void Grid::reset() {

	for (int i = 0; i < NUMBEROFCELLS; i++) {

		if (gridVector[i].isFixed == false) {
			
			if(gridVector[i].number != 0) {

				numberOfCellsFillCorrectly--;
				gridVector[i].number = 0;
			}
		}
	}
}

// TODO abstraction
Grid::MovementReturnValue Grid::insertNumber(short linealPosition, short number) {

	MovementReturnValue mrv;
	mrv.cellID = -1;
	mrv.returnCode = UNDEFINED;

	if (gridVector[linealPosition].isFixed == true) {

		mrv.returnCode = MODIFIEDFIXEDPOSITION;
		return mrv;
	}

	if (number == 0) {

		mrv.returnCode = DELETEDCELLNUMBER;
    gridVector[linealPosition].number = number;
		return mrv;
	}

	if (numberRepeatedInRow(linealPosition, number)) {

		mrv.returnCode = NUMBERREPEATED;
		mrv.cellID = linealPosition;
		return mrv;
	}

	if (numberRepeatedInColumn(linealPosition, number)) {

		mrv.returnCode = NUMBERREPEATED;
		mrv.cellID = linealPosition;
		return mrv;
	}

	if (numberRepeatedInSquare(linealPosition, number)) {

		mrv.returnCode = NUMBERREPEATED;
		mrv.cellID = linealPosition;
		return mrv;
	}

	numberOfCellsFillCorrectly++;
	gridVector[linealPosition].number = number;

	if (numberOfCellsFillCorrectly == 81) {

		haveWeAlreadyWonTheGame = true;
	}

	mrv.returnCode = SUCCESS;
	return mrv;
}

bool Grid::numberRepeatedInRow(short &linealPosition, short number) {

	short x,y;
	getMatrixPosition(linealPosition,x,y);

	for (int i = linealPosition - x; i < (linealPosition - x + ROWSIZE); i++) {

		//std::cout << i << std::endl;

		if (number == gridVector[i].number && i != linealPosition) {

			std::cout << "repeated in row, position " << i << " number " << gridVector[i].number << std::endl;
			linealPosition = i;
			return true;
		}
	}

	return false;
}

bool Grid::numberRepeatedInColumn(short &linealPosition, short number) {

	short x,y;
	getMatrixPosition(linealPosition,x,y);

	for (int i = x; i <= NUMBEROFCELLS - ROWSIZE + x; i += 9) {

		//std::cout << i << std::endl;

		if (number == gridVector[i].number && i != linealPosition) {

			std::cout << "repeated in column, position " << i << " number ";
			std::cout << gridVector[i].number << std::endl;
			linealPosition = i;
			return true;
		}
	}

	return false;
}

bool Grid::numberRepeatedInSquare(short &linealPosition, short number) {

	short x,y;
	getMatrixPosition(linealPosition,x,y);

	short bigSquareX = x - (x % SQUARESIZE);
	short bigSquareY = y - (y % SQUARESIZE);

	for (int i = bigSquareX; i < bigSquareX + 3; i++) {
		for (int j = bigSquareY; j < bigSquareY + 3; j++) {

			//std::cout << i << j << std::endl;

			if (gridVector[getLinealPosition(i,j)].number == number && getLinealPosition(i,j) != linealPosition) {

					std::cout << "repeated in square, position " << i << "," << j << " number ";
					std::cout << gridVector[getLinealPosition(i,j)].number << std::endl;
					linealPosition = getLinealPosition(i,j);
					return true;
			}
		}
	}

	return false;
}

void Grid::printGrid() {

	for (int i = 0; i < NUMBEROFCELLS; i++) {

		if (i % ROWSIZE == 0) {

			std::cout << std::endl;
		}

		std::cout << " " << gridVector[i].number;
	}

	std::cout << std::endl;
}

Grid::~Grid() {


}