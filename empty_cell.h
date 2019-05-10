#ifndef EMPTY_CELL_H
#define EMPTY_CELL_H

#include "piece.h"
#include "colour.h"

class Position;

class EmptyCell : public Piece {

    PieceType getType() const;
    bool doCanMove( const Position &to ) const override;
    std::unique_ptr<Piece> doDuplicatePiece() const;

  public:

    EmptyCell( Position position, Colour colour, 
               Direction direction = Direction::NW );

};

#endif
