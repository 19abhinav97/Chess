#include "bishop.h"
#include "piece_type.h"
#include "position.h"


Bishop::Bishop( Position position, Colour colour, Direction direction ) :

    Piece( position, colour, direction ) {}


PieceType Bishop::getType() const {

    return PieceType::Bishop;

}


bool Bishop::doCanMove( const Position &to ) const {

    Position position = getPosition();

    // Bishop is allowed to move along diagonal directions
    return to.getABSRowDiff( position )  ==
           to.getABSColDiff( position ) ;

}


std::unique_ptr<Piece> Bishop::doDuplicatePiece() const {

    return std::make_unique<Bishop>( *this );

}
