#include "invalid_move_exception.h"
#include <string>
#include <sstream>

InvalidMoveException::InvalidMoveException(
        Position from, Position to, std::string remark ) :

    from{ from }, to{ to }, remark{ remark } {}

std::string InvalidMoveException::getErrorMessage() const{
  std::ostringstream ss;
  ss << from <<" " <<to << " "<< remark ;
  return ss.str();
}
