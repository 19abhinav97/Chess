#ifndef ROOK_H
#define ROOK_H

#include "piece.h"
#include "colour.h"

class Position;

class Rook : public Piece {

    PieceType getType() const;
    bool doCanMove( const Position &to ) const override;
    std::unique_ptr<Piece> doDuplicatePiece() const;

  public:

    Rook( Position position, Colour colour, Direction direction );

};

#endif
