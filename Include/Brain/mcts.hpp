/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** mcts
*/

#pragma once

#include <random>
#include <chrono>
#include "node.hpp"
#include "game_logic.hpp"

class MCTS {
    public:
        MCTS(const gomoku_t &game) : _root(nullptr), _timeLimit(game.global_info.timeout_turn.count() / 1000.0), _gameLogic() {}
        ~MCTS() {} // ?

        Node *getBestChildInfo(gomoku_t &game);

    private:
        double _timeLimit;
        std::unique_ptr<Node> _root;
        GameLogic _gameLogic;

        int simulate(Node *node);
        void backPropagate(Node *node, int depth);
};
