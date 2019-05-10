#ifndef BOARD_H
#define BOARD_H

#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include "colour.h"
#include "direction.h"
#include "piece_type.h"

class BoardImpl;
class PieceInfo;
class Position;
template <typename InfoType, typename StateType> class Observer;

class Board {

    std::unique_ptr<BoardImpl> boardImpl;

    void resetBoardImpl( int numPlayers );
    
  public:

    Board();
    Board( std::unique_ptr<BoardImpl> boardImpl );

    //Board( BoardImpl *boardImpl );

    // getNumRows() returns the number of rows of this board.
    int getNumRows() const;

    // getNumCols() returns the number of columns of this board.
    int getNumCols() const;

    // getPieceInfo( position ) returns the PieceInfo for
    //   the piece on position position.
    PieceInfo getPieceInfo( const Position &position ) const;

    // getPiecesInfo() returns a vector of PieceInfo reflecting
    //   the status of all pieces on the board.
    std::vector<PieceInfo> getPiecesInfo() const;

    // getPossibleMoves( from ) returns a vector of Position
    //   containing all possibles legal moves the piece at
    //   position from can make
    std::vector<Position> getPossibleMoves( const Position &from ) const;
    
    // getUnderAttackBy ( position ) returns a vector of PieceInfo
    //   for the Pieces on the board that are currently attacking
    //   the piece on position position.
    std::vector<PieceInfo> getUnderAttackBy ( 
            const Position &position ) const;

    // duplicateBoard() returns a defensive copy of the current
    //   board without observers attached. Any changes to the
    //   copy are local and will not affect the original board.
    Board duplicateBoard() const;

    // init( numRows, numCols, numPlayers ) initialize a board of
    //   numRows rows and numCols columns for numPlayers players.
    void init( int numRows, int numCols, int numPlayers );

    // init( numRows, numCols, numPlayers, directionMap) initialize a 
    //   board of numRows rows and numCols columns for numPlayers
    //   players, where each player's forward direction is specified
    //   in directionMap and the cell clours are specified in cellColours
    void init( int numRows, int numCols, int numPlayers, 
               const std::map<Colour, Direction> &directionMap,
               const std::vector<Colour> cellColours);

    // initStandardBoard() initialize the standard chessboard
    void initStandardBoard();

    // setPiece( position, type, colour ) sets a piece of type type
    //   with colour colour at position position.
    void setPiece( 
            const Position &position, PieceType type, Colour colour );

    // removePiece( position ) removes the piece at position position.
    void removePiece( const Position &position );

    // movePiece( from, to ) moves the piece from position from 
    //   to position to. InvalidMoveException will be thrown if
    //   such move is invalid.
    void movePiece( const Position &from, const Position &to );

    // moveAndPromote ( from, to, type ) moves the piece from position
    //   from to position to, and promotes the piece to type type.
    //   InvalidMoveException will be thrown if such move is invalid.
    void moveAndPromote( 
            const Position &from, const Position &to, PieceType type );

    // isValidBoard() checks if the board setup is valid.
    bool isValidBoard() const;

    // isStalemate() checks if the board is in stalemate.
    bool isStalemate() const;

    // isCheckmate() checks if the board is in checkmate.
    bool isCheckmate() const;

    // isLegalMove( from, to ) checks whether the move from position 
    //   from to  position to is legal or not.
    bool isLegalMove( const Position &from, const Position &to ) const;

    // isCheckMove( from, to ) checks whether the move from position 
    //   from to position to involves an attack on the opponent's king.
    bool isCheckMove( const Position &from, const Position &to ) const;

    // isCapturingMove( from, to ) checks whether the move from position
    //   from to position to captures an opponent's piece.
    bool isCapturingMove( 
            const Position &from, const Position &to ) const;

    // isPromotionMove( from, to ) checks whether the move from position
    //   from to position to results in a piece promotion
    bool isPromotionMove( 
            const Position &from, const Position &to ) const;

    // isUnderAttack( position ) checks whether the current piece at position
    //   is under attack by some opponent's piece or not
    bool isUnderAttack( Position position ) const;

    // isUnderAttack( position, colour ) checks whether the move from 
    //   position from to position to will put the piece being moved 
    //   (whose colour is colour) under attack by some opponent's piece.
    bool isUnderAttack( Position position, Colour colour ) const;

    //virtual ~Board();
    
    friend std::ostream &operator<<(std::ostream &out, const Board &board);

};

#endif
