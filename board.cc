#include "board.h"
#include "board_impl.h"
#include "piece_info.h"
#include "two_player_board_impl.h"
#include "four_player_board_impl.h"


const int STANDARD_NUM_ROW = 8;
const int STANDARD_NUM_COL = 8;
const int STANDARD_NUM_PLAYER = 2;


Board::Board() {}


Board::Board( std::unique_ptr<BoardImpl> boardImpl ) :

    boardImpl{ std::move( boardImpl ) } {}


int Board::getNumRows() const {

    return boardImpl->getNumRows();

}


int Board::getNumCols() const {

    return boardImpl->getNumCols();

}


PieceInfo Board::getPieceInfo( const Position &position ) const {

    return boardImpl->getPieceInfo( position );

}


std::vector<PieceInfo> Board::getPiecesInfo() const {

    return boardImpl->getPiecesInfo();

}


std::vector<Position> Board::getPossibleMoves( 
        const Position &from ) const {

    return boardImpl->getPossibleMoves( from );

}


std::vector<PieceInfo> Board::getUnderAttackBy (
        const Position &position ) const {

    return boardImpl->getUnderAttackBy( position );

}


Board Board::duplicateBoard() const {

    return Board{ boardImpl->duplicateBoard() };

}


void Board::resetBoardImpl( int numPlayers ) {

    std::vector< Observer<PieceInfo,MoveState>* > observers;
    if ( boardImpl.get() ) {
        observers = boardImpl->getObservers();
    }
    if ( numPlayers == 2 ) {
        boardImpl = std::make_unique<TwoPlayerBoardImpl>();
    } else if ( numPlayers == 4 ) {
        boardImpl = std::make_unique<FourPlayerBoardImpl>();
    }
    boardImpl->addObservers( observers );   

}

void Board::init( int numRows, int numCols, int numPlayers ) {

    resetBoardImpl( numPlayers );
    boardImpl->init( numRows, numCols );

}


void Board::init( int numRows, int numCols, int numPlayers,
        const std::map<Colour, Direction> &directionMap,
        const std::vector<Colour> cellColours ) {

    resetBoardImpl( numPlayers );
    boardImpl->init( numRows, numCols, directionMap, cellColours );

}


void Board::initStandardBoard() {

    init( STANDARD_NUM_ROW, STANDARD_NUM_COL, STANDARD_NUM_PLAYER );
    
    for ( int col = 0; col < getNumCols(); ++col ) {
        setPiece( { 1, col }, PieceType::Pawn, Colour::Black );
    }

    for ( int col = 0; col < getNumCols(); ++col ) {
        setPiece( { 6, col }, PieceType::Pawn, Colour::White );
    }

    setPiece( { 0, 0 }, PieceType::Rook, Colour::Black );
    setPiece( { 0, 1 }, PieceType::Knight, Colour::Black );
    setPiece( { 0, 2 }, PieceType::Bishop, Colour::Black );
    setPiece( { 0, 3 }, PieceType::Queen, Colour::Black );
    setPiece( { 0, 4 }, PieceType::King, Colour::Black );
    setPiece( { 0, 5 }, PieceType::Bishop, Colour::Black );
    setPiece( { 0, 6 }, PieceType::Knight, Colour::Black );
    setPiece( { 0, 7 }, PieceType::Rook, Colour::Black );

    setPiece( { 7, 0 }, PieceType::Rook, Colour::White );
    setPiece( { 7, 1 }, PieceType::Knight, Colour::White );
    setPiece( { 7, 2 }, PieceType::Bishop, Colour::White );
    setPiece( { 7, 3 }, PieceType::Queen, Colour::White );
    setPiece( { 7, 4 }, PieceType::King, Colour::White );
    setPiece( { 7, 5 }, PieceType::Bishop, Colour::White );
    setPiece( { 7, 6 }, PieceType::Knight, Colour::White );
    setPiece( { 7, 7 }, PieceType::Rook, Colour::White );

}


void Board::setPiece(
        const Position &position, PieceType type, Colour colour ) {

    boardImpl->setPiece( position, type, colour );

}


void Board::removePiece( const Position &position ) {
 
    boardImpl->removePiece( position );

}


void Board::movePiece( const Position &from, const Position &to ) {

    boardImpl->movePiece( from, to );

}


void Board::moveAndPromote(
        const Position &from, const Position &to, PieceType type ) {

    boardImpl->moveAndPromote( from, to, type );

}


bool Board::isValidBoard() const {

    return boardImpl->isValidBoard();

}


bool Board::isStalemate() const {

    return boardImpl->isStalemate();

}


bool Board::isCheckmate() const {

    return boardImpl->isCheckmate();

}


bool Board::isLegalMove( const Position &from, const Position &to ) const {
    
    return boardImpl->isLegalMove( from, to );

}
    

bool Board::isCheckMove( const Position &from, const Position &to ) const {

    return boardImpl->isCheckMove( from, to );

}


bool Board::isCapturingMove(
        const Position &from, const Position &to ) const {

    return boardImpl->isCapturingMove( from, to );

}


bool Board::isPromotionMove(
        const Position &from, const Position &to ) const {

    return boardImpl->isPromotionMove( from, to );

}


bool Board::isUnderAttack( Position position ) const {

    return boardImpl->isUnderAttack( position );

}


bool Board::isUnderAttack( Position position, Colour colour ) const {

    return boardImpl->isUnderAttack( position, colour );

}


std::ostream &operator<<(std::ostream &out, const Board &board) {
    
    return out << *( board.boardImpl );

}
