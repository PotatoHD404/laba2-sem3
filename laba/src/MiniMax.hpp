//
// Created by PotatoHD on 08.12.2021.
//

#pragma  once

#include <cstdint>
#include <cwchar>
#include <limits>
#include "Pairs.hpp"

size_t maxDepth = 3;

long
MiniMax(Board &board, bool isEnemyMove, // NOLINT(performance-unnecessary-value-param,misc-no-recursion)
        size_t depth) {
    if (depth >= maxDepth) {
//        cout << "Exceeded" << endl;
        return 0;
    }
    long bestScore = isEnemyMove ? std::numeric_limits<long>::max() : std::numeric_limits<long>::min();
    char gameState = board.GetGameState();
    if (gameState != 0) {
        return (long) ((gameState == 'o') ?
                       std::numeric_limits<long>::max() : gameState == 'x' ?
                                                          std::numeric_limits<long>::min() : 0);
    }
    for (size_t i = 0; i < board.size; ++i) {
        for (size_t j = 0; j < board.size; ++j) {
            if (board.Get(i, j) == '_' && board.IsInClusters(i, j)) {
//                cout << i << ' ' << j << endl;
                board.Set(i, j, isEnemyMove ? 'x' : 'o');
                long x = MiniMax(board, !isEnemyMove, depth + 1);
                if ((x > bestScore && !isEnemyMove) || (x < bestScore && isEnemyMove)) bestScore = x;

//                cout << (long) bestScore << endl;
                board.UndoClusters();
                board.Set(i, j, '_');
                if ((!isEnemyMove && bestScore == std::numeric_limits<long>::max()) ||
                    (bestScore == std::numeric_limits<long>::min() && isEnemyMove))
                    return bestScore;
            }
        }
    }
    return bestScore;
}

Pair<size_t> PredictMove(Board &board) {

    Pair<size_t> move{std::numeric_limits<size_t>::max(), std::numeric_limits<size_t>::max()};
    long best_score = std::numeric_limits<long>::min();
    size_t movesCount = 1;
    size_t boardSize = board.GetSize();
    for (maxDepth = 0; movesCount < 1000000; ++maxDepth) {
        if (boardSize - board.GetCount() - maxDepth == 0)
            break;
        movesCount *= boardSize - board.GetCount() - maxDepth;
    }
    --maxDepth;
    for (size_t i = 0; i < board.size; ++i) {
        for (size_t j = 0; j < board.size; ++j) {
            if (board.Get(i, j) == '_' && board.IsInClusters(i, j)) {
//                cout << i << ' ' << j << endl;
                board.Set(i, j, 'o');
                long score = MiniMax(board, true, 0);
                board.UndoClusters();
                board.Set(i, j, '_');
//                cout << board << endl;
                if (score > best_score) {
                    cout << score << endl;

                    best_score = score;
//                    cout << (long) best_score << endl;
                    move = {i, j};
                    if (best_score == std::numeric_limits<long>::max())
                        return move;
                }

            }
        }
    }
    cout << "not found" << endl;
    return move;

}