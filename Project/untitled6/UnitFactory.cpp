#include "Units.h"
SiegeTank* AeonUnitFactory::create_tank() {
    return new AeonSiegeTank();
}

AssaultBot* AeonUnitFactory::create_bot() {
    return new AeonAssaultBot();
}

SiegeTank* CybranUnitFactory::create_tank() {
    return new CybranSiegeTank();
}

AssaultBot* CybranUnitFactory::create_bot() {
    return new CybranAssaultBot();
}


