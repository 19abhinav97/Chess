#include "two_player_board_impl.h"


const int NUM_PLAYERS = 2;


TwoPlayerBoardImpl::TwoPlayerBoardImpl() {}


TwoPlayerBoardImpl::TwoPlayerBoardImpl( 
        const TwoPlayerBoardImpl &other ) :

    BoardImpl{ other } {}


void TwoPlayerBoardImpl::initCells( 
        std::vector<std::vector<std::unique_ptr<Piece>>> &theBoard ) {

    theBoard.clear();
    for ( int row = 0; row < getNumRows(); ++row ) {
        theBoard.emplace_back(
                std::vector<std::unique_ptr<Piece>>{} );
        std::vector<std::unique_ptr<Piece>> &theRow = theBoard.at( row );
        for ( int col = 0; col < getNumCols(); ++col ) {
            theRow.emplace_back( makeEmptyCell( { row, col } ) );
        }
    }

}


size_t TwoPlayerBoardImpl::getNumPlayers() const {

    return NUM_PLAYERS;

}


std::unique_ptr<BoardImpl> TwoPlayerBoardImpl::doDuplicateBoard() const {

    return std::make_unique<TwoPlayerBoardImpl>( *this );

}
