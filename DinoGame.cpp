#include "DinoGame.hpp"

DinoGame::DinoGame() : 
    game({{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}) {
        gen.seed(rd());
    }

bool DinoGame::isObstacle(Coords coord) {
    return game[coord.y][coord.x] == Points::OBSTACLE;
}

Coords DinoGame::spawnObstacle(){
    int rand = 0;

    std::uniform_int_distribution<> dis(16, 31);
    for(int attempts = 0; attempts < 10; attempts++){
        rand = dis(gen);
        Coords coord = {1, rand};
        const bool coordOccupied = isObstacle(coord); 

        //Check if point where you're spawning obstacle already has something in it

        if(coordOccupied){
            continue;
        }

        if(isObstacle({1, rand - 1}) || isObstacle({1, rand + 1})){
            continue;
        }

        return coord;
    }
    return {-1, -1};
}

void DinoGame::shiftScreen(){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 32; j++){
            if(game[i][j] == Points::OBSTACLE && j - 1 > 0){
                game[i][j] = Points::BLANK;
                game[i][j - 1] = Points::OBSTACLE;
            }else if(j - 1 <= 0){
                game[i][j] = Points::BLANK;
            }
        }
    }
}

void DinoGame::draw(const Coords& coord, Points objType) {
    game[coord.y][coord.x] = objType;
}

void DinoGame::printGame(){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 16; j++){
            const auto& curr = game[i][j];
            char cChar;
            switch(curr){
                case Points::BLANK:
                    cChar = 'O';
                    break;
                case Points::PLAYER:
                    cChar = 'G';
                    break;
                case Points::OBSTACLE: 
                    cChar = '#';
                    break;
                default: 
                    cChar = 'O';
            }
            std::cout << cChar;
        }
        std::cout << std::endl;
    }
}

bool DinoGame::gameLoop(){
    printGame();    //Prints out each of the obstacles

    char input;
    std::cin >> std::noskipws >> input;
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    const Coords newEnemy = spawnObstacle();
    //Checks if it's a valid coordinate which would mean there was a valid location for an enemy to spawn in
    if(newEnemy.x >= 0) 
        draw(newEnemy, Points::OBSTACLE);   //Spawns in an obstacle at a random point

    shiftScreen();  //Moves the obstacles
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    system("clear");
    return true;
}

void DinoGame::start(){
    while(gameLoop());
    std::cout << "Game over!" << '\n';
}
