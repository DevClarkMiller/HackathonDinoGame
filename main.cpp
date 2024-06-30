#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <random>

using namespace std;

typedef vector<vector<int>> twoDVec;
typedef pair<int, int> coord;

bool isObstacle(twoDVec& game, coord coords){
    return game[coords.first][coords.second] == 2;
}

void printGame(twoDVec& game){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 32; j++){
            const char cChar = (game[i][j] == 1 || game[i][j] == 2) ? '#' : 'O';
            cout << cChar;
        }
        cout << endl;
    }
}

void draw(twoDVec& game, const coord& coords, int objType){
    game[coords.first][coords.second] = objType;
}

pair<int, int> spawnObstacle(twoDVec& game, std::mt19937& gen){
    int ran = 0;

    std::uniform_int_distribution<> dis(16, 31);
    do{
        ran = dis(gen);
        coord coords{1, ran};
        const bool coordOccupied = isObstacle(game, coords); 

        //Check if point where you're spawning obstacle already has something in it

        if(coordOccupied){
            continue;
        }
        if(isObstacle(game, coord(1, ran - 1)) || isObstacle(game, coord(1, ran + 1))){
            continue;
        }

        return coords;
    }while(true);
}

void shiftScreen(twoDVec& game){
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 32; j++){
            if(game[i][j] && j - 1 >= 0){
                game[i][j] = 0;
                game[i][j - 1] = 1;
            }
        }
    }
}

int main(){
    std::random_device rd;  // Obtain a random seed from hardware
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

    pair<int, int> playerCoords(1, 0);

    twoDVec game = {
        // 2 x 32 game screen. Half is used strictly for spawning in the obstacles off-screen
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };

    draw(game, playerCoords, 1);

    while(true){
        // char input;
        // cin >> std::noskipws >> input;

        // cin.clear();
        //cin.ignore(numeric_limits<streamsize>::max(), '\n');

        //addCoords(game, playerCoords, 0);

        //playerCoords = {0, 0};
        //addCoords(game, playerCoords, 1);
        //printGame(game);
        //addCoords(game, playerCoords, 0);

        std::thread t([](){
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
            system("clear");  
        });
        t.join();  // Wait for the thread to finish

        //playerCoords = {1, 0};
        //addCoords(game, playerCoords, 1);
        draw(game, spawnObstacle(game, gen), 1);

        printGame(game);
        shiftScreen(game);
    }
}