#include <vector>
#include <iostream>
#include <random>

using namespace std;

class Cell {
	public:
		Cell(): x(0), y(0), _state(0) {}
		Cell(int x_p, int y_p): x(y_p), y(y_p), _state(0) {}
		Cell(int x_p, int y_p, int state_p): x(x_p), y(y_p), _state(state_p) {} 
		void setX(int x_p) { x = x_p;}
		int getX() {return x;}
		void setY(int y_p) { y = y_p;}
		int getY() {return y;}
		void setState(int nextState) { 
			_state = nextState; 
		}
		int getState() {return _state;}
		int setPreviousState(int s) {_previousState = s;}
		int getPreviousState() {return _previousState;}
	public:
		int x;
		int y;
		int _state;
		int _previousState;
};