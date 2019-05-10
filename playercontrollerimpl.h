#ifndef _PCONTROLLERIMPL_H_
#define _PCONTROLLERIMPL_H_
#include "humancontrollerimpl.h"
#include "aicontollerimpl.h"

class PlayerControllerImpl {
  Board *board;
public:
  PlayerControllerImpl(Board *board);
  virtual void doPlayNextMove (Board *board) = 0;
  void PlayNextMove();
  virtual ~PlayerControllerImpl() = 0;
};

#endif

