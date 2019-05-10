#include "ai_level_2.h"
#include "ai_level_3.h"
#include "piece_info.h"
#include "piece.h"
#include <algorithm>
#include "board_impl.h"
using namespace std;


AILevel3Impl::AILevel3Impl(Colour c) : colour{c} {}


void AILevel3Impl::doPlayNextMove(Board* board){
  vector<PieceInfo> pieces  = board->getPiecesInfo();
  // Go through every piece
  for(unsigned int i = 0 ; i < pieces.size();i++){
    // Get the position and type
    PieceType pt = pieces[i].getType();
    Position pos = pieces[i].getPosition();
    // if it's a valid cell
    if(!(pt == PieceType::InvalidCell || pt == PieceType::EmptyCell)){
      if(board->isUnderAttack(pos)){ // Check if it's a under attack
        // Now get the list of all the attackers
        vector<Position> possible_moves = board->getPossibleMoves(pos);
        for(unsigned int i = 0 ; i < possible_moves.size(); i++){
          if(board->isLegalMove(pos, possible_moves[i]) && !(board->isUnderAttack(possible_moves[i], colour))){
            board->movePiece(pos, possible_moves[i]);
            return;
          }
        }
      }
    }
  }
  auto l2 = make_unique<AILevel2Impl>();
  l2->doPlayNextMove(board);
}
// All pieces are unsafe or should play other type of moves
  // Call AI Level 2 now
  //
AILevel3Impl::~AILevel3Impl(){
}
