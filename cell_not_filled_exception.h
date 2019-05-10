#ifndef CELL_NOT_FILLED_EXCEPTION_H
#define CELL_NOT_FILLED_EXCEPTION_H

#include <string>
#include "position.h"

class CellNotFilledException {

    Position position;
    std::string remark;

    public:

    CellNotFilledException( Position position, 
                            std::string remark = "");
    std::string getErrorMessage() const;

};

#endif
