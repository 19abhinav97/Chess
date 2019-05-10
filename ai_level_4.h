#ifndef AILevel4Impl_H
#define AILevel4Impl_H
#include "ai_controller_impl.h"
#include "position.h"
#include "board.h"
#include "piece_info.h"

class AILevel4Impl : public AIControllerImpl{
  int get_worth(PieceType pt);
  Colour colour;
public:
  void doPlayNextMove(Board* board);
  AILevel4Impl(Colour colour);
};

#endif
