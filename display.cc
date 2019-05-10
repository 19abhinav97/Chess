#include "display.h"
#include "display_impl.h"


Display::Display( int width, int height ) :

    displayImpl{ std::make_unique<DisplayImpl>( width, height ) } {}


void Display::display( std::ostream &out ) {

    displayImpl->display( out ); 

}


void Display::reset() {

    displayImpl->reset();

}
