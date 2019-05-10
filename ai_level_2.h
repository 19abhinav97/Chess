#ifndef AILevel2Impl_H
#define AILevel2Impl_H
#include "ai_controller_impl.h"
#include "piece_info.h"
#include "board.h"
#include "position.h"

class AILevel2Impl : public AIControllerImpl{
  bool isNextMovePossiblePawn(Position&, Board*);
  bool isNextMovePossibleKing(Position&, Board*);
  bool isNextMovePossibleQueen(Position&, Board*);
  bool isNextMovePossibleBishop(Position&, Board*);
  bool isNextMovePossibleRook(Position&, Board*);
  bool isNextMovePossibleKnight(Position&, Board*);
  Colour colour;
public:
  AILevel2Impl(Colour colour);
  void doPlayNextMove(Board* board);
  ~AILevel2Impl();

};
#endif
