#ifndef KING_H
#define KING_H

#include "piece.h"
#include "colour.h"

class Position;

class King : public Piece {

    PieceType getType() const;
    bool doCanMove( const Position &to ) const override;
    std::unique_ptr<Piece> doDuplicatePiece() const;

  public:

    King( Position position, Colour colour, Direction direction );

};

#endif
