#include <iostream>
#include <queue>
#include <algorithm>
#include <memory>
#include <vector>
#include "unit.h"
#include "unit.cpp"
#include "commander.h"
#include "commander.cpp"
#include "composite_and_iterator.h"
#include "composite_and_iterator.cpp"
#include "command.h"
#include "command.cpp"



using std::string;
using std::sort;
using std::queue;
using std::vector;
using std::cin;
using std::cout;
using std::endl;

int main() {
    GameManager game;
    game.Run();
}