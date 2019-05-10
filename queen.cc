#include "queen.h"
#include "piece_type.h"


Queen::Queen( Position position, Colour colour, Direction direction ) :

    Piece( position, colour, direction ) {}


PieceType Queen::getType() const {

    return PieceType::Queen;

}


bool Queen::doCanMove( const Position &to ) const {

    // Queen is allowed to move in any direction and any distance
    return true; 

}


std::unique_ptr<Piece> Queen::doDuplicatePiece() const {

    return std::make_unique<Queen>( *this );

}
