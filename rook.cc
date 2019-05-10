#include "rook.h"
#include "piece_type.h"
#include "position.h"


Rook::Rook( Position position, Colour colour, Direction direction ) :

    Piece( position, colour, direction ) {}


PieceType Rook::getType() const {

    return PieceType::Rook;

}


bool Rook::doCanMove( const Position &to ) const {

    Position position = getPosition();

    // Rook is allowed to move along vertical/horizontal directions
    return ( to.getRowDiff( position ) ) == 0 ||
           ( to.getColDiff( position ) ) == 0;

}


std::unique_ptr<Piece> Rook::doDuplicatePiece() const {

    return std::make_unique<Rook>( *this );

}
