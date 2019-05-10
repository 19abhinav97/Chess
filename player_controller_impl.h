#ifndef PlayerControllerImpl_H
#define PlayerControllerImpl_H

#include "board.h"


class PlayerControllerImpl{
    Board board;
      void doPlayNextMove();
  public:
        void playNextMove();
          Board getBoard();
};
#endif
