#ifndef AIControllerImpl_H
#define AIControllerImpl_H

#include "player_controller_impl.h"

class AIControllerImpl : public PlayerControllerImpl {
  virtual void doPlayNextMove(Board* board) = 0;
};

#endif
