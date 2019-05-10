#ifndef INVALID_SETUP_EXCEPTION_H
#define INVALID_SETUP_EXCEPTION_H

#include <string>
#include "position.h"

class InvalidSetupException {

    std::string errorMessage;

  public:

    InvalidSetupException( std::string errorMessage );
    std::string getErrorMessage() const;

};
  
#endif
