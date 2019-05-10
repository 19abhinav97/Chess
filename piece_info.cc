#include "piece_info.h"


PieceInfo::PieceInfo( PieceType type, Colour colour,
        Direction direction, Position position, bool moved ) :

    type{ type }, colour{ colour }, direction{ direction },
    position{ position }, moved { moved } {}


PieceType PieceInfo::getType() const {

    return type;

}


Colour PieceInfo::getColour() const {

    return colour;

}


Direction PieceInfo::getDirection() const {

    return direction;

}


Position PieceInfo::getPosition() const {

    return position;

}
