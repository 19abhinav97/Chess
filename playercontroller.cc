#include "playercontroller.cc"
using namespace std;

void PlayerController::playNextMove() {
  PlayerControllerImpl->playNextMove(); //playercontrollerimpl is a pointer (Will change later)
}

