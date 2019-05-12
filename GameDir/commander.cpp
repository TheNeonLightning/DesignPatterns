////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AeonCommander::attack(Unit* enemy) {
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

void CybranCommander::attack(Unit* enemy) {
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