#ifndef AILevel3Impl_H
#define AILevel3Impl_H
#include "ai_controller_impl.h"
#include "piece_info.h"
#include "board.h"
#include "position.h"

class AILevel3Impl : public AIControllerImpl{
  Colour colour;
public:
  void doPlayNextMove(Board* board);
  AILevel3Impl(Colour colour);
  ~AILevel3Impl();
};
#endif
