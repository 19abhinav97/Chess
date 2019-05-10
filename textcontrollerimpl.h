#ifndef _TEXTCONTROLLER_H_
#define _TEXTCONTROLLER_H_
#include "humancontrollerimpl.h"

class TextControllerImpl : public HumanControllerImpl {
public:
  TextControllerImpl();
  void doPlayNextMove(Board *board);
  ~TextControllerImpl();
}

#endif

