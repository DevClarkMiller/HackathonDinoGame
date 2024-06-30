#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <thread>

using namespace std;

typedef vector<vector<bool>> twoDVec;

class FullScreen{
    public:
        unsigned int const WIDTH = 80;
        unsigned int const HEIGHT = 16;
        
        //2D bool vector typedef
        
        map<string, twoDVec> objsMap;

        bool screenMap[16][80];
    public:
        FullScreen(){
            zeroOut();
        }   

        void zeroOut(){
            for(unsigned int h = 0; h < HEIGHT; h++){
                for(unsigned int w = 0; w < WIDTH; w++){
                    screenMap[h][w] = 0;
                }
            }
        }

        void print(){
            for(unsigned int h = 0; h < HEIGHT; h++){
                for(unsigned int w = 0; w < WIDTH; w++){
                    const char output = (screenMap[h][w]) ? '#' : ' ';
                    cout << output;
                }
                //Spacing
                cout << endl;
            }
        }
        
        void addToMap(unsigned int x, unsigned int y, const bool customChar[8][5]){
            //Calc region to draw to
            if(x >= 0 && x < 80 && y >= 0 && y <= 16){
                unsigned int charx = 0, chary = 0;
                for(unsigned int h = y; h < 8; h++){
                    charx = 0;
                    for(unsigned int w = x; w < 5; w++){
                        screenMap[h][w] = customChar[chary][charx];
                        charx++;
                    }
                    chary++;
                }
            }
        }

        void printChar(const bool customChar[8][5] ){
            //Outer loop to iterate rows
            for(size_t i = 0; i < 8; i++){
                //Inner loop to print columns
                for(size_t j = 0; j < 5; j++){
                    const char output = (customChar[i][j]) ? '#' : ' ';
                    cout << output;
                }
                cout << endl;
            }
        }
};

void printChar(const twoDVec& customChar){
    //Outer loop to iterate rows
    for(size_t i = 0; i < 8; i++){
        //Inner loop to print columns
        for(size_t j = 0; j < 5; j++){
            const char output = (customChar[i][j]) ? '#' : 'O';
            cout << output;
        }
        cout << endl;
    }
}

//Combines each 8 x 5 region into a full bitmapped screen
void zeroOutMap(map<pair<int, int>, twoDVec> &screenMap){
    const twoDVec blankChar = {
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0},
        {0,0,0,0,0}
    };


    pair<int, int> it;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 16; j++){
            it = {i,j};
            screenMap[it] = blankChar;
        }
    }
}

void printMap(map<pair<int, int>, twoDVec> &screenMap){
    pair<int, int> it;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 16; j++){
            it = {i,j};
            printChar(screenMap[it]);
            //screenMap[it] = blankChar;
            std::thread t([](){
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            system("clear");  
            });
            t.join();  // Wait for the thread to finish
        }
    }
}

int main(){
    // bool aChar[8][5] = {
    //     {1,1,1,1,1},
    //     {1,0,0,0,1},
    //     {1,0,0,0,1},
    //     {1,1,1,1,1},
    //     {1,0,0,0,1},
    //     {1,0,0,0,1},
    //     {1,0,0,0,1},
    //     {1,0,0,0,1}
    // };

    //printChar(aChar);
    // FullScreen screen;
    // screen.addToMap(0, 0, aChar);
   
    // const twoDVec dino = {
    //     {1,1},
    //     {1,1},
    // };

    // screen.objsMap["dino"] = dino;

    //screen.print();

    map<pair<int, int>, twoDVec> screenMap;
    zeroOutMap(screenMap);
    
    twoDVec cus = {
        {1,1,1,1,1},
        {1,0,0,0,1},
        {1,1,1,1,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
        {1,0,0,0,1},
    };
    screenMap[pair<int,int> {0, 0}] = cus;

    printMap(screenMap);
}