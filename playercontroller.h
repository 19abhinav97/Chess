#ifndef _PCONTROLLER_H_
#define _PCONTROLLER_H_
#include "playercontrollerimpl.h"
#include <utility>

class PlayerContoller {
  std::unique_ptr<PlayerControllerImpl> playercontrollerimpl (std::make<Player>);
public:
  void playNextMove();
};

#endif

