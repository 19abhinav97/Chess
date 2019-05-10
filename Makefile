CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -g -MMD -Werror=vla
EXEC = chess
OBJECTS = main.o \
		  board.o board_impl.o \
		  two_player_board_impl.o four_player_board_impl.o \
		  piece.o \
		  king.o queen.o bishop.o rook.o knight.o pawn.o \
		  position.o \
		  piece_info.o move_state.o \
		  empty_cell.o invalid_cell.o \
		  cell_not_filled_exception.o invalid_move_exception.o \
		  ai_level_1.o ai_level_2.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
