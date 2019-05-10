#ifndef AILevel1Impl_H
#define AILevel1Impl_H
#include "ai_controller_impl.h"
#include "piece_info.h"
#include "board.h"
#include "position.h"

class AILevel1Impl : public AIControllerImpl{
  bool isNextMovePossiblePawn(Position&, Board*);
  bool isNextMovePossibleKing(Position&, Board*);
  bool isNextMovePossibleQueen(Position&, Board*);
  bool isNextMovePossibleBishop(Position&, Board*);
  bool isNextMovePossibleRook(Position&, Board*);
  bool isNextMovePossibleKnight(Position&, Board*);
  bool inCheck(Board*, std::vector<PieceInfo>);
  Colour colour;
public:
  AILevel1Impl(Colour colour);
  void doPlayNextMove(Board* board);
  ~AILevel1Impl();
};
#endif
