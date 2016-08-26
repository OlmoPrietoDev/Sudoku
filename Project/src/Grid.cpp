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