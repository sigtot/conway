#include <stdexcept>
#include <iostream>
#include "Conway.h"

Conway::Conway(int width, int height) {
	std::vector<std::vector<bool>>  matrix(width, std::vector<bool>(height));
	this->canvas = matrix;

	this->started = false;
}

Conway::~Conway() {
// No dynamic variables
}

bool Conway::isTileAlive(int row, int col) const{
	try{
		return this->canvas.at(col).at(row);
	}
	catch(std::out_of_range& e){
		return false;
	}
}

void Conway::toggleAlive(int row, int col){
	try{
		this->canvas.at(col).at(row) = !this->canvas.at(col).at(row);
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

int Conway::getNumAdjacentCells(int row, int col) const{
	int count = 0;
	for(int x = -1; x <= 1; x++){
		for(int y = -1; y <= 1; y++){
			if(x == 0 && y == 0) continue;
			if(this->isTileAlive(row + y, col + x)) count++;
		}
	}
	return count;
}

void Conway::nextGeneration(){
	std::vector<std::vector<bool>> nextCanvas(this->canvas.size(), std::vector<bool>(this->canvas[0].size()));
	for(int y = 0; y < this->canvas[0].size(); y++){
		for(int x = 0; x < this->canvas.size(); x++){
			// Alive and less than 2 or more than 3 neighbors -> kill cell
			if(this->isTileAlive(y,x)){ 
				if(this->getNumAdjacentCells(y,x) < 2 || this->getNumAdjacentCells(y,x) > 3)
					nextCanvas[x][y] = false;
				else{
					nextCanvas[x][y] = true;;
				}
			}
			else
			// Dead and 3 neighbors -> bring cell to life
			if(!this->isTileAlive(y,x) && this->getNumAdjacentCells(y,x) == 3)
				nextCanvas[x][y] = true;
		}
	}
	this->canvas = nextCanvas;
}