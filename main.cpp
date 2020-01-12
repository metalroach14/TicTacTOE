#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct Board{
    char board[9];
    char winnerIs;
    void fillBoard();
    void drawBoard();
    int checkwin();
};

void Board::fillBoard(){
    for (int i = 0; i < 9; i++){
        board[i] = ' ';
    }
}
void Board::drawBoard()
{
    system("cls");
    cout << "Player 1 (X)  -  Player 2 (O)" << endl;
    cout << endl;
    cout << "    0   1   2" << endl;
    cout << "  +---+---+---+" << endl;
    cout << "0 | " << board[0] << " | " << board[1] << " | " << board[2] << " |" << endl;
    cout << "  +---+---+---+" << endl;
    cout << "1 | " << board[3] << " | " << board[4] << " | " << board[5] << " |" << endl;
    cout << "  +---+---+---+" << endl;
    cout << "2 | " << board[6] << " | " << board[7] << " | " << board[8] << " |" << endl;
    cout << "  +---+---+---+" << endl;
}
int Board::checkwin()
{
    for(int i=0;i<9;i+=3) {
        if((board[i]==board[i+1])&&(board[i+1]==board[i+2])&&board[i]!=' '){
            winnerIs = board[i];
            return 1;
        }
    }
    for(int i=0;i<3;i++) {
        if((board[i]==board[i+3])&&(board[i+3]==board[i+6])&&board[i]!=' '){
            winnerIs = board[i];
            return 1;
        }
    }
    if((board[0]==board[4])&&(board[4]==board[8])&&board[0]!=' ') {
        winnerIs = board[0];
        return 1;
    }
    if((board[2]==board[4])&&(board[4]==board[6])&&board[2]!=' ') {
        winnerIs = board[2];
        return 1;
    }
    for(int i=0;i<9;i++){
        if(board[i] == ' ')
            return -1;
    }
    return 0;
}

class Game {
    Board b;
    void menu();
    void singleplayer();
    void multiplayer();
    int minimax(bool flag);
    int getNumFromCoords(int x, int y);
    int index1;
public:
    Game();
    void start();
};
Game::Game(){
    b.fillBoard();
}
void Game::start(){
    menu();
}
void Game::menu(){
    int choise, second;
    do{
        cout<<"***=====================TIC-TAC-TOE=====================***\n";
        cout<<"==========================================================\n\n";
        cout<<"           PLEASE SELECT AN OPTION FROM THE MENU           \n\n";
        cout<<"     1. singleplayer \n";
        cout<<"     2. multiplayer \n";
        cout<<"     3. exit\n";
        cin>>choise;
        if (choise == 1) { singleplayer(); break; }
        if (choise == 2) { multiplayer(); break; }
        b.fillBoard();
        if(choise == 1 || choise == 2 ){
            cout<<"\n--- Thank you for playing this game! ---\n\n Do you want another? \n\n";
            cout<<"   1. Yes \n";
            cout<<"   2. No \n";
            do{
                cin>>second;
                if(second==1){

                    switch(choise){
                        case 1: singleplayer();break;
                        case 2: multiplayer();break;
                        default: cout<<"error occured";
                    }
                }

            }while(second !=2);
            system("cls");
        }

    }while(choise != 3);
    cout<<"\n--->   Thank you for chooseing our game!   <---\n";
    cout<<"---  See you soon! ---\n";
}
void Game::singleplayer(){
    int x,y,whoIsFirst;
    ofstream outF("TicTacToe.txt", ios::ate);
    if (!outF.is_open())
        throw("Error while opening the file");
    cout << "\n Player 1 (X)  -  Player 2 (O) \n";

    cout<<"---> Who should play first? \n";
    cout<<"  1. Player 1 \n";
    cout<<"  2. Player 2 (CPU)\n";
    do{
        cin>>whoIsFirst;
        if(whoIsFirst == 1) {
            b.drawBoard();
            cout << "Player, enter Position:  ";
            do {
                cin>>x>>y;
                int pos = getNumFromCoords(x,y);
                if(b.board[pos-1]==' ') {
                    b.board[pos-1] = 'X';
                    outF<<"Player 1 entered: [" << x << "] [" << y << "]\n";
                    if (!outF.good())
                        throw("Error occurred while writing the file");
                    b.drawBoard();
                    break;
                } else {
                    cout<<"Invalid move :( \n Please try another\n";
                }
            }while(b.board[getNumFromCoords(x,y)-1]!=' ');
        }
    }while(whoIsFirst != 1 && whoIsFirst != 2);
    while(true) {
        minimax(true);
        b.board[index1] = 'O';
        if(index1==0) outF<<"Player 2 entered: [" << 0 << "] [" << 0 << "]\n";
        else 	      outF<<"Player 2 entered: [" << index1/3 << "] [" << index1%3 << "]\n";
        if (!outF.good())
            throw("Error occurred while writing the file");
        b.drawBoard();
        if(b.checkwin()==1) {
            cout<<"Player2 has won\n";
            outF<<"Player2 has won\n";
            if (!outF.good())
                throw("Error occurred while writing the file");
            return;
        }
        if(b.checkwin()==0) {
            cout<<"Game is draw\n";
            outF<<"Game is draw\n";
            if (!outF.good())
                throw("Error occurred while writing the file");
            return;
        }
        do{
            cout<<endl<<"Enter the move:";
            cin>>x>>y;
            int pos = getNumFromCoords(x,y);
            if(b.board[pos-1]==' ') {
                b.board[pos-1] = 'X';
                outF<<"Player 1 entered: [" << x << "] [" << y << "]\n";
                if (!outF.good())
                    throw("Error occurred while writing the file");
                b.drawBoard();
                break;
            } else {
                cout<<endl<<"Invalid Move......Try different move";
            }
        }while(b.board[getNumFromCoords(x,y)-1]!=' ');
        if(b.checkwin()==1) {
            cout<<"Player 1 has won \n";
            outF<<"Player1 has won\n";
            if (!outF.good())
                throw("Error occurred while writing the file");
            return;
        }
        if(b.checkwin() == 0) {
            cout<<"Game is draw \n";
            outF<<"Game is draw\n";
            if (!outF.good())
                throw("Error occurred while writing the file");
            return;
        }
    }
    outF.close();
}
void Game::multiplayer(){
    int player = 1, i, x, y;
    ofstream outF("TicTacToe.txt", ios::ate);
    if (!outF.is_open())
        throw("Error while opening the file");
    char mark;
    do
    {
        b.drawBoard();
        player = (player % 2) ? 1 : 2;

        cout << "Player " << player << ", enter Position:  ";

        string text;
        do {
            cin >> x >> y;
            cout << "Are you sure? ";
            cin >> text;
            if (text == "no") {
                cout << "Then enter another X and Y:";
            }
        } while (text == "yes");
        mark = (player == 1) ? 'X' : 'O';

        outF << "Player " << player << " entered: [" << x << "] [" << y << "]" << endl;
        if (!outF.good())
            throw("Error occurred while writing the file");
        int pos = getNumFromCoords(x,y);
        if(b.board[pos-1] == ' ' && pos != 99)
            b.board[pos-1] = mark;
        else {
            cout << "Invalid move :(";
            player--;
            cin.ignore();
            cin.get();
        }
        i = b.checkwin();
        player++;
    } while (i == -1);
    b.drawBoard();
    if (i == 1) {
        int winner = --player;
        outF << "Player " <<  winner << " has won ";
        if (!outF.good())
            throw("Error occurred while writing the file");
        cout << " Player " << winner << " has won ";

    }
    else {
        outF << "Game is draw";
        if (!outF.good())
            throw("Error occurred while writing the file");
        cout << "Game is draw";

    }
    outF.close();
//	cin.ignore();
//	cin.get();
}
int Game::minimax(bool flag) {
    int max_val=-1000,min_val=1000;
    int i,j,value = 1;
    if(b.checkwin() == 1 && b.winnerIs == 'O')
        return 10;
    else if(b.checkwin() == 1 && b.winnerIs == 'X')
        return -10;
    else if(b.checkwin()== 0)
        return 0;
    int score[9] = {1,1,1,1,1,1,1,1,1};
    for(i=0;i<9;i++) {
        if(b.board[i] == ' ') {
            if(min_val>max_val) {
                if(flag == true) {
                    b.board[i] = 'O';
                    value = minimax(false);
                }
                else {
                    b.board[i] = 'X';
                    value = minimax(true);
                }
                b.board[i] = ' ';
                score[i] = value;
            }
        }
    }
    if(flag == true) {
        max_val = -1000;
        for(j=0;j<9;j++) {
            if(score[j] > max_val && score[j] != 1) {
                max_val = score[j];
                index1 = j;
            }
        }
        return max_val;
    }
    if(flag == false) {
        min_val = 1000;
        for(j=0;j<9;j++) {
            if(score[j] < min_val && score[j] != 1) {
                min_val = score[j];
                index1 = j;
            }
        }
        return min_val;
    }
}
int Game::getNumFromCoords(int x, int y){
    if(x<0 || x>2 || y<0 ||y>2) return 99;
    if(x==0){
        switch(y){
            case 0: return 1; break;
            case 1: return 2; break;
            case 2: return 3; break;
        }
    }
    if(x==1){
        switch(y){
            case 0: return 4; break;
            case 1: return 5; break;
            case 2: return 6; break;
        }
    }
    if(x==2){
        switch(y){
            case 0: return 7; break;
            case 1: return 8; break;
            case 2: return 9; break;
        }
    }
}

int main(){

    Game b;
    b.start();
    while (true);
    return 0;
}

