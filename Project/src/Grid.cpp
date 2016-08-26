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

	if (numberRepeatedInRow(linealPosition, number)) {

		return false;
	}

	if (numberRepeatedInColumn(linealPosition, number)) {

		return false;
	}

	if (numberRepeatedInSquare(linealPosition, number)) {

		return false;
	}

	return true;
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
				return true;
			}

			else {

				numberRepeated[gridVector[getLinealPosition(i,y)].number -1] = true;
			}
		}
	}

	return false;
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
				return true;
			}

			else {

				numberRepeated[gridVector[getLinealPosition(x,i)].number -1] = true;
			}
		}
	}

	return false;
}

bool Grid::numberRepeatedInSquare(short linealPosition, short number) {

	bool numberRepeated[ROWSIZE];

	for (int i = 0; i < ROWSIZE; i++) {

		numberRepeated[i] = false;
	}

	short x,y;
	getMatrixPosition(linealPosition,x,y);

	short bigSquareX = x - (x % SQUARESIZE);
	short bigSquareY = y - (y % SQUARESIZE);

	std::cout << bigSquareX << bigSquareY << std::endl;

	for (int i = bigSquareX; i < bigSquareX + 3; i++) {
		for (int j = bigSquareY; j < bigSquareY + 3; j++) {

			if (gridVector[getLinealPosition(i,j)].number != 0) {

				if (numberRepeated[gridVector[getLinealPosition(i,j)].number -1]){

					std::cout << "repeated in square, position " << i << "," << j << " number ";
					std::cout << gridVector[getLinealPosition(i,j)].number << std::endl;
					return true;
				}

				else {

					numberRepeated[gridVector[getLinealPosition(i,j)].number -1] = true;
				}
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