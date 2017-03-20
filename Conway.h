#pragma once
#include <vector>

class Conway {
private:
    // Legg til de medlemsvariablene og hjelpefunksjonene du trenger
    std::vector<std::vector<bool>> canvas;
    bool started;
public:
    Conway(int width, int height);
    ~Conway();

    bool isTileAlive(row, col) const;
    bool hasSimulationStarted() const;

    void toggleAlive(row, col);
    void startSimulation();

    // Vi slår av autogenerert kopikonstruktør og tilordningsoperator for å unngå feil
    Conway(const Conway &) = delete;
    Conway &operator=(const Conway &) = delete;
};
