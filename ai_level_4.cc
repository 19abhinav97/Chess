#include "ai_level_4.h"
#include "ai_level_3.h"
#include "points.h"
#include "board_impl.h"


using namespace std;


AILevel4Impl::AILevel4Impl(Colour colour) : colour{colour} {}

// King is not needed since it's value is essentially infinity
int AILevel4Impl::get_worth(PieceType pt){
  if(pt == PieceType::Queen)
    return 5;
  if(pt == PieceType::Bishop || pt == PieceType::Knight)
    return 4;
  if(pt == PieceType::Rook)
    return 3;
  // Else it will be a pawn anyways.
  return 1;
}


// TODO FOR PAWN PROMOTION
void AILevel4Impl::doPlayNextMove(Board* board){
  vector<PieceInfo> pieces = board->getPiecesInfo();
  vector<Score> best_moves;
  for(unsigned int i = 0 ; i < pieces.size(); i++){
    Position pos = pieces[i].getPosition();
    // Go through all the possible moves and store the best value
    //
    // CHeck if the pueces are under attack
    if(board->isUnderAttack(pos)){
      vector<Position> moves = board->getPossibleMoves(pos);
      for(unsigned int i = 0 ; i < moves.size(); i++){
        if(!board->isUnderAttack(moves[i], colour)){
          PieceType p = board->getPieceInfo(moves[i]).getType();
          best_moves.push_back(Score{pos.getRow(), pos.getCol(), moves[i].getRow(), moves[i].getCol(), get_worth(p)});
        }
      }
    }
    // Now check the normal attacks
    vector<Position> possible_moves = board->getPossibleMoves(pos);
    for(unsigned int i = 0 ; i < possible_moves.size(); i++){
      if(board->isCapturingMove(pos, possible_moves[i])){
        PieceType p = board->getPieceInfo(possible_moves[i]).getType();;
        best_moves.push_back(Score{pos.getRow(), pos.getCol(), possible_moves[i].getRow(), possible_moves[i].getCol(), get_worth(p)});
      }
    }
  }
  // Now get the best moves
  int i_x; // Initial
  int i_y; // XY coordinated
  int f_x; // Final
  int f_y;
  int max_score = 0;
  for(unsigned int i = 0 ; i < best_moves.size(); i++){
    if(abs(best_moves[i].get_score()) >= max_score){

      i_x = best_moves[i].get_initial()[0];
      i_y = best_moves[i].get_initial()[1];
      f_x = best_moves[i].get_final()[0];
      f_y = best_moves[i].get_final()[1];

      max_score = best_moves[i].get_score();
    }
  }
  if(best_moves.size() == 0){
    auto l3 = make_unique<AILevel3Impl>(colour);
    l3->doPlayNextMove(board);
    return;
  }


  // Now I've got the optimal moves, I'll mmake the move
  board->movePiece(Position{i_x, i_y}, Position{f_x, f_y});


}
