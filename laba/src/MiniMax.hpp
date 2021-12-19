//
// Created by PotatoHD on 08.12.2021.
//

#pragma  once

#include <cstdint>
#include <cwchar>
#include "Pairs.hpp"

size_t maxDepth = 3;

int8_t
MiniMax(const Board &board, bool isEnemyMove, // NOLINT(performance-unnecessary-value-param,misc-no-recursion)
        size_t depth) {
    if (depth >= maxDepth) {
//        cout << "Exceeded" << endl;
        return 0;
    }
    int8_t bestScore = isEnemyMove ? std::numeric_limits<int8_t>::max() : std::numeric_limits<int8_t>::min();
    char gameState = board.GetGameState();
    if (gameState == '_')
        return 0;
    else if (gameState != 0) {
        return (int8_t) ((gameState == 'o') ? 1 : gameState == 'x' ? -1 : 0);
    }
    for (size_t i = 0; i < board.size; ++i) {
        for (size_t j = 0; j < board.size; ++j) {
            if (board.Get(i, j) == '_' && board.IsInClusters(i, j)) {
//                cout << i << ' ' << j << endl;
                board.Set(i, j, isEnemyMove ? 'x' : 'o');
                int8_t x = MiniMax(board, !isEnemyMove, depth + 1);
                if ((x > bestScore && !isEnemyMove) || (x < bestScore && isEnemyMove)) bestScore = x;

//                cout << (long) bestScore << endl;
                board.Set(i, j, '_');
                if ((!isEnemyMove && bestScore == 1) || (bestScore == -1 && isEnemyMove))
                    return bestScore;
            }
        }
    }
    return bestScore;
}

Pair<size_t> PredictMove(const Board &board) {

    Pair<size_t> move{std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max()};
    int8_t best_score = std::numeric_limits<int8_t>::min();
    size_t movesCount = 1;
    size_t boardSize = board.GetSize();
    for (maxDepth = 0; movesCount < 1000000; ++maxDepth) {
        movesCount *= boardSize - board.GetCount() - maxDepth;
    }
    --maxDepth;
    for (size_t i = 0; i < board.size; ++i) {
        for (size_t j = 0; j < board.size; ++j) {
            if (board.Get(i, j) == '_' && board.IsInClusters(i, j)) {
                cout << i << ' ' << j << endl;
                board.Set(i, j, 'o');
                int8_t score = MiniMax(board, true, 0);
                board.Set(i, j, '_');
//                cout << board << endl;
                if (score > best_score) {
                    best_score = score;
//                    cout << (long) best_score << endl;
                    move = {i, j};
                    if (best_score == 1)
                        return move;
                }

            }
        }
    }
    return move;

}