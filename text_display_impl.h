#ifndef TEXT_DISPLAY_IMPL_H
#define TEXT_DISPLAY_IMPL_H

#include "display_impl.h"

class TextDisplayImpl : public DisplayImpl {

    void doDisplay ( std::ostream &out );
    void doNotify( Subject<PieceInfo, MoveState> &whoFrom );

};

#endif
