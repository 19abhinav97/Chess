#include "cell_not_filled_exception.h"
#include <sstream>


CellNotFilledException::CellNotFilledException(
        Position position, std::string remark) :

    position{ position }, remark{ remark } {}


std::string CellNotFilledException::getErrorMessage() const {

    std::ostringstream errorMsg;
    errorMsg << "The Cell at " << position << " not filled. " << remark;
    return errorMsg.str();

}
