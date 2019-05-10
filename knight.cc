#include "knight.h"
#include "piece_type.h"
#include "position.h"
#include "invalid_move_exception.h"


const int KNIGHT_LARGE_STEP_SIZE = 2;
const int KNIGHT_SMALL_STEP_SIZE = 1;


Knight::Knight( Position position, Colour colour, Direction direction ) :

    Piece( position, colour, direction ) {}


PieceType Knight::getType() const {

    return PieceType::Knight;

}


bool Knight::doCanMove( const Position &to ) const {

    Position position = getPosition();
    int absRowDiff = to.getABSRowDiff( position );
    int absColDiff = to.getABSColDiff( position );

    // Knight is allowed to move to (x +/- 2, y +/- 1) 
    //    or (x +/- 1, y +/- 2) when sitting on (x, y)
    return ( absRowDiff == KNIGHT_LARGE_STEP_SIZE &&
             absColDiff == KNIGHT_SMALL_STEP_SIZE ) ||
           ( absRowDiff == KNIGHT_SMALL_STEP_SIZE &&
             absColDiff == KNIGHT_LARGE_STEP_SIZE );

}


bool Knight::doCanJump() const {

    // Knight will not be blocked by piece that is on its path
    return true;

}


std::vector<Position> Knight::doGetPath( const Position &to ) const {

    std::vector<Position> path;
    Position position = getPosition();

    int row = position.getRow();
    int col = position.getCol();

    int rowDiff = to.getRowDiff( position );
    int colDiff = to.getColDiff( position );

    if ( std::abs( rowDiff ) == KNIGHT_LARGE_STEP_SIZE ) {

        if ( rowDiff < 0 ) {
            path.emplace_back( Position{ row-1, col } );
        } else if ( rowDiff > 0 ) {
            path.emplace_back( Position{ row+1, col } );
        } else {
            throw InvalidMoveException{ position, to,
                "Knight cannot move to the same row." };
        }

    } else if ( std::abs( colDiff ) == KNIGHT_LARGE_STEP_SIZE ) {

        if ( colDiff < 0 ) {
            path.emplace_back( Position{ row, col-1 } );
        } else if ( colDiff > 0 ) {
            path.emplace_back( Position{ row, col+1 } );
        } else {
            throw InvalidMoveException{ position, to,
                "Knight cannot move to the same column." };
        }

    } else {

        throw InvalidMoveException{ position, to, 
            "Invalid Move for Knight" };

    }

    return path;

}


std::unique_ptr<Piece> Knight::doDuplicatePiece() const {

    return std::make_unique<Knight>( *this );

}
