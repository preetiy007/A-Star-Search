#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

enum class State {kStart,kFinish,kEmpty,kObstacle,kPath,kClosed};

//Valid directions
const int delta[4][2]{{-1,0},{0,1},{1,0},{0,1}};



///////////////////  READING /////////////////

//Parsing just one line
vector<State> ParseLine(string line){
    istringstream sline(line);
    int n;
    int c;
    vector<State> row;
    while(sline >> n >> c && c== ','){

        if(n=0){ 
            row.push_back(State::kEmpty);}

            else{
                row.push_back(State::kObstacle);

            }
    }
    return row;

} 


vector<vector<State>> ReadBoardFile(string path){

    ifstream myfile(path);
    vector<vector<State>> board{};
    if(myfile){
        string line;
        while(getline(myfile, line)){
            vector<State> row=ParseLine(line);
            board.push_back(row);

        }
    }

    return board;


}


/////////////   ASTAR SEARCH PART   //////////////////

 //Calculating heuristic

 int Heuristic (int x1, int y1, int x2, int y2){
  return abs(x2-x1) + abs(y2-y1);
 }

 //Adding nodes in the open list

 void AddToOpen(int x, int y, int g, int h, vector<vector<int>> &open_list, vector<vector<State>> &grid){
    
     open_list.push_back(vector<int>{x,y,g,h});
     grid[x][y]=State::kClosed;

 }


 ///Comparing the f value

 bool Compare(vector<int> a , vector<int> b){
     int f1=a[2] + a[3];
     int f2=b[2] + b[3];
return f1>f2;
 }


 //Sorting the cell

 void CellSort(vector<vector<int>> *v){

     sort(v->begin(),v->end(),Compare);

 }


 //checking valid neighbours

 bool CheckValidCell(int x, int y, vector<vector<State>> &grid){

     bool on_grid_x=(x>=0 && x<grid.size());
     bool on_grid_y=(y>=0 && y<grid[0].size());
     if(on_grid_x && on_grid_y && (grid[x][y] == State::kEmpty )){
         return true;
     }
     return false;
 }




 ///Expanding neighbours

void ExpandNeighbours(const vector<int> &current,int goal[2],vector<vector<int>> &openlist,vector<vector<State>> &grid){


int x=current[0];
int y=current[1];
int g=current[2];

for(int i=0;i<4;i++){
    int x2=x+delta[i][0];
    int y2=y+delta[i][0];

    if(CheckValidCell(x2,y2,grid)){
        int g2=g+1;
        int h2=Heuristic(x2,y2,goal[0],goal[1]);
        AddToOpen(x2,y2,g2,h2,openlist,grid);

    }
}
}







vector<vector<State>>  Search(vector<vector<State>> grid, int init[2], int goal[2]){

    int x=init[0];
    int y=init[1];

    int g=0;
    int h=Heuristic(x,y,goal[0],goal[1]);

    vector<vector<int>> open{};

    AddToOpen(x,y,g,h,open,grid);

    while(open.size()>0){

        CellSort(&open);
        auto current=open.back();
        open.pop_back();
        x=current[0];
        y=current[1];
        grid[x][y]==State::kPath;
    

    if(x==goal[0] && y==goal[1]){

        grid[init[0]][init[1]]=State::kStart;
        grid[goal[0]][goal[1]] = State::kFinish;
        return grid;
    }
      ExpandNeighbours(current,goal,open,grid);
    }

    cout << "No path found!" << "\n";
  return std::vector<vector<State>>{};

}



















//////////////// PRINTING ///////////////////


string CellString(State cell){
    switch(cell){

        case State::kObstacle : return "⛰️   ";
        case State::kPath : return "🚗   ";
        default : return "0   "; 

    }
}


void PrintBoard(const vector<vector<State>> board){

    for(int i=0; i< board.size();i++){
            for (int j=0;j< board[i].size();j++){
                cout << CellString(board[i][j]);

            }

            cout<<"\n";



    }


}



int main(){
    int init[2]{0,0};
    int goal[2]{4,5};
   auto board=ReadBoardFile("/home/preeti/College/udacity/C++ Practise/ASearch/1.board");
   auto solution = Search(board, init, goal);
   PrintBoard(solution);
   






}
