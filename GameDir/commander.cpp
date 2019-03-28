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

std::shared_ptr<AeonCommander> Aeon::commander_unit() {
    if (!commander) {
        commander.reset(new AeonCommander);
    }
    return commander;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<CybranCommander> Cybran::commander_unit() {
    if (!commander) {
        commander.reset(new CybranCommander);
    }
    return commander;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////