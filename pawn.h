#ifndef PAWN_H
#define PAWN_H

#include "piece.h"
#include "colour.h"

class Position;

class Pawn : public Piece {

    PieceType getType() const;
    bool doCanMove( const Position &to ) const override;
    bool doCanCapture( const Position &target ) const override;
    std::unique_ptr<Piece> doDuplicatePiece() const;

  public:

    Pawn( Position position, Colour colour, Direction direction );

};

#endif
