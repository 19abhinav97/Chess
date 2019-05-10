#include "pawn.h"
#include "direction.h"
#include "piece_type.h"
#include "position.h"


const int PAWN_STEP_SIZE_REGULAR_MOVE = 1;
const int PAWN_STEP_SIZE_FIRST_MOVE = 2;
const int PAWN_STEP_SIZE_CAPTURE = 1;


Pawn::Pawn( Position position, Colour colour, Direction direction ) :

    Piece( position, colour, direction ) {}


PieceType Pawn::getType() const {

    return PieceType::Pawn;

}


bool Pawn::doCanMove( const Position &to ) const {

    Position position = getPosition();
    Direction direction = getDirection();

    // Pawn is allowed to move one square foward
    // If on its first move, Pawn is also allowed to
    //    move two squares foward

    return to.isNSquaresForwardTo( position, direction, 
                                   PAWN_STEP_SIZE_REGULAR_MOVE) ||
         ( !hasMoved() &&
           to.isNSquaresForwardTo( position, direction,
                                   PAWN_STEP_SIZE_FIRST_MOVE ) );

}


bool Pawn::doCanCapture( const Position &target ) const {

    // Pawn is allowed to capture on one square diagonally foward
    return target.isNSquaresDiagForwardTo( 
            getPosition(), getDirection(), PAWN_STEP_SIZE_CAPTURE );

}


std::unique_ptr<Piece> Pawn::doDuplicatePiece() const {

    return std::make_unique<Pawn>( *this );

}
