#include "board_impl.h"
#include "piece_info.h"
#include <algorithm>
#include <set>
#include "king.h"
#include "queen.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "pawn.h"
#include "empty_cell.h"
#include "invalid_cell.h"
#include "invalid_move_exception.h"
#include <iostream>

using namespace std;


const std::map<Colour, Direction> DEFAULT_COLOUR_TO_DIRECTION_MAP =
    { { Colour::Black, Direction::S },
      { Colour::White, Direction::N },
      { Colour::Red, Direction::E },
      { Colour::Green, Direction::W } };
const std::vector<Colour> DEFAULT_CELL_COLOURS =
    { Colour::Yellow, Colour::Orange };
const std::map<PieceType, std::string> PIECE_TO_STRING_MAP =
    { { PieceType::King, "k" }, { PieceType::Queen, "q" },
      { PieceType::Bishop, "b" }, { PieceType::Rook, "r" },
      { PieceType::Knight, "n" }, { PieceType::Pawn, "p" },
      { PieceType::EmptyCell, " "}, { PieceType::InvalidCell, "x" } };

const std::vector< Observer<PieceInfo,MoveState>* > INITIAL_OBSERVERS =
    {};
const int KING_CASTLING_STEP_SIZE = 2;
const int EN_PASSANT_FORWARD_STEP_SIZE = 2;
const int EN_PASSANT_BACKWARD_STEP_SIZE = 1;


BoardImpl::BoardImpl() :

    colourToDirectionMap{ DEFAULT_COLOUR_TO_DIRECTION_MAP },
    observers{ INITIAL_OBSERVERS },
    cellColours{ DEFAULT_CELL_COLOURS } {}


void BoardImpl::mapPiecePointers( const std::vector<Piece*> &origin,
        std::vector<Piece*> &destination ) {

    std::vector<Piece*> newPiecePointers;
    for ( const auto &oldPiece : origin ) {
        Position position = oldPiece->getPosition();
        for ( const auto &row : theBoard ) {
            for ( const auto &newPiece : row ) {
                if ( newPiece->getPosition() == position ) {
                    newPiecePointers.emplace_back( newPiece.get() );
                    break;
                }
            }
        }
    }
    destination = newPiecePointers;

}


std::map<Colour, Direction> BoardImpl::getDefaultDirectionMap() const {

    return DEFAULT_COLOUR_TO_DIRECTION_MAP;

}


std::vector<Colour> BoardImpl::getDefaultcellColours() const {

    return DEFAULT_CELL_COLOURS;

}


const Piece &BoardImpl::getConstPiece(
        const Position &position ) const {

    int row = position.getRow();
    int col = position.getCol();
    return *( theBoard.at( row ).at( col ) );

}


BoardImpl::BoardImpl( const BoardImpl &other ) :

    numRows{ other.numRows }, numCols{ other.numCols },
    colourToDirectionMap{ other.colourToDirectionMap },
    observers{ INITIAL_OBSERVERS },
    cellColours { other.cellColours } {

        for ( int row = 0; row < numRows; ++row ) {
            theBoard.emplace_back(
                    std::vector<std::unique_ptr<Piece>>{} );
//            cout << "before get row";
            std::vector<std::unique_ptr<Piece>> &theRow = theBoard.at( row );
  //          cout << "after get row";
            for ( int col = 0; col < numCols; ++col ) {
                theRow.emplace_back(
                        other.getConstPiece( Position{row, col} ).duplicatePiece() );
            }
        }
        cout << "before map kingsAlive\n";
        mapPiecePointers( other.kingsAlive, kingsAlive );
        cout << "after kingsAlive\n";
        mapPiecePointers( other.enPassant, enPassant );
        cout << "copied\n";

}


int BoardImpl::getNumRows() const {

    return numRows;

}


int BoardImpl::getNumCols() const {

    return numCols;

}


PieceInfo BoardImpl::getPieceInfo( const Position &position ) const {

    return getConstPiece( position ).getInfo();

}


Colour BoardImpl::getCellColour ( const Position &position ) const {

    int row = position.getRow();
    int col = position.getCol();
    return cellColours.at( ( row + col ) % cellColours.size() );

}


PieceType BoardImpl::getType( const Position &position ) const {

    return getPieceInfo( position ).getType();

}

bool BoardImpl::isEmpty( const Position &position ) const {

    return getType( position ) == PieceType::EmptyCell;

}


bool BoardImpl::isInvalidCell ( const Position &position ) const {

    return getType( position ) == PieceType::InvalidCell;

}


bool BoardImpl::isKing( const Position &position ) const {

    return getType( position ) == PieceType::King;

}


bool BoardImpl::isPawn( const Position &position ) const {

    return getType( position ) == PieceType::Pawn;

}


bool BoardImpl::isRook( const Position &position ) const {

    return getType( position ) == PieceType::Rook;

}


bool BoardImpl::isFilled( const Position &position ) const {

    return !isEmpty( position ) &&
           !isInvalidCell( position );

}


bool BoardImpl::hasMoved( const Position &position ) const {

    return getConstPiece( position ).hasMoved();

}


std::vector<PieceInfo> BoardImpl::getPiecesInfo() const {

    std::vector<PieceInfo> piecesInfo;

    for ( int row = 0; row < numRows; ++row ) {
        for ( int col = 0; col < numCols; ++col ) {
            Position position = Position{ row, col };
            if ( isFilled( position ) ) {
                piecesInfo.emplace_back( getPieceInfo( position ) );
            }
        }
    }

    return piecesInfo;

}


std::unique_ptr<BoardImpl> BoardImpl::duplicateBoard() const {

    return doDuplicateBoard();

}


bool BoardImpl::isBlocked(
        const Piece &piece,  const Position &to ) const {

    std::vector<Position> path = piece.getPath( to );

    for ( const auto &position : path ) {
        if ( isInvalidCell( position ) ||
             ( !isEmpty( position ) && !piece.canJump() ) ) {
            return true;
        }
    }
    return false; // path clear

}


bool BoardImpl::canMove(
        const Position &from, const Position &to ) const {

    const Piece &piece = getConstPiece( from );
    return piece.canMove( getPieceInfo( to ) ) && !isBlocked( piece, to );

}

/*
// test if the piece at position from can capture the piece at to if
//   a piece of colour colour is moved to position to
bool canCaptureIfMoved( const Position &from,
        const Position &to, Colour colour ) const {

    const Piece &piece = getConstPiece( from );
    return colour != Colour::NoColour && piece.getColour() != colour &&
           piece.canCapture( to ) && !isBlocked( piece, to );

}
*/


Colour BoardImpl::getColour( const Position &position ) const {

    return getPieceInfo( position ).getColour();

}


bool BoardImpl::isSameColour(
                const Position &from, const Position &to ) const {

    return getColour( from ) == getColour( to );

}


bool BoardImpl::areOpponents(
        const Position &from, const Position &target) const {

    return isFilled( from ) && isFilled( target ) &&
           !isSameColour( from, target );

}


// excluding enPassant capture
bool BoardImpl::isRegularCapture(
        const Position &from, const Position &target ) const {

    const Piece &piece = getConstPiece( from );
    return areOpponents( from, target ) &&
           piece.canCapture( getPieceInfo( target ) ) &&
           !isBlocked( piece, target );

}


// return Position { numRows, numCols } if not found
Position BoardImpl::findEnPassantCapturedPawn(
        const Position &from, const Position &to ) const {

    for ( const auto &pawn : enPassant ) {

        Position pawnPosition = pawn->getPosition();
        Position pawnSkipped = pawnPosition.getNSquaresBackward(
                pawn->getDirection(), EN_PASSANT_BACKWARD_STEP_SIZE );

        if ( pawnSkipped == to  &&
                !isSameColour( pawnPosition, from ) ) {
            return pawnPosition;

        }
    }
    return { numRows, numCols };

}


std::unique_ptr<Piece> &BoardImpl::getPiecePtr(
        const Position &position ) {

    int row = position.getRow();
    int col = position.getCol();
    return theBoard.at( row ).at( col );

}


void BoardImpl::doEnPassantCapture(
        const Position &from, const Position &to ) {

    getPiece( from ).capture( to );
    getPiecePtr( to ).swap( getPiecePtr( from ) );
    removePiece( from );

    Position pawnToCapture = findEnPassantCapturedPawn( from, to );
    getPiece( pawnToCapture ).beCaptured();
    removePiece( pawnToCapture );

}


bool BoardImpl::isEnPassantCapture(
        const Position &from, const Position &to ) const {

    Position pawnToCapture = findEnPassantCapturedPawn( from, to );
    return isPawn( from ) &&
           getConstPiece( from ).canCapture( getPieceInfo( to ) ) &&
           pawnToCapture != Position{ numRows, numCols };

    /*
    if ( isPawn( from ) &&
         getConstPiece( from ).canCapture( to ) ) {


        for ( const auto &pawn : enPassant ) {

            Position pawnPosition = pawn->getPosition();
            int backwardStepSize = 1;
            Position pawnSkipped =
                pawnPosition.getNSquaresBackward(
                        pawn->getDirection(), backwardStepSize );

            if ( pawnSkipped == to  &&
                    !isSameColour( pawnPosition, from ) ) {
                return true;
            }

        }

    }
    return false;
    */

}


bool BoardImpl::canCapture(
        const Position &from, const Position &to ) const {

    return isRegularCapture( from, to ) ||
           isEnPassantCapture( from, to );

}


std::unique_ptr<Piece> BoardImpl::makeEmptyCell(
        const Position &position ) {

    return std::make_unique<EmptyCell>(
            position, getCellColour( position ) );

}


void BoardImpl::removePiece( const Position &position ) {

    if ( !isInvalidCell( position ) ) {
        getPiecePtr( position ) = makeEmptyCell( position );
    }

}


// simply moves the piece from position from to position to with
// no enPassant speical capture, no castling, no check if the move
// is legal, etc. allows for special case handling

void BoardImpl::doBasicMove( const Position &from, const Position &to ) {

    if ( !isFilled( from ) ) {
        throw InvalidMoveException{ from, to,
            "No valid piece at the starting position" };
    } else if ( isInvalidCell( to ) ) {
        throw InvalidMoveException{ from, to,
            "The ending position is an invalid cell" };
    } else if ( from != to ) { // no need to move if at same position
        if ( isFilled( to ) ) {
            getPiece( from ).capture( to );
            getPiece( to ).beCaptured();
        } else {
            getPiece( from ).move( to );
        }
        getPiecePtr( to ).swap( getPiecePtr( from ) );
        removePiece( from );

        /*
        getPiece( from ).move( to );
        getPiecePtr( to ).swap( getPiecePtr( from ) );
        removePiece( from );
        */
    }

}




bool BoardImpl::isKingUnderAttackIfMoved(
        const Position &from, const Position &to ) const {
//        const Position &position, Colour colour ) const {

    std::unique_ptr<BoardImpl> simulatedBoard = duplicateBoard();
    simulatedBoard->doBasicMove( from, to );
    for ( int row = 0; row < simulatedBoard->numRows; ++row ) {
        for ( int col = 0; col < simulatedBoard->numCols; ++col ) {
            if ( simulatedBoard->canCapture(
                        Position{ row, col }, to ) ) {
                return true;
            }
        }
    }
    return false;
/*
    for ( int row = 0; row < numRows; ++row ) {
        for ( int col = 0; col < numCols; ++col ) {
            if ( canCaptureIfMoved( Position{ row, col },
                                    position, colour ) ) {
                return true;
            }
        }
    }
    return false;
*/
}


bool BoardImpl::isKingUnderAttack( const Position &from ) const {

    return isKingUnderAttackIfMoved( from, from );

}


bool BoardImpl::isPuttingKingUnderAttack(
        const Position &from, const Position &to ) const {

    if ( !isKing( from ) || isCastlingMove( from, to ) ||
        ( !canMove( from, to ) && !canCapture( from, to ) ) ) {
        return false;
    } else {
        return isKingUnderAttackIfMoved( from, to );
               //  position, getConstPiece( from ).getColour() );
    }


    //BoardImpl simulatedBoard = *this;
    /*
    for ( int row = 0; row < numRows; ++row ) {
        for ( int col = 0; col < numCols; ++col ) {
            if ( canCaptureIfMoved( Position{ row, col }, to,  ) ) {
                return true;
            }
        }
    }
    return false; */

}


// returns the position of piece type on the line starting from
//   position from and connecting to position to.

Position BoardImpl::findPieceOnLine( PieceType type,
        const Position &from, const Position &to) const {

    Direction direction = from.getDirection( to );
    for ( const Position &position :
            from.getLine( direction, numRows, numCols ) ) {
        if ( getType( position ) == type ) {
            return position;
        }
    }
    return Position{ numRows, numCols };

}


void BoardImpl::doCastling(
        const Position &from, const Position &to ) {

    doBasicMove( from, to ); // move King

    Position rookPosition =
        findPieceOnLine( PieceType::Rook, from, to );
    Position rookTarget = from.getInBetween( to ).front();

    doBasicMove( rookPosition, rookTarget ); // move Rook

}


bool BoardImpl::isCastlingMove(
        const Position &from, const Position &to ) const {

    if ( !isKing( from ) || hasMoved( from ) ||
         !isEmpty( to ) || isKingUnderAttack( from ) ) {
        return false;
    }

    Direction direction = from.getDirection( to );
    if ( !to.isNSquaresForwardTo(
                from, direction, KING_CASTLING_STEP_SIZE ) ) {
        return false;
    }

    Position rookPosition =
        findPieceOnLine( PieceType::Rook, from, to );
    if ( rookPosition == Position{ numRows, numCols } // rook not found
            || hasMoved( rookPosition ) ) {
        return false;
    }

    // king must not be in check along the path
    for ( const Position &position : from.getLineSegment( to ) ) {
        if ( isKingUnderAttackIfMoved( from, position ) ) {
                return false;
        }
    }

    // king also cannot be in check after castling
    std::unique_ptr<BoardImpl> simulatedBoard = duplicateBoard();
    simulatedBoard->doCastling( from, to );
    return !( simulatedBoard->isKingUnderAttack( to ) );

}


bool BoardImpl::isNonCapturingMove(
        const Position &from, const Position &to ) const {
    return !isPuttingKingUnderAttack( from, to ) &&
        ( canMove( from, to ) || isCastlingMove( from, to ) );

}


bool BoardImpl::isCapturingMove(
        const Position &from, const Position &to ) const {

    return !isPuttingKingUnderAttack( from, to ) &&
        ( isRegularCapture( from, to ) || isEnPassantCapture( from, to ) );

}


bool BoardImpl::isLegalMove(
        const Position &from, const Position &to ) const {

    return isNonCapturingMove( from, to ) ||
           isCapturingMove( from, to );

}


std::vector<Position> BoardImpl::getPossibleMoves(
        const Position &from ) const {

    std::vector<Position> possibleMoves;

    for ( int row = 0; row < numRows; ++row ) {
        for ( int col = 0; col < numCols; ++col ) {
            Position to = Position{ row, col };
            if ( isLegalMove( from, to ) ) {
                possibleMoves.emplace_back( to );
            }
        }
    }

    return possibleMoves;

}


std::vector<PieceInfo> BoardImpl::getUnderAttackBy(
        const Position &position ) const {

    std::vector<PieceInfo> attackers;

    for ( int row = 0; row < numRows; ++row ) {
        for ( int col = 0; col < numCols; ++col ) {
            Position from = Position{ row, col };
            Position to = position;
            if ( isCapturingMove( from, to ) ) {
                attackers.emplace_back( getPieceInfo( from ) );
            }
        }
    }

    return attackers;

}


/*
BoardImpl BoardImpl::duplicaeBoard() const {

    return BoardImpl{ numRows, numCols,
        colourToDirectionMap, INITIAL_OBSERVERS };

}
*/

void BoardImpl::resetBoard() {

    theBoard.clear();
    kingsAlive.clear();
    enPassant.clear();

}


void BoardImpl::init( int numRows, int numCols ) {

    resetBoard();
    this->numRows = numRows;
    this->numCols = numCols;
    initCells( theBoard );

}


void BoardImpl::init( int numRows, int numCols,
        const std::map<Colour, Direction> & colourToDirectionMap,
        const std::vector<Colour> cellColours) {

    init( numRows, numCols );
    this->colourToDirectionMap = colourToDirectionMap;
    this->cellColours = cellColours;

}


void BoardImpl::addObserver(
        Observer<PieceInfo,MoveState>* observer ) {

    observers.emplace_back( observer );

}


void BoardImpl::removeObserver(
        Observer<PieceInfo,MoveState>* observer ) {

    observers.erase(
            std::remove( observers.begin(), observers.end(), observer ),
            observers.end() );

}


std::vector< Observer<PieceInfo,MoveState>* > BoardImpl::getObservers() const {

    return observers;

}


void BoardImpl::addObservers(
        std::vector< Observer<PieceInfo,MoveState>* > observers ) {

    for ( auto observer : observers ) {
        addObserver( observer );
    }

}


Piece &BoardImpl::getPiece( const Position &position ) {

    return *getPiecePtr( position );

    /*
    int row = Position.getRow();
    int col = Position.getCol();
    return *( theBoard.at( row ).at( col ) );*/

}


void BoardImpl::setPiece(
        const Position &position, PieceType type, Colour colour ) {

    Direction direction = colourToDirectionMap.at( colour );
    std::unique_ptr<Piece> &piece = getPiecePtr( position );
    if ( type == PieceType::King ) {
        piece = std::make_unique<King>( position, colour, direction );
        kingsAlive.emplace_back( piece.get() );
    } else if ( type == PieceType::Queen ) {
        piece = std::make_unique<Queen>( position, colour, direction );
    } else if ( type == PieceType::Bishop ) {
        piece = std::make_unique<Bishop>( position, colour, direction );
    } else if ( type == PieceType::Rook ) {
        piece = std::make_unique<Rook>( position, colour, direction );
    } else if ( type == PieceType::Knight ) {
        piece = std::make_unique<Knight>( position, colour, direction );
    } else if ( type == PieceType::Pawn ) {
        piece = std::make_unique<Pawn>( position, colour, direction );
    } else if ( type == PieceType::EmptyCell ) {
        piece = std::make_unique<EmptyCell>( position, colour, direction );
    } else {
        piece = std::make_unique<InvalidCell>( position, colour, direction );
    }

}


Direction BoardImpl::getDirection( const Position &position ) const {

    return getPieceInfo( position ).getDirection();

}


bool BoardImpl::isReachingOtherEnd(
        const Position &from, const Position &to ) const {

    Direction direction = getDirection( from );
    if ( direction == Direction::N ) {
        return to.getRow() == 0;
    } else if ( direction == Direction::S ) {
        return to.getRow() == ( numRows - 1 );
    } else if ( direction == Direction::W ) {
        return to.getCol() == 0;
    } else if ( direction == Direction::E ) {
        return to.getCol() == ( numCols - 1 );
    } else {
        return false;
    }

}


bool BoardImpl::isPromotionMove(
        const Position &from, const Position &to ) const {

    return isPawn( from ) && isReachingOtherEnd( from, to );

}


bool BoardImpl::canBeEnPassantCaptured(
        const Position &from, const Position &to ) const {

    return isPawn( from ) && !hasMoved( from ) &&
        to.isNSquaresForwardTo( from, getDirection( from ),
                EN_PASSANT_FORWARD_STEP_SIZE );

}


void BoardImpl::removePreviousEmPassant( Colour colour ) {

  for(unsigned int i = 0; i < enPassant.size(); i++){
    if( enPassant.at(i)->getColour() == colour){
      enPassant.erase(enPassant.begin() + i);
    }
  }
  /*
    for ( auto pawnIter = enPassant.begin();
            pawnIter != enPassant.end(); ++pawnIter ) {
      cout << "Before dereference\n";
        if ( (*pawnIter)->getColour()  == colour ) {
          cout << "Done derefernecing\n";
            enPassant.erase( pawnIter );
        }
    }
    */


}


void BoardImpl::updateAlivePieces( const Position &from, const Position &to ) {

    if ( isCapturingMove( from, to ) && isKing( to ) ) {
        kingsAlive.erase(
                std::remove( kingsAlive.begin(),kingsAlive.end(),
                             getPiecePtr( to ).get() ),
                kingsAlive.end());
        for ( int row = 0; row < numRows; ++row ) {
            for ( int col = 0; col < numCols; ++col ) {
                Position position = Position{ row, col };
                if ( isSameColour( position, to ) ) {
                    removePiece( position );
                }
            }
        }
    }

}


void BoardImpl::movePiece( const Position &from, const Position &to ) {

    if ( !isLegalMove( from, to ) ) {
        throw InvalidMoveException{ from, to };
    }
    removePreviousEmPassant( getColour( from ) );
    updateAlivePieces( from, to );

    /*
    // remove EnPassant from previous round
    for ( const auto &pawnIter = enPassant.begin();
            pawnIter != enPassant.end(); ++pawnIter ) {
        if ( (*pawnIter)->getColour()  == getColour( from ) ) {
            enPassant.erase( pawnIter );
        }
    }
    */

    if ( isEnPassantCapture( from, to ) ) {
        doEnPassantCapture( from, to );
    } else if ( isCastlingMove( from, to ) ) {
        doCastling( from, to );
    } else { // regular move/capture

        if ( canBeEnPassantCaptured( from, to ) ) {
            enPassant.emplace_back( getPiecePtr( from ).get() );
        }

        doBasicMove( from, to );

    }

}


void BoardImpl::moveAndPromote(
        const Position &from, const Position &to, PieceType type ) {

    if ( !isLegalMove( from, to ) ) {
        throw InvalidMoveException{ from, to };
    } else if ( !isPromotionMove( from, to ) ) {
        throw InvalidMoveException{ from, to, "Not a promotion move" };
    }

    removePreviousEmPassant( getColour( from ) );
    updateAlivePieces( from, to );

    if ( isEnPassantCapture( from, to ) ) {
        doEnPassantCapture( from, to );
    } else {
        doBasicMove( from, to );
        setPiece( to, type, getColour( to ) );
    }

}


size_t BoardImpl::getKingColourCount() const{

    std::set<Colour> colours;
    for ( const auto &king : kingsAlive ) {
        colours.emplace( king->getColour() );
    }
    return colours.size();

}


bool BoardImpl::arePawnsOnBorder() const {

    for ( int row = 0; row < numRows; ++row ) {
        for ( int col = 0; col < numCols; ++col ) {
            if ( row == 0 || row == ( numRows - 1 ) ||
                 col == 0 || col == ( numCols - 1 ) ) {
                if ( isPawn( Position{ row, col } ) ) {
                    return true;
                }
            }
        }
    }
    return false;

}


bool BoardImpl::isValidBoard() const {

    size_t numPlayers = getNumPlayers();
    return kingsAlive.size() == numPlayers &&
        getKingColourCount() == numPlayers &&
        !arePawnsOnBorder();

}


bool BoardImpl::isStalemate() const {

    for ( int row = 0; row < numRows; ++row ) {
        for ( int col = 0; col < numCols; ++col ) {
            if ( getPossibleMoves( Position{ row, col } ).size() != 0 ) {
                return false;
            }
        }
    }
    return true;

}


bool BoardImpl::isCheckmate() const {

    return kingsAlive.size() == 1;

}


bool BoardImpl::isCheckMove(
        const Position &from, const Position &to ) const {

    if ( isLegalMove( from, to ) ) {
        cout << "start duplicating\n";
        std::unique_ptr<BoardImpl> simulatedBoard = duplicateBoard();
        cout << "duplicateDone\n";
        simulatedBoard->movePiece( from, to );
        cout << "simulatemovedone\n";
        for ( const auto &king : simulatedBoard->kingsAlive ) {
          cout << "start test\n";
            if ( simulatedBoard->isCapturingMove(
                        to,  king->getPosition() ) ) {
              cout << "true\n";
                return true;
            }
          cout << "end test\n";
        }
    }
    cout << "endIsCheckMove\n";
    return false;

}


bool BoardImpl::isUnderAttack( const Position &position ) const {

    return getUnderAttackBy( position ).size() != 0;

}


bool BoardImpl::isUnderAttack( const Position &position,
        const Colour &colour ) const {

    std::unique_ptr<BoardImpl> simulatedBoard = duplicateBoard();
    simulatedBoard->setPiece( position, PieceType::Pawn, colour );
    return simulatedBoard->isUnderAttack( position );

}


std::string getStringRep( PieceInfo piece ) {

    std::string stringRep = PIECE_TO_STRING_MAP.at( piece.getType() );
    if ( piece.getColour() == Colour::White ) {
        std::transform(
                stringRep.begin(), stringRep.end(),
                stringRep.begin(), ::toupper);
    }
    return stringRep;

}


std::ostream &operator<<(std::ostream &out, const BoardImpl &board) {

    for ( int row = 0; row < board.getNumRows(); ++row ) {
        out << row << " ";
        for (int col = 0; col < board.getNumCols(); ++col ) {
            out << getStringRep( board.getPieceInfo( { row, col } ) );
        }
        out << std::endl;
    }
    out << std::endl << "  ";

    // print row indexes
    char c = 'a';
    for ( int j = 0; j < board.getNumCols(); ++j ) {
        char currentC = c + j;
        out << currentC;
    }
    return out << std::endl;

}
