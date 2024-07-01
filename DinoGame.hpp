#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <random>
#include <string>

typedef std::vector<std::vector<int>> twoDVec;

struct Coords{
    int y;
    int x;
};

enum Points{
    BLANK = 0,
    PLAYER = 1,
    OBSTACLE = 2
};

class DinoGame{
    private:
        twoDVec game;
        std::random_device rd;  // Obtain a random seed from hardware
        std::mt19937 gen; // Standard mersenne_twister_engine seeded with rd()

        bool gameLoop();
    public:
        DinoGame();

        bool isObstacle(Coords coord);

        Coords spawnObstacle();

        void start();

        void shiftScreen();

        void draw(const Coords& coord, Points objType);

        void printGame();
};