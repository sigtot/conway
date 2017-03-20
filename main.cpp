#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <iomanip>

#include "Conway.h"

using namespace std;

const sf::Color open_fill_color(60,60,60), closed_fill_color(210,210,210);

const int tile_size = 10;
int border_size = 0;
int frequency = 2;

int main(int argc, char *argv[]) {
    srand(time(nullptr));

    int height = 50, width = 50;


    // Command line parameters
    for(int i = 1; i < argc; i++){
        if((strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--frequency") == 0) && i + 1 < argc){
            //frequency = strtol(argv[i+1]);
            frequency = strtol(argv[i+1],&argv[i+1], 10);
            i++;
            continue;
        }

        if(strcmp(argv[i], "-g") == 0 || strcmp(argv[i], "--grid") == 0){
            border_size = 1;
            continue;
        }

        if((strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--dimensions") == 0) && i + 2 < argc){
            height = strtol(argv[i+1],&argv[i+1], 10);
            width = strtol(argv[i+2],&argv[i+2], 10);
            i += 2;
            continue;
        }

        if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0){
            cout << "Conway's game of life\n\n";
            cout << "Usage: ./conway [-d height width] [-f frequency]\n";
            cout << "Options:\n";
            cout << "-g, --grid" << setw(10) << " " << "Display with background grid\n";
            cout << "-h, --help" << setw(10) << " " << "Show this help\n";
            return 0;
        }
    }

    Conway* game = new Conway(width, height);

    sf::RenderWindow window(sf::VideoMode(width * tile_size, height * tile_size), "Conway's Game of Life", sf::Style::Close);

    cout << "Place living cells with your cursor. Spacebar starts the simulation. Q/Esc to quit" << endl;

    window.setFramerateLimit(60);

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch(event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch(event.key.code) {
                case sf::Keyboard::Escape:
                case sf::Keyboard::Q:
                    window.close();
                    break;
                case sf::Keyboard::Space:
                    // Start simulation
                    game->startSimulation();
                    break;
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left && !game->hasSimulationStarted()) {
                    int row = event.mouseButton.y / tile_size;
                    int col = event.mouseButton.x / tile_size;

                    game->toggleAlive(row, col);
                }
                break;
            }
        }

        window.clear();

        for(int row = 0; row < height; ++row) {
            for(int col = 0; col < width; ++col) {
                const int tile_x = col * tile_size, tile_y = row * tile_size;

                sf::RectangleShape tile;
                tile.setSize(sf::Vector2f(tile_size - border_size, tile_size - border_size));
                tile.setFillColor(game->isTileAlive(row, col) ? open_fill_color : closed_fill_color);
                tile.setPosition(tile_x + border_size / 2.0, tile_y + border_size / 2.0);

                sf::Time elapsedTime = clock.getElapsedTime();
                if(game->hasSimulationStarted() && elapsedTime.asSeconds() > 1/static_cast<double>(frequency)){
                    game->nextGeneration();
                    clock.restart();
                }

                window.draw(tile);

            }
        }

        window.display();
    }

    delete game;

    return 0;
}
