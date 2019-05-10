#include "position.h"
#include <map>
#include <iostream>

using namespace std;

const std::map<Direction, Direction> OPPOSITE_DIRECTIONS =
    { { Direction::N, Direction::S }, { Direction::S, Direction::N },
      { Direction::W, Direction::E }, { Direction::E, Direction::W },
      { Direction::NW, Direction::SE }, { Direction::SE, Direction::NW },
      { Direction::NE, Direction::SW }, { Direction::SW, Direction::NE } };
const std::map<Direction, std::vector<Direction>> FORWARD_DIAGONALS =
    { { Direction::N, { Direction::NW, Direction::NE } },
      { Direction::S, { Direction::SW, Direction::SE } },
      { Direction::W, { Direction::NW, Direction::SW } },
      { Direction::E, { Direction::NE, Direction::SE } } };


Position::Position( int row, int col ) :

    row{ row }, col{ col } {}


int Position::getRow() const {

    return row;

}


int Position::getCol() const {

    return col;

}


int Position::getRowDiff( const Position &other ) const {

    return row - other.row;

}


int Position::getColDiff( const Position &other ) const {

    return col - other.col;

}


int Position::getABSRowDiff( const Position &other ) const {

    return std::abs( getRowDiff( other ) );

}


int Position::getABSColDiff( const Position &other ) const {

    return std::abs( getColDiff( other ) );

}


Direction Position::getDirection( const Position &other ) const {

    int r = row;
    int c = col;
    int otherR = other.getRow();
    int otherC = other.getCol();

    if (otherR < r) {

        if (otherC < c) {
            return Direction::NW;
        } else if (otherC == c) {
            return Direction::N;
        } else { // otherC > c
            return Direction::NE;
        }


    } else if (otherR == r) {

        if (otherC < c) {
            return Direction::W;
        } else { // (otherC >= c)
            return Direction::E;
        }

    } else { // otherR > r

        if (otherC < c) {
            return Direction::SW;
        } else if (otherC == c) {
            return Direction::S;
        } else { // otherC > c
            return Direction::SE;
        }
    }

}


int getDeltaR( Direction direction, int n ) {

    if ( direction == Direction::NW ||
         direction == Direction::N ||
         direction == Direction::NE ) {
        return -1 * n;
    } else if ( direction == Direction::SW ||
                direction == Direction::S ||
                direction == Direction::SE ) {
        return n;
    } else {
        return 0;
    }
}


int getDeltaC( Direction direction, int n ) {

    if ( direction == Direction::NW ||
         direction == Direction::W ||
         direction == Direction::SW ) {
        return -1 * n;
    } else if ( direction == Direction::NE ||
                direction == Direction::E ||
                direction == Direction::SE ) {
        return n;
    } else {
        return 0;
    }

}


Position Position::getNSquaresForward(
        Direction direction, int n ) const {

    return { row + getDeltaR( direction, n ),
             col + getDeltaC( direction, n ) };

    /*
    if ( direction == Direction::NW ) {
        return { row - n, col - n };
    } else if ( direction == Direction::N ) {
        return { row - n, col };
    } else if ( direction == Direction::NE ) {
        return { row - n, col + n };
    } else if ( direction == Direction::W ) {
        return { row, col - n };
    } else if ( direction == Direction::E ) {
        return { row, col + n };
    } else if ( direction == Direction::SW ) {
        return { row + n, col - n };
    } else if ( direction == Direction::S ) {
        return { row + n, col };
    } else { // direction == Direction::SE
        return { row + n, col + n };
    }
    */
}


Position Position::getNSquaresBackward(
        Direction direction, int n ) const {

    return getNSquaresForward( OPPOSITE_DIRECTIONS.at( direction ), n );

}


std::vector<Position> Position::getLine(
        Direction direction, int endRow, int endCol ) const {

    std::vector<Position> line;
    int r = row;
    int c = col;
    int deltaR = getDeltaR( direction, 1 );
    int deltaC = getDeltaC( direction, 1 );
    /*
    cout << "r" << r << " c " << c << endl;
    cout << "dr" << deltaR << " dc " << deltaC <<  endl;

    cout << "End row " << endRow << " end col " << endCol;
    cout << "Position" << Position{ r + deltaR, c + deltaC } << endl;
    */




    for ( Position position = { r + deltaR, c + deltaC };
          position.getRow() < endRow && position.getCol() < endCol;
          position = { position.getRow() + deltaR,
                       position.getCol() + deltaC } ) {
        line.emplace_back( position );
    }
    return line;

}


std::vector<Position> Position::getInBetween(
        const Position &other ) const {

    std::vector<Position> line;
    int startRow = row;
    int startCol = col;
    int endRow = other.getRow();
    int endCol = other.getCol();
    Direction direction = getDirection( other );
    int deltaR = getDeltaR( direction, 1 );
    int deltaC = getDeltaC( direction, 1 );

    /*
    cout << "endRow" << endRow << "endCol" << endCol << endl;
    cout << "path start" << Position{ startRow + deltaR, startCol + deltaC } << endl;*/

    for ( Position position = { startRow + deltaR, startCol + deltaC };
          position.getRow() != endRow ||  position.getCol() != endCol;
          position = { position.getRow() + deltaR,
                       position.getCol() + deltaC } ) {
//      cout << "Position" << position << endl;
      line.emplace_back( position );
    }
    return line;

//    return getLine( getDirection( other ),
  //          other.getRow(), other.getCol() );

}


std::vector<Position> Position::getLineSegment (
        const Position &other ) const {

    std::vector<Position> line = getInBetween( other );
    line.insert( line.begin(), *this );
    line.emplace_back( other );
    return line;

}


bool Position::isNSquaresForwardTo(
        const Position &other, Direction direction, int n ) const {

    return (*this) ==
        Position{ other.getRow() + getDeltaR( direction, n ),
                  other.getCol() + getDeltaC( direction, n ) };

}


bool Position::isNSquaresDiagForwardTo(
        const Position &other, Direction direction, int n ) const {

    std::vector<Direction> forwardDiagonals = FORWARD_DIAGONALS.at( direction );
    for ( const auto &forwardDiagonal : forwardDiagonals ) {
        if ( isNSquaresForwardTo( other, forwardDiagonal, n ) ) {
            return true;
        }
    }
    return false;

}


bool Position::operator==( const Position &other ) const {

    return row == other.row && col == other.col;

}


bool Position::operator!=( const Position &other ) const {

    return !( *this == other );

}


std::ostream &operator<<(std::ostream &out, const Position &position) {

    return out << "( " << position.getRow() << ", "
               << position.getCol() << " )";

}
