#include "board.h"
#include "ai_level_1.h"

int main(int argc, char *argv[]) {
  Board board;
  board.init(8, 8, 2);
  AILevel1Impl* ai_lev1_1 = new AILevel1Impl();
  AILevel1Impl* ai_lev1_2 = new AILevel1Impl();
  while(!board.isCheckmate()){
    ai_lev1_1->doPlayNextMove(&board);
    ai_lev1_2->doPlayNextMove(&board);
  }
}
