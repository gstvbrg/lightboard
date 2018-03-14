#include "cell.h"
#include "./matrix/include/led-matrix.h"
#include "./matrix/include/threaded-canvas-manipulator.h"

#include <vector>
#include <array>
#include <iostream>
using namespace rgb_matrix;
using namespace std;

class Cyclic : public ThreadedCanvasManipulator  {
	public:
		Cyclic(Canvas *m, vector<int> b, vector<int> d, vector< array<int,3> > s);
		~Cyclic();
		void initGrid();
		void Run();
		int numLivingNeighbors(int x, int y);
		void update();
	public:
		vector< vector<Cell> > grid;
		vector< array<int, 3> > states;
		vector<int> births;
		vector<int> deaths;
		int _delay_ms;
		int _width;
  		int _height;
};