#include <iostream>
#include <memory>
#include "unit.cpp"

int main() {
    auto aeon_commander = Aeon::commander_unit();
    SiegeTank* tank = aeon_commander->ProduceTank();
    auto aeon_commander2 = Aeon::commander_unit();
    AssaultBot* bot = aeon_commander->ProduceBot();
    auto cybran_commander = Cybran::commander_unit();
    SiegeTank* tank2 = cybran_commander->ProduceTank();
    tank2->attack(bot);
    tank2->attack(tank);
    tank->attack(tank2);
    bot->attack(tank2);
    return 0;
}


