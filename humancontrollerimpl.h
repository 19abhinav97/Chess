#ifndef _HUMANCONIMPL_H_
#define _HUMANCONIMPL_H_
#include "playercontollerimpl.h"

class HumanControllerImpl : public PlayerControllerImpl {
public:
  void doPlayNextMove(Board *board) override = 0;
}

#endif

