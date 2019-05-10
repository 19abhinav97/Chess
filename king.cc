#include "king.h"
#include "piece_type.h"
#include "position.h"


const int KING_REGULAR_STEP_SIZE = 1;


King::King( Position position, Colour colour, Direction direction ) :

    Piece( position, colour, direction ) {}


PieceType King::getType() const {

    return PieceType::King;

}


bool King::doCanMove( const Position &to ) const {

    // King is allowed to move one square in any direction
    // or upwhen castling, is allowed to move two squares
    return isWithinStepSize( to,  KING_REGULAR_STEP_SIZE );

}


std::unique_ptr<Piece> King::doDuplicatePiece() const {

    return std::make_unique<King>( *this );

}
