#include "Grid.h"
#include <iostream>

Grid::Grid() {

	for (int i = 0; i < 81; i++) {

		gridVector[i].number = 0;
		gridVector[i].isFixed = false;
	}

	gridVector[0].number = 8;
	gridVector[0].isFixed = true;

	std::cout << "Generating Sudoku test template" << std::endl;
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

bool Grid::insertNumber(short linealPosition, short number) {

	gridVector[linealPosition].number = number;

	bool isCorrectPosition = true;

	if (numberRepeatedInRow(linealPosition, number)) {

		isCorrectPosition = false;
	}

	if (numberRepeatedInColumn(linealPosition, number)) {

		isCorrectPosition = false;
	}

	if (numberRepeatedInSquare(linealPosition, number)) {

		isCorrectPosition = false;
	}

	return isCorrectPosition;
}

bool Grid::numberRepeatedInRow(short linealPosition, short number) {

	bool numberRepeated[ROWSIZE];

	for (int i = 0; i < ROWSIZE; i++) {

		numberRepeated[i] = false;
	}

	short x,y;
	getMatrixPosition(linealPosition,x,y);

	for (int i = 0; i < ROWSIZE; i++) {

		if (gridVector[getLinealPosition(i,y)].number != 0) {

			if (numberRepeated[gridVector[getLinealPosition(i,y)].number -1]){

				std::cout << "repeated in row, position " << i << "," << y << " number " << gridVector[getLinealPosition(i,y)].number << std::endl;
				return false;
			}

			else {

				numberRepeated[gridVector[getLinealPosition(i,y)].number -1] = true;
			}
		}
	}

	return true;
}

bool Grid::numberRepeatedInColumn(short linealPosition, short number) {

	bool numberRepeated[ROWSIZE];

	for (int i = 0; i < ROWSIZE; i++) {

		numberRepeated[i] = false;
	}

	short x,y;
	getMatrixPosition(linealPosition,x,y);

	for (int i = 0; i < ROWSIZE; i++) {

		if (gridVector[getLinealPosition(x,i)].number != 0) {

			if (numberRepeated[gridVector[getLinealPosition(x,i)].number -1]){

				std::cout << "repeated in column, position " << x << "," << i << " number ";
				std::cout << gridVector[getLinealPosition(x,i)].number << std::endl;
				return false;
			}

			else {

				numberRepeated[gridVector[getLinealPosition(x,i)].number -1] = true;
			}
		}
	}

	return true;
}

bool Grid::numberRepeatedInSquare(short linealPosition, short number) {

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