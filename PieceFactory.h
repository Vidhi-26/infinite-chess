#ifndef PIECE_FACTORY_H
#define PIECE_FACTORY_H

#include <memory>
#include "Piece.h"
#include "Board.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"

class PieceFactory {
public:
    static std::unique_ptr<Piece> createPiece(char key, Board& board);
};

#endif // PIECE_FACTORY_H
