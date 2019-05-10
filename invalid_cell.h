#ifndef INVALID_CELL_H
#define INVALID_CELL_H

#include "piece.h"
#include "colour.h"

class Position;

class InvalidCell : public Piece {

    PieceType getType() const;
    bool doCanMove( const Position &to ) const override;
    std::unique_ptr<Piece> doDuplicatePiece() const;

  public:

    InvalidCell( Position position, Colour colour, 
                 Direction direction = Direction::SE );

};

#endif
