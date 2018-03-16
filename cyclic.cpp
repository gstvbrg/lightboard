#include "cyclic.h"

#include <iostream>
#include <random>

using namespace rgb_matrix;

Cyclic::Cyclic(Canvas *m, const int t, vector< array<int,3> > s, int w, int h)
		: ThreadedCanvasManipulator(m), _delay_ms(500), _threshold(t), states(s),
		_width(w), _height(h), grid(vector<vector<Cell>> (h, vector<Cell>(w, Cell())))
	{	
		// Initalize Grid
		Cyclic::initGrid();
	}

Cyclic::~Cyclic(){}

void Cyclic::initGrid() {
	uniform_int_distribution<int> states_dist(0,states.size()-1);
  	default_random_engine randNum;
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			grid[i][j].setInitState(states_dist(randNum));
		}
	}
}

void Cyclic::Run(){
	return;
}

int Cyclic::numActiveNeighbors(int x, int y) {
	int count = 0;
	int currState = grid[x][y].getPreviousState();

	int h = _height;
	int w = _width;

	// Torus //
	// N
	if (currState == 1 + grid[((((x%h)-1) % h + h) % h)][y].getPreviousState()){count++;}
	// NE
	if (currState == 1 + grid[((((x%h)-1) % h + h) % h)][((y+1) % w)].getPreviousState()){count++;}
	// E
	if (currState == 1 + grid[x][((y+1)%w)].getPreviousState()){count++;}
	// SE
	if (currState == 1 + grid[((((x%h)+1)%h))][((y+1) % w)].getPreviousState()){count++;}
	// S
	if (currState == 1 + grid[(((x%h)+1)%h)][y].getPreviousState()){count++;}
	// SW
	if (currState == 1 + grid[((((x%h)+1)%h))][((y-1) % w)].getPreviousState()){count++;}
	// W
	if (currState == 1 + grid[x][((y-1) % w)].getPreviousState()){count++;}
	// NW
	if (currState == 1 + grid[((((x%h)-1) % h + h) % h)][((y-1) % w)].getPreviousState()){count++;}

	return count;
}

void Cyclic::update() {
	for (int i = 0; i < _height; i++) {
		for (int j = 0; j < _width; j++) {
			int numActive = Cyclic::numActiveNeighbors(i,j);
			if ( numActive >= _threshold) {
				grid[i][j].setState( (grid[i][j].getPreviousState() + 1) % states.size());
			} else {
				grid[i][j].setState( grid[i][j].getState());
			}
		}
	}
}