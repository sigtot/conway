#include "Conway.h"

Conway::Conway(int width, int height) {
	vector<vector<bool>>  matrix(height, vector<bool>(width));
	this->canvas = matrix;

	this->started = false;
}

Conway::~Conway() {
// No dynamic variables
}

bool Conway::isTileAlive(row,col) const{
	try{
		return this->canvas.at(col).at(row);
	}
	catch(std::out_of_range& e){
		return false;
	}
}

void toggleAlive(row,col){
	try{
		this->canvas.at(col).at(row);
	}
	catch(std::out_of_range& e){
		return;
	}
}

bool Conway::hasSimulationStarted() const{
	return this->started;
}

void Conway::startSimulation(){
	this->started = true;
}