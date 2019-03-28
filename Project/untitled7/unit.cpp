#include "unit.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AeonCommander::attack(SiegeTank* enemy) {
    enemy->under_attack(damage);
}

void AeonCommander::attack(AssaultBot* enemy) {
    enemy->under_attack(damage);
}

SiegeTank* AeonCommander::ProduceTank() {
    spawning_points -= tank_cost;
    return factory.create_tank();
}

AssaultBot* AeonCommander::ProduceBot() {
    spawning_points -= bot_cost;
    return factory.create_bot();
}

AeonCommander::~AeonCommander() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CybranCommander::attack(SiegeTank* enemy) {
    enemy->under_attack(damage);
}

void CybranCommander::attack(AssaultBot* enemy) {
    enemy->under_attack(damage);
}

SiegeTank* CybranCommander::ProduceTank() {
    spawning_points -= tank_cost;
    return factory.create_tank();
}

AssaultBot* CybranCommander::ProduceBot() {
    spawning_points -= bot_cost;
    return factory.create_bot();
}

CybranCommander::~CybranCommander() {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

AeonCommander* Aeon::commander_unit() {
    if (!commander) {
        commander.reset(new AeonCommander);
    }
    return commander.get();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CybranCommander* Cybran::commander_unit() {
    if (!commander) {
        commander.reset(new CybranCommander);
    }
    return commander.get();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

void AeonAssaultBot::veterancy_check() {
    if (kill_count % 4 == 0) {
        health += 2;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AeonAssaultBot::attack(AssaultBot* enemy) {
    bool flag = enemy->under_attack(damage);
    if (flag) {
        kill_count += 1;
        veterancy_check();
    }
}

void AeonAssaultBot::attack(SiegeTank* enemy) {
    bool flag = enemy->under_attack(damage);
    if (flag) {
        kill_count += 1;
        veterancy_check();
    }
}

bool AeonAssaultBot::under_attack(size_t damage) {
    health = health - damage;
    if (health <= 0) {
        return true;
    }
    return false;
}

AeonAssaultBot::~AeonAssaultBot() {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CybranAssaultBot::veterancy_check() {
    if (kill_count % 6 == 0) {
        health += 3;
    }
}

