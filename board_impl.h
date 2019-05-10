#ifndef BOARD_IMPL_H
#define BOARD_IMPL_H

#include <map>
#include <vector>
#include <memory>
#include <iostream>
#include "piece.h"
#include "colour.h"
#include "piece_type.h"

class Position;
class PieceInfo;
class MoveState;
template <typename InfoType, typename StateType> class Observer;

class BoardImpl {

    // set by user
    int numRows;
    int numCols;
    std::map<Colour, Direction> colourToDirectionMap;
    std::vector< Observer<PieceInfo,MoveState>* > observers;
    std::vector<Colour> cellColours;

    // internal representation
    std::vector<std::vector<std::unique_ptr<Piece>>> theBoard;
    std::vector<Piece*> kingsAlive;
    std::vector<Piece*> enPassant;

    virtual void initCells( 
            std::vector<std::vector<std::unique_ptr<Piece>>> &theBoard ) = 0;
    virtual size_t getNumPlayers() const = 0;
    virtual std::unique_ptr<BoardImpl> doDuplicateBoard() const = 0;

    Colour getCellColour ( const Position &position ) const;
    Piece &getPiece( const Position &position );
    const Piece &getConstPiece( const Position &position ) const;
    std::unique_ptr<Piece> &getPiecePtr( const Position &position );

    PieceType getType( const Position &position ) const;
    Direction getDirection( const Position &position ) const;
    Colour getColour( const Position &position ) const;
    size_t getKingColourCount() const;

    Position findPieceOnLine( PieceType type, 
            const Position &from, const Position &to ) const;
    Position findEnPassantCapturedPawn(
            const Position &from, const Position &to ) const;

    void mapPiecePointers( const std::vector<Piece*> &origin,
            std::vector<Piece*> &destination );
    void doEnPassantCapture(
            const Position &from, const Position &to );
    void doBasicMove( const Position &from, const Position &to );
    void doCastling( const Position &from, const Position &to );

    void resetBoard();
    void removePreviousEmPassant( Colour colour );
    void updateAlivePieces( const Position &from, const Position &to );

    bool arePawnsOnBorder() const;
    bool isEmpty( const Position &position ) const;
    bool isInvalidCell( const Position &position ) const;
    bool isFilled( const Position &position ) const;

    bool isKing( const Position &position ) const;
    bool isPawn( const Position &position ) const;
    bool isRook( const Position &position ) const;
    bool hasMoved( const Position &position ) const;
    
    bool areOpponents( 
            const Position &from, const Position &target) const;
    bool isBlocked(
            const Piece &piece,  const Position &to ) const;
    bool isSameColour(
            const Position &from, const Position &to ) const;
    bool isKingUnderAttackIfMoved(
            const Position &from, const Position &to ) const;
    bool isKingUnderAttack( const Position &from ) const;
    bool isReachingOtherEnd(
            const Position &from, const Position &to ) const;

    bool canMove(
            const Position &from, const Position &to ) const;
    bool canCapture(
            const Position &from, const Position &target ) const;
    bool canBeEnPassantCaptured( 
            const Position &from, const Position &to ) const;

    bool isRegularCapture(
            const Position &from, const Position &target ) const;
    bool isPuttingKingUnderAttack(
            const Position &from, const Position &to ) const;
    bool isNonCapturingMove(
            const Position &from, const Position &to ) const;
    bool isEnPassantCapture(
            const Position &from, const Position &to ) const;
    bool isCastlingMove(
            const Position &from, const Position &to ) const;

  protected:

    std::unique_ptr<Piece> makeEmptyCell( const Position &position );

  public:

    BoardImpl();
    BoardImpl( const BoardImpl &other );

    int getNumRows() const;
    int getNumCols() const;

    PieceInfo getPieceInfo( const Position &position ) const;
    std::vector<PieceInfo> getPiecesInfo() const;

    std::vector<Position> getPossibleMoves( 
            const Position &from ) const;
    std::vector<PieceInfo> getUnderAttackBy( 
            const Position &position ) const;

    std::unique_ptr<BoardImpl> duplicateBoard() const;

    std::map<Colour, Direction> getDefaultDirectionMap() const;
    std::vector<Colour> getDefaultcellColours() const;

    void init( int numRows, int numCols  );
    void init( int numRows, int numCols, 
               const std::map<Colour, Direction> &directionMap,
               const std::vector<Colour> cellColours );

    void addObserver( Observer<PieceInfo,MoveState>* observer );
    void removeObserver( Observer<PieceInfo,MoveState>* observer );
    std::vector< Observer<PieceInfo,MoveState>* > getObservers() const;
    void addObservers( 
            std::vector< Observer<PieceInfo,MoveState>* > observers );
   
    void setPiece( 
            const Position &position, PieceType type, Colour colour );
    void removePiece( const Position &position );

    void movePiece( const Position &from, const Position &to );
    void moveAndPromote( 
            const Position &from, const Position &to, PieceType type );

    bool isValidBoard() const;
    bool isStalemate() const;
    bool isCheckmate() const;
    bool isLegalMove( 
            const Position &from, const Position &to ) const;
    bool isCheckMove( 
            const Position &from, const Position &to ) const;
    bool isCapturingMove( 
            const Position &from, const Position &to ) const;
    bool isPromotionMove(
            const Position &from, const Position &to ) const;
    bool isUnderAttack( const Position &position ) const;
    bool isUnderAttack( 
            const Position &position, const Colour &colour ) const;

    virtual ~BoardImpl() = default;

    friend std::ostream &operator<<(std::ostream &out, const BoardImpl &board);

};

#endif
