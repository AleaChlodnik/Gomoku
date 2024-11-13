/*
** EPITECH PROJECT, 2024
** Gomoku
** File description:
** game_logic
*/

#include "game_logic.hpp"

/////////////////////////////////////////////////////////////////
std::ostream &operator<<(std::ostream &os, const TILE_STATE &entry)
{
  switch (entry) {
  case TILE_STATE::EMPTY:
    os << "X";
    break;
  case TILE_STATE::ME:
    os << "1";
    break;
  case TILE_STATE::PLAYER2:
    os << "2";
    break;
  default:
    os << "UNDEFINED";
    break;
  }
  return os;
}
/////////////////////////////////////////////////////////////////

std::vector<std::pair<int, int>> GameLogic::getAvailableMoves(const gomoku_t &gameState) const
{
    int i = 0;
    int j = 0;
    std::vector<std::pair<int, int>> moves;

    for (i = 0; i < gameState.size.x; ++i)
    {
        for (j = 0; j < gameState.size.y; ++j)
        {
            if (gameState.map[i][j] == TILE_STATE::EMPTY)
            {
                moves.push_back({i, j});
            }
        }
    }

    return moves;
}

std::vector<std::pair<int, int>> GameLogic::tempGetAvailableAdjacentMoves(const gomoku_t &gameState, TILE_STATE tileState) const ///////////////////
{

    std::vector<std::pair<int, int>> adjacentMoves;
    std::vector<std::pair<int, int>> tiles;
    std::set<std::pair<int, int>> uniqueAdjacentMoves;

    for (int i = 0; i < gameState.map.size(); i++)
    {
        for (int j = 0; j < gameState.map[i].size(); j++)
        {
            std::cout << " " << i << " " << j << " " << gameState.map[i][j] << " "; ///////////////////////
            // std::cout << gameState.map[i][j] <<  " "; ///////////////////////
            if (gameState.map[i][j] == tileState)
            {
                // std::cout << " " << i << " " << j << "-> " << gameState.map[i][j] <<  std::endl; ///////////////////////
                tiles.push_back({i, j});
            }
        }
        std::cout << std::endl; ///////////////////////
    }
    if (tiles.empty())
    {
        return adjacentMoves;
    }

    for (const auto &tile : tiles)
    {
        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                if (x == 0 && y == 0)
                    continue;
                int newX = tile.first + x;
                int newY = tile.second + y;

                if (newX >= 0 && newX < gameState.map.size() &&
                    newY >= 0 && newY < gameState.map[0].size() &&
                    gameState.map[newX][newY] == TILE_STATE::EMPTY)
                {
                    uniqueAdjacentMoves.insert({newX, newY});
                }
            }
        }
    }

    adjacentMoves.assign(uniqueAdjacentMoves.begin(), uniqueAdjacentMoves.end());

    return adjacentMoves;
}

std::vector<std::pair<int, int>> GameLogic::getAvailableAdjacentMoves(const gomoku_t &gameState, TILE_STATE tileState) const
{

    std::vector<std::pair<int, int>> adjacentMoves;
    std::vector<std::pair<int, int>> tiles;
    std::set<std::pair<int, int>> uniqueAdjacentMoves;

    for (int i = 0; i < gameState.map.size(); i++)
    {
        for (int j = 0; j < gameState.map[i].size(); j++)
        {
            if (gameState.map[i][j] == tileState)
            {
                tiles.push_back({i, j});
            }
        }
    }
    if (tiles.empty())
    {
        return adjacentMoves;
    }

    for (const auto &tile : tiles)
    {
        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                // if (x == 0 && y == 0)
                //     continue;
                int newX = tile.first + x;
                int newY = tile.second + y;

                if (newX >= 0 && newX < gameState.map.size() &&
                    newY >= 0 && newY < gameState.map[0].size() &&
                    gameState.map[newX][newY] == TILE_STATE::EMPTY)
                {
                    uniqueAdjacentMoves.insert({newX, newY});
                }
            }
        }
    }

    adjacentMoves.assign(uniqueAdjacentMoves.begin(), uniqueAdjacentMoves.end());

    return adjacentMoves;
}

// Check for a sequence of 5
bool GameLogic::checkWin(const gomoku_t &gameState) const
{
    int i = 0;
    int j = 0;

    // Horizontal check
    for (int i = 0; i < gameState.size.x; ++i)
    {
        for (int j = 0; j <= gameState.size.y - 5; ++j)
        {
            if (gameState.map[i][j] == TILE_STATE::ME &&
                gameState.map[i][j + 1] == TILE_STATE::ME &&
                gameState.map[i][j + 2] == TILE_STATE::ME &&
                gameState.map[i][j + 3] == TILE_STATE::ME &&
                gameState.map[i][j + 4] == TILE_STATE::ME)
            {
                return true;
            }
        }
    }

    // Vertical check
    for (int i = 0; i <= gameState.size.x - 5; ++i)
    {
        for (int j = 0; j < gameState.size.y; ++j)
        {
            if (gameState.map[i][j] == TILE_STATE::ME &&
                gameState.map[i + 1][j] == TILE_STATE::ME &&
                gameState.map[i + 2][j] == TILE_STATE::ME &&
                gameState.map[i + 3][j] == TILE_STATE::ME &&
                gameState.map[i + 4][j] == TILE_STATE::ME)
            {
                return true;
            }
        }
    }

    // Diagonal (bottom-left to top-right) check
    for (int i = 0; i <= gameState.size.x - 5; ++i)
    {
        for (int j = 0; j <= gameState.size.y - 5; ++j)
        {
            if (gameState.map[i][j] == TILE_STATE::ME &&
                gameState.map[i + 1][j + 1] == TILE_STATE::ME &&
                gameState.map[i + 2][j + 2] == TILE_STATE::ME &&
                gameState.map[i + 3][j + 3] == TILE_STATE::ME &&
                gameState.map[i + 4][j + 4] == TILE_STATE::ME)
            {
                return true;
            }
        }
    }

    // Diagonal (top-left to bottom-right) check
    for (int i = 0; i <= gameState.size.x - 5; ++i)
    { // Start from i = 0, not i = 4
        for (int j = 0; j <= gameState.size.y - 5; ++j)
        { // Check columns as well
            if (gameState.map[i][j] == TILE_STATE::ME &&
                gameState.map[i + 1][j + 1] == TILE_STATE::ME &&
                gameState.map[i + 2][j + 2] == TILE_STATE::ME &&
                gameState.map[i + 3][j + 3] == TILE_STATE::ME &&
                gameState.map[i + 4][j + 4] == TILE_STATE::ME)
            {
                return true;
            }
        }
    }

    return false;
}

// Check if current game state is at a draw
bool GameLogic::checkDraw(const gomoku_t &gameState) const
{
    int i = 0;
    int j = 0;

    for (i = 0; i < gameState.size.x; ++i)
    {
        for (j = 0; j < gameState.size.y; ++j)
        {
            if (gameState.map[i][j] == TILE_STATE::EMPTY)
            {
                return false;
            }
        }
    }

    return true;
}
