#ifndef DISPLAY_IMPL_H
#define DISPLAY_IMPL_H

#include <vector>
#include <iostream>
#include "observer.h"
#include "piece_info.h"

class DisplayImpl : public Observer<PieceInfo, MoveState> {

    std::vector<std::vector<PieceInfo>> cells;
    int numRows;
    int numCols;

    virtual void doDisplay( std::ostream &out ) = 0;
    void initCells();

  protected:

    std::string getStringRep( PieceInfo piece );

  public:

    DisplayImpl( int numRows, int numCols );
    void display( std::ostream &out );
    int getNumRows() const;
    int getNumCols() const;
    std::vector<std::vector<PieceInfo>> getCellsInfo() const;

}

#endif
