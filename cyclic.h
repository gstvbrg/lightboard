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
		Cyclic(Canvas *m, const int t, array< array<int,3>, 4> s, const int w, const int h);
		~Cyclic();
		void initGrid();
		void Run();
		int numActiveNeighbors(int x, int y);
		void updateState();
		void drawStateTo(Canvas *m);
		void archiveState();
	public:
		Canvas *_m;
		vector< vector<Cell> > grid;
		array< array<int, 3>, 4> _states;
		const int _threshold;
		const int _numStates;
		int _delay_ms;
		const int _width;
  		const int _height;
};