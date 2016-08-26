#ifndef __GRID_H__
#define __GRID_H__

#define NUMBEROFCELLS 81
#define ROWSIZE 9

class Grid {

public:
	Grid();
	~Grid();

	short getLinealPosition(short x, short y);
	void getMatrixPosition(short linealPosition, short &x, short &y);
	bool isCellFixed(short linealPosition);
	short getCellNumber(short linealPosition);

private:

	struct Cell {

			short number;
			bool isFixed;
		};

	Cell gridVector[NUMBEROFCELLS];			
};



#endif //__GRID_H__