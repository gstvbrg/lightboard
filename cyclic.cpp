#include "cyclic.h"

#include <iostream>
#include <random>
#include <signal.h>

using namespace rgb_matrix;

Cyclic::Cyclic(Canvas *m, const int t, array< array<int,3>, 4> s, int w, int h)
		: ThreadedCanvasManipulator(m), _delay_ms(500), _threshold(t), _states(s), _numStates(3), 
		_width(w), _height(h), grid(vector<vector<Cell>> (h, vector<Cell>(w, Cell())))
	{	
		// Initalize Grid
		Cyclic::initGrid();
		
	}

Cyclic::~Cyclic(){}

void Cyclic::initGrid() {
	uniform_int_distribution<int> states_dist(0,2);
  	default_random_engine randNum;
	for (int row = 0; row < _height; row++) {
		for (int col = 0; col < _width; col++) {
			grid[row][col].setState(states_dist(randNum));
		}
	}
}

void Cyclic::Run(){
	cout << "run!" << endl;
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
	//cout << "count : " << count << "\n";

	return count;
}

void Cyclic::updateState() {
	int numActive;
	for (int row = 0; row < _height; row++) {
		for (int col = 0; col < _width; col++) {


			// Active Numbers of Previous State
			numActive = Cyclic::numActiveNeighbors(row,col);

			if ( numActive >= _threshold) {
				// If neighborhood occurence of next state(color) of cell is 
				// great or equal to threshold, advance cell state by 1
				grid[row][col].setState( (grid[row][col].getState() + 1) % _numStates);

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


void Cyclic::drawStateTo(Canvas *m) {
	for(int row = 0; row < _height; row++){
		for(int col = 0; col < _width; col++){
			int s = grid[row][col].getState();
			m->SetPixel(col,row, _states[s][0], _states[s][1], _states[s][2]);
		}
	}
}
