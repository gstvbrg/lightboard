#include <vector>
#include <iostream>
#include <random>

using namespace std;

class Cell {
	public:
		Cell(): x(0), y(0), state(0) {}
		Cell(int x_p, int y_p): x(y_p), y(y_p), state(0) {}
		Cell(int x_p, int y_p, int state_p): x(x_p), y(y_p), state(state_p) {} 
		void setX(int x_p) { x = x_p;}
		int getX() {return x;}
		void setY(int y_p) { y = y_p;}
		int getY() {return y;}
		void setState(int nextState) { 
			state = nextState; 
		}
		int getState() {return state;}
		int setPreviousState(int s) {previousStates.push_back(s);}
		int getPreviousState() {return previousStates.back();}
	public:
		int x;
		int y;
		int state;
		std::vector<int> previousStates;
};