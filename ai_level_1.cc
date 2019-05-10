#include  "ai_level_1.h"
#include <algorithm>
#include "board_impl.h"
#include <iostream>
using namespace std;


// Get position of the king and check if it is in a  check state

AILevel1Impl::AILevel1Impl(Colour colour) : colour{colour} {}

bool AILevel1Impl::inCheck(Board* board, vector<PieceInfo> p){
  for(unsigned int i = 0; i < p.size(); i++){
    if(p[i].getType() == PieceType::King){
      return board->isUnderAttack(p[i].getPosition());
    }
  }
  return false;
}


void AILevel1Impl::doPlayNextMove(Board* board){
  vector<PieceInfo> p = board->getPiecesInfo();
  vector<PieceInfo> pieces;
  for(unsigned int i = 0 ; i < p.size(); i++){
    if(p[i].getColour() == colour){
      pieces.emplace_back(p[i]);
    }
  }
  /*
  if(inCheck(board, pieces)){
    while(inCheck(board, pieces)){ // While board is in check
      for(unsigned int i = 0; i < pieces.size(); i++){ // Go through all piece
        Position p = pieces[i].getPosition();
        vector<Position> moves = board->getPossibleMoves(p); // Get moves
        for(unsigned int m = 0 ; m < moves.size(); m++){ // Go through moves
          Board b = board->duplicateBoard();
          b.movePiece(p, moves[i]); // Move piece in the duplicate board
          if(!inCheck(&b, pieces)){ // If the board is not in check anymore
            board->movePiece(p, moves[i]); // MOve the actual piece
            return;
          }
        }
      }
    }
  }
  */

  auto rng = default_random_engine {};
  shuffle(pieces.begin(), pieces.end() , rng);
  for(unsigned int r = 0 ; r < pieces.size(); r++){
    Position pos = pieces[r].getPosition();
    PieceType pt = pieces[r].getType();
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
}

// I am assuming that the top of the board is always black
bool AILevel1Impl::isNextMovePossiblePawn(Position& pos, Board* board){
  vector<Position> possible_moves = board->getPossibleMoves(pos);
  for(unsigned int i = 0 ; i < possible_moves.size() ; i++)
    if(board->isPromotionMove(pos, possible_moves[i])){
      board->moveAndPromote(pos, possible_moves[i], PieceType::Queen);
      return true;
    }
    else if(board->isLegalMove(pos, possible_moves[i])){
      board->movePiece(pos, possible_moves[i]);
      return true;
    }
  return false;
}

bool AILevel1Impl::isNextMovePossibleBishop(Position& pos, Board* board){
  vector<Position> moves = board->getPossibleMoves(pos);
  for(unsigned int i = 0 ; i < moves.size() ; i++){
    if(board->isLegalMove(pos, moves[i])){
      board->movePiece(pos, moves[i]);
      return true;
    }
  }
  return false;
}

bool AILevel1Impl::isNextMovePossibleRook(Position& pos, Board* board){
  vector<Position> moves = board->getPossibleMoves(pos);
  for(unsigned int i = 0 ; i < moves.size() ; i++){
    if(board->isLegalMove(pos, moves[i])){
      board->movePiece(pos, moves[i]);
      return true;
    }
  }
  return false;
}

bool AILevel1Impl::isNextMovePossibleKnight(Position& pos, Board* board){
  vector<Position> moves = board->getPossibleMoves(pos);
  for(unsigned int i = 0 ; i < moves.size(); i++){
    if(board->isLegalMove(pos, moves[i])){
      board->movePiece(pos, moves[i]);
      return true;
    }
  }
  return false;
}

bool AILevel1Impl::isNextMovePossibleQueen(Position& pos, Board* board){
  if(isNextMovePossibleRook(pos, board))
    return true;
  if(isNextMovePossibleBishop(pos, board))
    return true;
  return false;
}

bool AILevel1Impl::isNextMovePossibleKing(Position& pos, Board* board){
  vector<Position> moves = board->getPossibleMoves(pos);
  for(unsigned int i = 0 ; i < moves.size(); i++){
    if(board->isLegalMove(pos, moves[i])){
      board->movePiece(pos, moves[i]);
      return true;
    }
  }
  return false;
}

AILevel1Impl::~AILevel1Impl(){
}
