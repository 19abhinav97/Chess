#ifndef DISPLAY_H
#define DISPLAY_H

#include <memory>
#include <iostream>

class DisplayImpl;

class Display {

    std::unique_ptr<DisplayImpl> displayImpl;

    public:

    Display( int numRows, int numCols );
    void display( std::ostream &out );
    void reset();

}

#endif
