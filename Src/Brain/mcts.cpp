/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** mcts
*/

#include <iostream>
#include "mcts.hpp"

Node *MCTS::select(Node *node)
{
    // while (!node->isTerminal() && node->isFullyExpanded())
    // {
    //     node = node->findBestChild();
    // }
    return node;
}

Node *MCTS::expand(Node *node)
{
    // if (node->isFullyExpanded())
    // {
    //     return node;
    // }
    // return node->expand();
    return node;
}

int MCTS::simulate(Node *node)
{
    gomoku_t simulatedState = node->getGameState();
    bool isCurrentPlayer = simulatedState.my_turn;
    int depth = 0;

    if (simulatedState.state != GAME_STATE::PLAY)
    {
        return -1;
    }
    std::pair<int, int> move;
    std::vector<std::pair<int, int>> availableMovesMe = _gameLogic.getAvailableAdjacentMoves(simulatedState, TILE_STATE::ME);
    while (simulatedState.state == GAME_STATE::PLAY)
    {
        if (availableMovesMe.empty())
        {
            availableMovesMe = _gameLogic.getAvailableMoves(simulatedState);
        }

        move = availableMovesMe[rand() % availableMovesMe.size()];

        simulatedState.map[move.first][move.second] = isCurrentPlayer ? TILE_STATE::ME : TILE_STATE::PLAYER2;

        if (isCurrentPlayer && _gameLogic.checkWin(simulatedState))
        {
            simulatedState.state = GAME_STATE::WIN;
            return depth;
        }

        if (_gameLogic.checkDraw(simulatedState))
        {
            simulatedState.state = GAME_STATE::LOSE;
            return -1;
        }

        isCurrentPlayer = !isCurrentPlayer;
        availableMovesMe = _gameLogic.getAvailableAdjacentMoves(simulatedState, TILE_STATE::ME);

        depth++;
    }
    return -1;
}

void MCTS::backPropagate(Node *node, int depth)
{
    while (node != nullptr)
    {
        if (depth >= 0)
        {
            node->updateValue(1.0);
            node->addWinningDepth(depth);
        }

        node = node->getParent();
    }
}

Node *MCTS::getBestChildInfo(gomoku_t &game)
{
    _root = std::make_unique<Node>(game, nullptr, game.me);
    std::vector<std::pair<int, int>> testMoves = _gameLogic.getAvailableAdjacentMoves(game, TILE_STATE::ME);

    if (testMoves.empty())
    {
        testMoves = _gameLogic.getAvailableMoves(game);
        std::pair<int, int> move = testMoves[rand() % testMoves.size()];
        coord_t moveCoord = {move.first, move.second};
        auto node = std::make_unique<Node>(game, nullptr, moveCoord);
        node->setFirstMove(move);
        return node.get();
    }

    for (auto &move : testMoves)
    {
        if (game.me.x == move.first && game.me.y == move.second)
        {
            continue;
        }
        Node *child = _root->expand(move);
        child->setFirstMove(move);
        int depth = simulate(child);
        backPropagate(child, depth);
    }
    
    Node *bestChild = _root->findBestChild();

    return bestChild;
}
