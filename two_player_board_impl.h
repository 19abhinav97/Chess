#ifndef TWO_PLAYER_BOARD_IMPL_H
#define TWO_PLAYER_BOARD_IMPL_H

#include <vector>
#include "board_impl.h"

class Piece;

class TwoPlayerBoardImpl : public BoardImpl {

    void initCells( 
            std::vector<std::vector<std::unique_ptr<Piece>>> &theBoard ) override;
    size_t getNumPlayers() const override;
    std::unique_ptr<BoardImpl> doDuplicateBoard() const override;

    public:

    TwoPlayerBoardImpl();
    TwoPlayerBoardImpl( const TwoPlayerBoardImpl &other );

};

#endif
