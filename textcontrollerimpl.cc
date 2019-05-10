#include "textcontrollerimpl.h"
using namespace std;

TextControllerImpl::TextControllerImpl() {}

TextControllerImpl::doPlayNextMove(Board *board) {
  string command;
  Position start;
  Position end;
  PieceType piece;
  Bool pawn_prom = true;
  cin >> command >> start >> end;
  if (!(cin >> piece)) {
    pawn_prom = false;
    cin.clear();
    cin.ignore();
  }
  if (board->isLegalMove(start, end)) {
    if (pawn_prom) {
      baord->moveAndPromote(start, end, piece);
      //cout << board;
    } else {
      board->movePiece(start, end);
      //cout << board;
    }
  } else {
    cout << "Error! Please try again." << endl;
  }
}

TextControllerImpl::~TextControllerImpl() {}
