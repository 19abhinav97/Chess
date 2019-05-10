#include "move_state.h"


MoveState::MoveState( 
        Position from, Position to, MoveType type ) :

    from{ from }, to{ to }, type {type } {}


MoveState::MoveState( Position position, MoveType type ) :

    from{ position }, to{ position }, type{ type } {}



