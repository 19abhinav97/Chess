#include "invalid_cell.h"
#include "piece_type.h"


InvalidCell::InvalidCell( Position position, Colour colour, 
        Direction direction ) :

    Piece( position, colour, direction ) {}


PieceType InvalidCell::getType() const {

    return PieceType::InvalidCell;

}


bool InvalidCell::doCanMove( const Position &to ) const {

    // InvalidCell does not change position
    return false; 

}


std::unique_ptr<Piece> InvalidCell::doDuplicatePiece() const {

    return std::make_unique<InvalidCell>( *this );

}
