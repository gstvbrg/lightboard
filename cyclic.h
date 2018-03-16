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
		Cyclic(Canvas *m, const int t, vector< array<int,3> > s, const int w, const int h);
		~Cyclic();
		void initGrid();
		void Run();
		int numActiveNeighbors(int x, int y);
		void update();
	public:
		vector< vector<Cell> > grid;
		vector< array<int, 3> > states;
		const int _threshold;
		int _delay_ms;
		const int _width;
  		const int _height;
};