#include "ai_level_1.h"
#include "ai_level_2.h"
#include "piece_info.h"
#include <algorithm>
#include "board_impl.h"
using namespace std;

AILevel2Impl::AILevel2Impl(Colour colour) : colour{colour} {}

void AILevel2Impl::doPlayNextMove(Board* board){
  vector<PieceInfo> p = board->getPiecesInfo();
  vector<PieceInfo> pieces;
  for(unsigned int i = 0 ; i < p.size(); i++){
    if(p[i].getColour()  == colour){
      pieces.emplace_back(p[i]);
    }
  }
  auto rng = default_random_engine {};
  shuffle(pieces.begin(), pieces.end(), rng);
  for(unsigned int i = 0 ; i < pieces.size(); i++){
    Position pos = pieces[i].getPosition();
    PieceType pt = pieces[i].getType();
    if(pt == PieceType::Pawn){
      if(isNextMovePossiblePawn(pos, board))
        break;
    }
    else if(pt == PieceType::Knight){
      if(isNextMovePossibleKnight(pos, board))
        break;
    }
    else if(pt == PieceType::Rook){
      if(isNextMovePossibleRook(pos, board))
        break;
    }
    else if(pt == PieceType::Bishop){
      if(isNextMovePossibleBishop(pos, board))
        break;
    }
    else if(pt == PieceType::Queen){
      if(isNextMovePossibleQueen(pos, board))
        break;
    }
    else if(pt == PieceType::King){
      if(isNextMovePossibleKing(pos, board))
        break;
    }
    else{
      continue;
    }
  }
  // If no check or capturing move present, then we go to random moves
  // Call the AI Level 1 doPlayNext function
  auto level1 = make_unique<AILevel1Impl>(Colour::Black);
  level1->doPlayNextMove(board);
}


// I am assuming that the top of the board is always black
bool AILevel2Impl::isNextMovePossiblePawn(Position& pos, Board* board){
  cout << "OK\n";
  vector<Position> possible_moves = board->getPossibleMoves(pos);
  for(unsigned int i = 0 ; i < possible_moves.size() ; i++){
    cout << i << endl;
    /*
    if(board->isPromotionMove(pos, possible_moves.at(i))){
      cout << "Moving promoitoina\n";
      board->moveAndPromote(pos, possible_moves[i], PieceType::Queen);
      return true;
    }
    */
    if(board->isCheckMove(pos , possible_moves[i])){
      board->movePiece(pos, possible_moves[i]);
      return true;
    }
    if(board->isCapturingMove(pos, possible_moves[i])){
      board->movePiece(pos, possible_moves[i]);
    }
  }
  return false;
}

bool AILevel2Impl::isNextMovePossibleBishop(Position& pos, Board* board){
  vector<Position> possible_moves = board->getPossibleMoves(pos);
  for(unsigned int i = 0 ; i < possible_moves.size(); i++){
    if(board->isCheckMove(pos, possible_moves[i]) || board->isCapturingMove(pos, possible_moves[i])){
      board->movePiece(pos, possible_moves[i]);
      return true;
    }
  }
  return false;
}

bool AILevel2Impl::isNextMovePossibleRook(Position& pos, Board* board){
  vector<Position> possible_moves = board->getPossibleMoves(pos);
  for(unsigned int i = 0 ; i < possible_moves.size() ; i++){
    if(board->isCheckMove(pos, possible_moves[i]) || board->isCapturingMove(pos, possible_moves[i])){
      board->movePiece(pos, possible_moves[i]);
      return true;
    }
  }
  return false;
}

bool AILevel2Impl::isNextMovePossibleKnight(Position& pos, Board* board){
  vector<Position> moves = board->getPossibleMoves(pos);
  for(unsigned int i = 0 ; i < moves.size(); i++){
    if(board->isCheckMove(pos, moves[i]) || board->isCapturingMove(pos, moves[i])){
      board->movePiece(pos, moves[i]);
      return true;
    }
  }
  return false;
}

bool AILevel2Impl::isNextMovePossibleQueen(Position& pos, Board* board){
  if(isNextMovePossibleRook(pos, board))
    return true;
  if(isNextMovePossibleBishop(pos, board))
    return true;
  return false;
}

// TODO WHAT TO DO WITH THE KING

bool AILevel2Impl::isNextMovePossibleKing(Position& pos, Board* board){
  vector<Position> moves = board->getPossibleMoves(pos);
  for(unsigned int i = 0 ; i < moves.size(); i++){
    if(board->isLegalMove(pos, moves[i])){
      board->movePiece(pos, moves[i]);
      return true;
    }
  }
  return false;
}

AILevel2Impl::~AILevel2Impl(){
}
