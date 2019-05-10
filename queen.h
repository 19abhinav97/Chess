#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"
#include "colour.h"

class Position;

class Queen : public Piece {

    PieceType getType() const;
    bool doCanMove( const Position &to ) const override;
    std::unique_ptr<Piece> doDuplicatePiece() const;

  public:

    Queen( Position position, Colour colour, Direction direction );

};

#endif
