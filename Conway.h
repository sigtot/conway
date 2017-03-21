#pragma once
#include <vector>

class Conway {
private:
    std::vector<std::vector<bool>> canvas;
    bool started;
public:
    Conway(int width, int height);

    bool isTileAlive(int row, int col) const;
    bool hasSimulationStarted() const;

    void toggleAlive(int row, int col);
    void startSimulation();

    int getNumAdjacentCells(int row, int col) const;

    void nextGeneration();
};
