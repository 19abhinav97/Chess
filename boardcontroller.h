#ifndef BOARD_CONTROLLER_IMPL_
#define BOARD_CONTROLLER_IMPL_
#include "boardcontrollerimpl.h"

class BoardController {
  BoardControllerImpl *boardControllerImpl; //Make unique pointer
public:
  void play();
}

#endif

