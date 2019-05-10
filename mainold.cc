//#include "boardcontrollerimpl.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  
  Board b;
  int rows;
  int columns;
  int n_players;
  cout << "Enter the number of Rows in the board" << endl;
  cin >> rows;
  cout << "Enter thr number of Columns in the board" << endl;
  cin >> columns;
  cout << "Enter the number of Players" << endl;
  cin >> n_players;
  b.init(rows, columns, n_players);
  cout << b;
  int whitewin = 0;
  int blackwin = 0;
  int whitemove = 0;
  int blackmove = 0;
  Colour c_piece = Colour::White;

  string input_string;
  cin >> input_string;

  if (!strcmp(input_string, "Setup")) {
    string s;
    while (cin >> s) {
      if (s == '+') {
        Position first;
        PieceType second;
        Colour colour;
        cin >> first;
        cin >> second;
        cin >> colour;
        b.setPiece(first, second, colour);
        colour = colour::Black;
        cout << b;
      }
      if (s == '-') {
        Position first;
        Colour colour;
        cin >> first;
        b.removePiece(first);
        cout << b;
      } 
      if (!strcmp(s, "Done")) {
        cout << b;
        break;
      }
      if (s == '=') {
        Colour colour;
        cin >> colour;
        c_piece = colour;
      }
    }
  }
  if (!strcmp(input_string, "move")) {
    //Check if the computer is playing. if yes, then just move will move the player
    Position initial_pos;
    Position final_pos;
    string s1;
    cin >> initial_pos;
    cin >> final_pos;
    
  }
}
