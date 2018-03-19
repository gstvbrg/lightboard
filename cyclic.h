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
		Cyclic(RGBMatrix *m, const int r, const int t, array< array<int,3>, 3> s, const int w, const int h);
		~Cyclic();
		void initGrid();
		void Run();
		int numActiveNeighbors(int x, int y);
		int numActiveNeighbors(int x, int y, int range);
		void updateState();
		void drawState();
		void archiveState();
	public:
		RGBMatrix *_canvas;
		FrameCanvas *_offscreen;
		//clevector< vector<Cell> > grid;
		array< array<Cell, 128 >, 96 > grid;
		array< array<int, 3>, 3> _states;
		const int _range;
		const int _threshold;
		int _numStates;
		int _delay_ms;
		const int _width;
  		const int _height;
};