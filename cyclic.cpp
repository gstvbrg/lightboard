#include "cyclic.h"

#include <iostream>
#include <random>

using namespace rgb_matrix;

Cyclic::Cyclic(Canvas *m, vector<int> b, vector<int> d, vector< array<int,3> > s)
		: ThreadedCanvasManipulator(m), _delay_ms(500), births(b), deaths(d), states(s)
	{	
		// Get Canvas Dimensions
		_width = canvas()->width();
		_height = canvas()->height();

		// Define Grid Shape
		grid = vector<vector<Cell>> (_height, vector<Cell>(_width, Cell()));

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
			//cout << "grid[" << i << "][" << j << "]: prevState" << grid[i][j].getPreviousState() << " CurrState " << grid[i][j].getState() << endl;
		}
	}
}

void Cyclic::Run(){
	return;
}

int Cyclic::numLivingNeighbors(int x, int y) {
	int num=0;
      // Edges are connected (torus)
	num += grid[(x-1+_width)%_width][(y-1+_height)%_height].getState();
	num += grid[(x-1+_width)%_width][y                    ].getState();
	num += grid[(x-1+_width)%_width][(y+1        )%_height].getState();
	num += grid[(x+1       )%_width][(y-1+_height)%_height].getState();
	num += grid[(x+1       )%_width][y                    ].getState();
	num += grid[(x+1       )%_width][(y+1        )%_height].getState();
	num += grid[x                  ][(y-1+_height)%_height].getState();
	num += grid[x                  ][(y+1        )%_height].getState();
	return num;
}

void Cyclic::update() {
	// for (int i = 0; i < _height; i++) {
	// 	for (int j = 0; j < _width; j++) {
	// 		cout << "Set at start: " << grid[i][j].getState();
	// 		int numLiving = Cyclic::numLivingNeighbors(i,j);
	// 		if ( any_of(births.begin(), births.end(), [&numLiving](int i){ return i == numLiving;} ) ){
	// 			grid[i][j].setState( (grid[i][j].getState() + 1) % states.size());
	// 		} else if ( any_of(deaths.begin(), deaths.end(), [&numLiving](int i){ return i == numLiving;} )
	// 	}
	// }
	return;
}