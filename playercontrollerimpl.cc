#include "playercontrollerimpl.h"
using namespace std;

PlayerControllerImpl::PlayerControllerImpl(Board *board): board{board} {}

void PlayerControllerImpl::playNextMove() {
  doPlayNextMove(board);
}

