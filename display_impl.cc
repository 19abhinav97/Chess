#include "display_impl.h"
#include "piece_info.h"
#include "piece_type.h"
#include <map>
#include <algorithm>
#include <string>


const std::map<PieceType, std::string> PIECE_TO_STRING_MAP = 
    { { PieceType::King, "k" }, { PieceType::Queen, "q" }, 
      { PieceType::Bishop, "b" }, { PieceType::Rook, "r" },
      { PieceType::Knight, "n" }, { PieceType::Pawn, "p" },
      { PieceType::EmptyCell, " "}, { PieceType::InvalidCell, "x" } };


std::string DisplayImpl::getStringRep( PieceInfo piece ) {

    std::string stringRep = PIECE_TO_STRING_MAP.at( piece.getType() );

    if ( piece.getColour() == Colour::White ) {
        std::transform( 
                stringRep.begin(), stringRep.end(), 
                stringRep.begin(), ::toupper);
    }

    return stringRep;

}


void DisplayImpl::initCells() {

    cells.clear();
    for ( int row = 0; row < numRows; ++ row ) {
        std::vector<PieceInfo> theRow;
        for ( int col = 0; col < numCols; ++col ) {
            theRow.emplace_back( 
                    PieceInfo{ PieceType::InvalidCell,
                               Direction::NE,
                               { row, col } } );
        } 
        cells.emplace_back( theRow );
    }
    
}


DisplayImpl::DisplayImpl( int numRows, int numCols ) :

    numRows{ numRows }, numCols{ numCols } {

    initCells();

}


void DisplayImpl::display( std::ostream &out ) {

    doDisplay();

}


int DisplayImpl::getNumRows() const {

    return numRows;

}


int DisplayImpl::getNumCols() cosnt {

    return numCols;

}


std::vector<std::vector<PieceInfo>> DisplayImpl::getCellsInfo const {

    return cells;

}
