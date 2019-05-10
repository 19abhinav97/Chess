#include "piece.h"
#include "position.h"
#include "move_state.h"
#include "piece_info.h"


Piece::Piece( Position position, Colour colour, 
        Direction direction, bool moved ) :

    Subject( MoveState( position, MoveType::NewPiece ) ), 
    colour{ colour }, position{ position }, direction{ direction },
    moved{ moved } {

        notifyObservers();
    
}


bool Piece::isWithinStepSize( 
        const Position &to, int stepSize ) const {

    return to.getABSRowDiff( position ) <= stepSize &&
           to.getABSColDiff( position ) <= stepSize;

}


bool Piece::doCanCapture( const Position &target ) const {
   
    return doCanMove( target );

}


bool Piece::doCanJump() const {

    return false;

}


int Piece::getRow() const {

    return position.getRow();

}


int Piece::getCol() const {

    return position.getCol();

}


Colour Piece::getColour() const {

    return colour;

}


Position Piece::getPosition() const {

    return position;

}


Direction Piece::getDirection() const {

    return direction;

}


PieceInfo Piece::getInfo() const {

    return PieceInfo{ getType(), colour, 
                      direction, position, moved };

}


bool isEmptyCell( const PieceInfo &info ) {

    return info.getType() == PieceType::EmptyCell;

}


bool isInvalidCell( const PieceInfo &info ) {

    return info.getType() == PieceType::InvalidCell;

}


bool Piece::canMove( const PieceInfo &to ) const {

    return getPosition() != to.getPosition() && 
           isEmptyCell( to ) && doCanMove( to.getPosition() );

}

/*
bool isOpponentPiece( const PieceInfo &info ) {

    return !isEmptyCell( info ) &&
           info.getType() != PieceType::InvalidCell &&
           info.getColour() != colour;

}
*/

bool Piece::canCapture( const PieceInfo &target ) const {

    return getPosition() != target.getPosition() &&
//           isOpponentPiece( target ) &&          
           !isInvalidCell( target ) &&
           doCanCapture( target.getPosition() );

}


std::vector<Position> Piece::doGetPath( const Position &to ) const {

    return getPosition().getInBetween( to );

}


std::vector<Position> Piece::getPath( const Position &to ) const {

    return doGetPath ( to );

    /*
    if ( canMove( to ) || canCapture( to ) ) {
        return doGetPath ( to );
    } else {
        throw InvalidMoveException{ position, to,
            "No legal path exists." };
    }
    */

}


bool Piece::canJump() const {

    return doCanJump();

}


bool Piece::hasMoved() const {

    return moved;

}


void Piece::updatePosition( Position newPosition ) {

    position = newPosition;
    moved = true;
    notifyObservers();

}


void Piece::move( Position to ) {

    setState( MoveState{ position, to, MoveType::Move } );
    updatePosition( to );

    /*
    if ( canMove( to ) ) {
        setState( MoveState{ position, to, MoveType::Move } );
        updatePosition( to );
    } else {
        throw InvalidMoveException{ position, to, 
            "The piece does not support such move." };
    }
    */

}


void Piece::capture( Position target ) {

    setState( MoveState{ position, target, MoveType::Capture } );
    updatePosition( target );

    /*
    if ( canCapture( target ) ) {
        setState( MoveState{ position, target, MoveType::Capture } );
        updatePosition( target );
    } else {
        throw InvalidMoveException{ position, to,
            "The piece does not support such capture." };
    }
    */

}


void Piece::beCaptured() {

    setState( MoveState{ position, MoveType::IsCaptured } );
    notifyObservers();

}


std::unique_ptr<Piece> Piece::duplicatePiece () const {

    return doDuplicatePiece();

}
