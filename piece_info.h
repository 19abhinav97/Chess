#ifndef PIECE_INFO_H
#define PIECE_INFO_H

#include "colour.h"
#include "direction.h"
#include "piece_type.h"
#include "position.h"

class Position;
class StatusType;

class PieceInfo {

    PieceType type;
    Colour colour;
    Direction direction;
    // the forward direction for the player controlling the piece
    Position position;
    bool moved;

  public:

    PieceInfo( PieceType type, Colour colour, Direction direction, 
               Position position, bool moved = false );
    PieceType getType() const;
    Colour getColour() const;
    Direction getDirection() const;
    Position getPosition() const;
    StatusType getStatus() const;
    bool hasMoved() const;

};

#endif
