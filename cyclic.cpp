#include "cyclic.h"

#include <iostream>
#include <random>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>

using namespace rgb_matrix;

//grid(vector<vector<Cell>> (h, vector<Cell>(w, Cell())))

Cyclic::Cyclic(RGBMatrix *m, const int r, const int t, array< array<int,3>, 3> s, int w, int h)
	: ThreadedCanvasManipulator(m), _delay_ms(750), _range(r), _threshold(t), _states(s),
	_width(w), _height(h) {	

	// Initalize Grid
	_numStates = _states.size();
	_canvas = m;
    _offscreen = m->CreateFrameCanvas();
	Cyclic::initGrid();
}

Cyclic::~Cyclic() {
	for(int row = 0; row < _height; row++){
		for(int col = 0; col < _width; col++){
			delete &grid[row][col];
		}
	}
}

void Cyclic::initGrid() {
	uniform_int_distribution<int> states_dist(0,_numStates-1);
  	default_random_engine randNum;
	for (int row = 0; row < _height; row++) {
		for (int col = 0; col < _width; col++) {
			grid[row][col].setState(states_dist(randNum));
		}
	}
}

void Cyclic::Run(){
	Cyclic::drawState();
	Cyclic::_canvas->SwapOnVSync(_offscreen);
	Cyclic::archiveState();
	Cyclic::updateState();
	usleep(Cyclic::_delay_ms * 5);
}

int Cyclic::numActiveNeighbors(int x, int y) {
	
	int count = 0;
	int cell = ((grid[x][y].getPreviousState() + 1) % _numStates);

	int h = _height;
	int w = _width;
	
	// Torus
	// N
	//cout << "N\n" << ((((x%h)-1) % h + h) % h) << "," << y << endl;
	if (cell == (grid[((((x%h)-1) % h + h) % h)][y].getPreviousState())){count++;}
	// NE
	// cout << "NE\n" << ((((x%h)-1) % h + h) % h) << "," << ((y+1) % w) << endl;
	if (cell == (grid[((((x%h)-1) % h + h) % h)][((y+1) % w)].getPreviousState())){count++;}
	// E
	// cout << "E\n" << x << "," << ((y+1)%w) << endl;
	if (cell == (grid[x][((y+1)%w)].getPreviousState())){count++;}
	// SE
	// cout << "SE\n" << ((((x%h)+1)%h)) << "," << ((y+1) % w) << endl;
	if (cell == (grid[((((x%h)+1)%h))][((y+1) % w)].getPreviousState())){count++;}
	// S
	// cout << "S\n" << (((x%h)+1)%h) << "," << y << endl;
	if (cell == (grid[(((x%h)+1)%h)][y].getPreviousState())){count++;}
	// SW
	// cout << "SW\n" << ((((x%h)+1)%h)) << "," << ((((x%w)-1) % w + w) % w) << endl;
	if (cell == (grid[((((x%h)+1)%h))][((((y%w)-1) % w + w) % w)].getPreviousState())){count++;}
	// W
	// cout << "W\n" << x << "," << ((((x%w)-1) % w + w) % w) << endl;
	if (cell == (grid[x][((((y%w)-1) % w + w) % w)].getPreviousState())){count++;}
	// NW
	// cout << "NW\n" << ((((x%h)-1) % h + h) % h) << "," << ((((x%w)-1) % w + w) % w) << endl;
	if (cell == (grid[((((x%h)-1) % h + h) % h)][((((y%w)-1) % w + w) % w)].getPreviousState())){count++;}
	// cout<<"sorted out"<<endl;
	return count;
}

int Cyclic::numActiveNeighbors(int x, int y, int range) {

	int h = _height;
	int w = _width;
	
	int cell = (((grid[x][y].getPreviousState()) + 1) % _numStates);
	int count = 0;

	//cout << "Cell State    : " << ((grid[x][y].getPreviousState() + 1) % _numStates) << endl;
	//cout << "Cell State + 1: " << cell << endl;
	for (int r = 1; r < range + 1; r++) { 
		// Torus
		// N
		// cout << r << "N of " << x << "," << y << "\n" << ((((x%h)-r) % h + h) % h) << "," << y << endl;
		if (cell == (grid[((((x%h)-r) % h + h) % h)][y].getPreviousState())){count++;}
		// NE
		// cout << r << "NE of " << x << "," << y << "\n" << ((((x%h)-r) % h + h) % h) << "," << ((y+r) % w) << endl;
		if (cell == (grid[((((x%h)-r) % h + h) % h)][((y+r) % w)].getPreviousState())){count++;}
		// E
		// cout << r << "E of " << x << "," << y << "\n" << x << "," << ((y+r)%w) << endl;
		if (cell == (grid[x][((y+r)%w)].getPreviousState())){count++;}
		// SE
		// cout << r << "SE of " << x << "," << y << "\n" << ((((x%h)+r)%h)) << "," << ((y+r) % w) << endl;
		if (cell == (grid[((((x%h)+r)%h))][((y+r) % w)].getPreviousState())){count++;}
		// S
		// cout << r << "S of " << x << "," << y << "\n" << (((x%h)+r)%h) << "," << y << endl;
		if (cell == (grid[(((x%h)+r)%h)][y].getPreviousState())){count++;}
		// SW
		// cout << r << "SW of " << x << "," << y << "\n" << ((((x%h)+r)%h)) << "," << ((((x%w)-r) % w + w) % w) << endl;
		if (cell == (grid[((((x%h)+r)%h))][((((y%w)-r) % w + w) % w)].getPreviousState())){count++;}
		// W
		// cout << r << "W of " << x << "," << y << "\n" << x << "," << ((((x%w)-r) % w + w) % w) << endl;
		if (cell == (grid[x][((((y%w)-r) % w + w) % w)].getPreviousState())){count++;}
		// NW
		//cout << r << "NW of " << x << "," << y << "\n" << ((((x%h)-r) % h + h) % h) << "," << ((((x%w)-r) % w + w) % w) << endl;
		if (cell == (grid[((((x%h)-r) % h + h) % h)][((((y%w)-r) % w + w) % w)].getPreviousState())){count++;}
	}
	//cout << "count " << count << endl;
	return count;
}

void Cyclic::updateState() {
	int numActive;
	for (int row = 0; row < _height; row++) {
		for (int col = 0; col < _width; col++) {


			// Active Numbers of Previous State
			numActive = Cyclic::numActiveNeighbors(row,col,_range);
			//cout << "numActive: " << numActive << endl;

			if ( numActive >= _threshold) {
				// If neighborhood occurence of next state(color) of cell is 
				// greater or equal to threshold, advance cell state by 1
				grid[row][col].setState((grid[row][col].getState() + 1) % _numStates);

			} else {
				// If neightborhood occurence of next state is not greater than threshold
				// pass cell state through to next grid
				grid[row][col].setState(grid[row][col].getPreviousState());

			}
		}
	}
}

void Cyclic::archiveState(){
	for(int row = 0; row < _height; row++){
		for(int col = 0; col < _width; col++){
			grid[row][col].setPreviousState(grid[row][col].getState());
		}
	}
}

void Cyclic::drawState() {
	for(int row = 0; row < _height; row++){
		for(int col = 0; col < _width; col++){
			int s = grid[row][col].getState();
			_offscreen->SetPixel(col,row, _states[s][0], _states[s][1], _states[s][2]);
		}
	}
}
