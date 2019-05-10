#include "empty_cell.h"
#include "piece_type.h"


EmptyCell::EmptyCell( Position position, Colour colour, Direction direction ) :

    Piece( position, colour, direction ) {}


PieceType EmptyCell::getType() const {

    return PieceType::EmptyCell;

}


bool EmptyCell::doCanMove( const Position &to ) const {

    // EmptyCell is not allowed to move
    return false; 

}


std::unique_ptr<Piece> EmptyCell::doDuplicatePiece() const {

    return std::make_unique<EmptyCell>( *this );

}
