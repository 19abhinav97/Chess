#include "board.h"
#include "ai_level_1.h"
#include "ai_level_2.h"
#include "board_impl.h"
#include <iostream>
#include "piece_type.h"
#include "colour.h"
#include <string>
#include "invalid_move_exception.h"

using namespace std;

int main(int argc, char *argv[]) {
  Board board;
  board.initStandardBoard();
  cout << board;
  int mode;
  cout << "For AI vs AI enter 1\n";
  cout << "For player vs player enter 2\n";
  cin >> mode;
  string next;
  if(mode == 1){
      AILevel1Impl* ai_lev1_1 = new AILevel1Impl(Colour::Black);
      AILevel1Impl* ai_lev1_2 = new AILevel1Impl(Colour::White);
      while(!board.isCheckmate()){
        try{
        ai_lev1_1->doPlayNextMove(&board);
        } catch(InvalidMoveException &e){
          cout << "First player Error\n";
          cout << e.getErrorMessage() << endl;
        }
        cout << board;
        cin >> next;
        try{
        ai_lev1_2->doPlayNextMove(&board);
        } catch (InvalidMoveException &e){
            cout << "Second player error\n";
          cout << e.getErrorMessage() << endl;
        }
        cout << board;
        cin >> next;
      }
  }
  if(mode == 2){
      bool white_turn = true;
      while(!board.isCheckmate()){
          char c1;
          int c2;
          char c3;
          int c4;
          string move;
          if(white_turn){
                  cout << "White moves now\n";
              }
              else{
                  cout << "Black moves now\n";
              }
              cin >> move;
          if(move == "move"){
              cout << "Enter positions\n";
            }
            cin >> c1 >> c2 >> c3 >> c4;
            int col = int(c1 - 'a');
            int row =  c2;
            Position p1 = Position{row, col};
            col = c3 - 'a';
            row = c4;
            Position p2 = Position{row, col};
            try{
            board.movePiece(p1, p2);
            } catch(InvalidMoveException &e){
                cout << "Invalid move\n";
                continue;
            }
            cout << board;
            if(white_turn)
                white_turn = false;
            else
                white_turn = true;
          }
      }
  }
