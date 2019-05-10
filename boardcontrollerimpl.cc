#include "boardcontrollerimpl.h"

BoardControllerImpl::BoardControllerImpl(Board *board): board{board} {}

BoardControllerImpl::play() {
  int num_players = players.size();
  for (int i = 0; i < num_players; ++i) {
    players[i].playNextMove(board);
  }
}

BoardControllerImpl::~BoardControllerImpl() {}

