#include "../include/Grid.h"
#include <iostream>

Grid::Grid() {

	for (int i = 0; i < NUMBEROFCELLS; i++) {

		gridVector[i].number = 0;
		gridVector[i].isFixed = false;
		gridVector[i].isCorrect = false;
	}

	gridVector[0].number = 8;
	gridVector[0].isFixed = true;
	gridVector[0].isCorrect = true;

	numberOfCellsFillCorrectly = 1;
	haveWeAlreadyWonTheGame = false;

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

bool Grid::isCellCorrect(short linealPosition) {

	return gridVector[linealPosition].isCorrect;
}

short Grid::getCellNumber(short linealPosition) {

	return gridVector[linealPosition].number;
}

bool Grid::isTheGameWon()  {

	return haveWeAlreadyWonTheGame;
}

// TODO abstraction
bool Grid::insertNumber(short linealPosition, short number) {

	if (gridVector[linealPosition].isFixed == true) {

		return false;
	}

	if (gridVector[linealPosition].isCorrect == true) {

		numberOfCellsFillCorrectly--;
	}

	gridVector[linealPosition].number = number;
	gridVector[linealPosition].isCorrect = false;

	if (number == 0) {

		return false;
	}

	if (numberRepeatedInRow(linealPosition, number)) {

		return false;
	}

	if (numberRepeatedInColumn(linealPosition, number)) {

		return false;
	}

	if (numberRepeatedInSquare(linealPosition, number)) {

		return false;
	}

	gridVector[linealPosition].isCorrect = true;
	numberOfCellsFillCorrectly++;

	if (numberOfCellsFillCorrectly == 81) {

		haveWeAlreadyWonTheGame = true;
	}

	return true;
}

bool Grid::numberRepeatedInRow(short linealPosition, short number) {

	short x,y;
	getMatrixPosition(linealPosition,x,y);

	for (int i = linealPosition - x; i < (linealPosition - x + ROWSIZE); i++) {

		//std::cout << i << std::endl;

		if (number == gridVector[i].number && i != linealPosition) {

			std::cout << "repeated in row, position " << i << " number " << gridVector[i].number << std::endl;
				return true;
		}
	}

	return false;
}

bool Grid::numberRepeatedInColumn(short linealPosition, short number) {

	short x,y;
	getMatrixPosition(linealPosition,x,y);

	for (int i = x; i <= NUMBEROFCELLS - ROWSIZE + x; i += 9) {

		//std::cout << i << std::endl;

		if (number == gridVector[i].number && i != linealPosition) {

			std::cout << "repeated in column, position " << i << " number ";
			std::cout << gridVector[i].number << std::endl;
			return true;
		}
	}

	return false;
}

bool Grid::numberRepeatedInSquare(short linealPosition, short number) {

	short x,y;
	getMatrixPosition(linealPosition,x,y);

	short bigSquareX = x - (x % SQUARESIZE);
	short bigSquareY = y - (y % SQUARESIZE);

	for (int i = bigSquareX; i < bigSquareX + 3; i++) {
		for (int j = bigSquareY; j < bigSquareY + 3; j++) {

			std::cout << i << j << std::endl;

			if (gridVector[getLinealPosition(i,j)].number == number && getLinealPosition(i,j) != linealPosition) {

					std::cout << "repeated in square, position " << i << "," << j << " number ";
					std::cout << gridVector[getLinealPosition(i,j)].number << std::endl;
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