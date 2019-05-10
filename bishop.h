#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"
#include "colour.h"

class Position;

class Bishop : public Piece {

    PieceType getType() const;
    bool doCanMove( const Position &to ) const override;
    std::unique_ptr<Piece> doDuplicatePiece() const;

  public:

    Bishop( Position position, Colour colour, Direction direction);

};

#endif
