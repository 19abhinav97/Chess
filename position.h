#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <vector>
#include "direction.h"

class Position {

    int row;
    int col;

  public:

    Position( int row, int col );

    int getRow() const;
    int getCol() const;

    // getRowDiff( other ) returns the difference between 
    // the row index of this and the row index of other
    int getRowDiff( const Position &other ) const;

    // getABSRowDiff( other ) returns the absolute difference
    // between the row index of this and the row index of other
    int getABSRowDiff( const Position &other ) const;

    // getColDiff( other ) returns the difference between
    // the col index of this and the col index of other
    int getColDiff( const Position &other ) const;

    // getABSColDiff( other ) returns the absolute difference
    // between the col index of this and the col index of other
    int getABSColDiff( const Position &other ) const;

    // getDirection( other ) returns the direction from
    // this to other, requires this and other to be on a straight line
    Direction getDirection( const Position &other ) const;

    // getNSquaresForward( direction, n ) returns the position
    // that is n squares forward in the direction relative to this
    Position getNSquaresForward( Direction direction, int n ) const;

    // getNSquaresBackward( direction, n ) returns the position
    // that is n squares backward in the direction relative to this
    Position getNSquaresBackward( Direction direction, int n ) const;

    // isNSquaresForwardTo( other, direction, n ) checks if 
    // this is in the direction forward relative to other and
    // if this is n squares forward along the direction
    bool isNSquaresForwardTo( 
            const Position &other, Direction direction, int n ) const;

    // isNSquaresDiagForwardTo( other, direction, n ) checks if
    // this is in the direction diagonally forward relative to other
    // and if this is n squares forward along the forward diagonal
    bool isNSquaresDiagForwardTo( 
            const Position &other, Direction direction, int n ) const;

    // isOnStraightLine( other ) checks if this and other are on a 
    // straight line of standard directions ( i.e. NW, N, NE, W, E,
    // SW, S, SE)
    bool isOnStraightLine( const Position &other ) const;

    // getInBetween( other ) returns a vector of positions along the
    // straight line in between this and other (exclusive). Requires
    // this and other to be on a straight line of standard directions
    // ( i.e. NW, N, NE, W, E, SW, S, SE )
    std::vector<Position> getInBetween ( const Position &other ) const;

    // getLineSegment( other ) returns a vector of positions along the
    // straight line in between this and other (inclusive). Requires
    // this and other to be on a straight line of standard directions
    // ( i.e. NW, N, NE, W, E, SW, S, SE )
    std::vector<Position> getLineSegment ( const Position &other ) const;

    // getLine( direction, endRow, endCol ) returns a vector of 
    // positions along the line segment starting from this (exclusive)
    // and in the direction direction and ends when row < 0 or  equals 
    // endRow or col < 0 or equals endCol (exclusive)
    std::vector<Position> getLine( 
            Direction direction, int endRow, int endCol ) const;

    bool operator==( const Position &other ) const;
    bool operator!=( const Position &other ) const;

};

std::ostream &operator<<(std::ostream &out, const Position &position);

#endif
