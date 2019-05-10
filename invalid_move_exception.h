#ifndef INVALID_MOVE_EXCEPTION_H
#define INVALID_MOVE_EXCEPTION_H

#include <string>
#include "position.h"

class InvalidMoveException {

    Position from;
    Position to;
    std::string remark;

  public:

    InvalidMoveException( Position from, Position to,
                          std::string remark = "");
    std::string getErrorMessage() const;

};
  
#endif
