#ifndef _BOARDCONTROLLERIMPL_H_
#define _BOARDCONTROLLERIMPL_H_
#include "board.h"
#include <vector>
//#include ""

class BoardControllerImpl  {
  Board *board;
  vector<PlayerController> players;
public:
  BoardControllerImpl(Board *board);
  void play();
  ~BoardControllerImpl();
};

#endif

