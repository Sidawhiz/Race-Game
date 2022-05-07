#pragma once
#include <cstdint>

#include "Networking.h"
#include "Vector2D.h"

enum class GameMsg : uint32_t
{
    Client_InitMap,
    Client_AssignID,
    Game_UserInput
};

enum class UserInput
{
    DUMMY,

    W,
    A,
    S,
    D,

    UP,
    LEFT,
    RIGHT,
    DOWN,

    W_UP,
    A_UP,
    S_UP,
    D_UP,

    UP_UP,
    LEFT_UP,
    RIGHT_UP,
    DOWN_UP
};

struct initMessage
{
    int playerID;
    time_t randomSeed;
};