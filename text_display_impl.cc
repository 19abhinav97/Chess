#include "text_display_impl.h"


void TextDisplayImpl::doDisplay ( std::ostream &out ) {

    std::vector<std::vector<PieceInfo>> cells = getCellsInfo();
    for ( int row = 0; row < numRows; ++ row ) {
        out << row << " ";
        for ( int col = 0; col < numCols; ++col ) {
            out << getStringRep( cells.at( row ).at( col ) );
        }
        out << std::endl;
    }
    out << std::endl;

    // print row indexes
    char c = 'a';
    for ( int j = 0; j < numCols; ++j ) {
        out << c + j;
    }

}


void TextDisplayImpl::doNotify( Subject<PieceInfo, MoveState> &whoFrom ) {

    

}
