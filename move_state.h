#ifndef MOVE_STATE_H
#define MOVE_STATE_H

#include "position.h"
#include "move_type.h"

class MoveState {

    Position from;
    Position to;
    MoveType type;

  public:

    MoveState( Position position, MoveType type );
    MoveState( Position from, Position to, MoveType type );
    Position whereFrom() const;
    Position whereTo() const;
    MoveType whatType() const;

};

#endif
