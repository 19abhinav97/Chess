#ifndef PIECE_H
#define PIECE_H

#include <vector>
#include <memory>
#include "subject.h"
#include "colour.h"
#include "position.h"
#include "direction.h"
#include "move_state.h"
#include "piece_type.h"

class Position;
class PieceInfo;

class Piece : public Subject<PieceInfo, MoveState> {

    Colour colour;
    Position position;
    Direction direction;
    // the forward direction for the player controlling the piece
    bool moved;

    virtual bool doCanMove( const Position &to ) const = 0;

    // default behaviour for for doCanCapture is set to be
    //   same as doCanMove. subclasses override doCanCapture
    //   if its capture move differs from standard move
    virtual bool doCanCapture( const Position &target ) const;

    // default behaviour for doCanJump is set to false.
    //   subclasses override doCanJump if it can jump over
    //   any piece that blocks its path of moving
    virtual bool doCanJump() const;

    virtual PieceType getType() const = 0;

    // default behaviour for doGetPath is set to return
    // the Positions on the straight line between this 
    // position and to. subclasses override doGetPath if
    // it does not always move along straight lines
    virtual std::vector<Position> doGetPath( 
            const Position &to ) const;

    void updatePosition( Position newPosition );

    virtual std::unique_ptr<Piece> doDuplicatePiece() const = 0;

  protected:

    Piece( Position position, Colour colour, 
           Direction direction, bool moved = false );
    bool isWithinStepSize( const Position &to, int stepSize ) const;

  public:

    int getRow() const;
    int getCol() const;
    Colour getColour() const;
    Position getPosition() const;
    Direction getDirection() const;
    PieceInfo getInfo() const;
    std::vector<Position> getPath( const Position &to ) const;
    
    void move( Position to );
    void capture( Position target );
    void beCaptured();

    bool canMove( const PieceInfo &to  ) const;
    bool canCapture( const PieceInfo &target ) const;
    bool canJump() const;
    bool hasMoved() const;

    std::unique_ptr<Piece> duplicatePiece() const;

};

#endif
