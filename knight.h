#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "colour.h"

class Position;

class Knight : public Piece {

    PieceType getType() const;
    bool doCanMove( const Position &to ) const override;
    bool doCanJump() const override;
    std::vector<Position> doGetPath(
            const Position &to ) const override;
    std::unique_ptr<Piece> doDuplicatePiece() const;

  public:

    Knight( Position position, Colour colour, Direction direction );

};

#endif
