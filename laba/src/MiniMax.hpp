//
// Created by PotatoHD on 08.12.2021.
//

#pragma  once

#include <cstdint>
#include <cwchar>
#include "Pairs.hpp"

int8_t maxDepth = 20;

int8_t
MiniMax(const Board &board, bool isEnemyMove, // NOLINT(performance-unnecessary-value-param,misc-no-recursion)
        int8_t depth) {
    if (depth >= maxDepth)
        return 0;
    int8_t bestScore = isEnemyMove ? std::numeric_limits<int8_t>::max() : std::numeric_limits<int8_t>::min();
//    int8_t worstScore = std::numeric_limits<int8_t>::max();
    char gameState = board.GetGameState();
    if (gameState == '_')
        return 0;
    else if (gameState != 0) {
        return gameState == (isEnemyMove ? 'x' : 'o') ? -1 : 1;
    }
    for (size_t i = 0; i < board.size; ++i) {
        for (size_t j = 0; j < board.size; ++j) {
            if (board[Pair(i, j)] == '_') {
                board[Pair(i, j)] = isEnemyMove ? 'x' : 'o';
                auto x = MiniMax(board, !isEnemyMove, (int8_t) (depth + 1));
                if ((x > bestScore && !isEnemyMove) || (x < bestScore && isEnemyMove)) bestScore = x;
                cout << (long) bestScore << endl;
                board[Pair(i, j)] = '_';
            }
        }
    }
    return bestScore;
}

Pair<size_t> PredictMove(const Board &board) {

    Pair<size_t> move{std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max()};
    int8_t best_score = std::numeric_limits<int8_t>::min();

    for (size_t i = 0; i < board.size; ++i) {
        for (size_t j = 0; j < board.size; ++j) {
            if (board.Get(i, j) == '_') {
                board.Get(i, j) = 'o';
                int8_t score = MiniMax(board, true, 0);
                board.Get(i, j) = '_';
                cout << board << endl;
                if (score > best_score) {
                    best_score = score;
                    cout << (size_t) score << endl;
                    move = {i, j};
                }
            }
        }
    }
    return move;

}