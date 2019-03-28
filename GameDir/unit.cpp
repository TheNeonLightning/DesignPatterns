//////////////////////////////////////////Factories/////////////////////////////////////////////////////////////////////

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

//////////////////////////////////////////Units/////////////////////////////////////////////////////////////////////////

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

void CybranAssaultBot::attack(AssaultBot* enemy) {
    bool flag = enemy->under_attack(damage);
    if (flag) {
        kill_count += 1;
        veterancy_check();
    }
}

void CybranAssaultBot::attack(SiegeTank* enemy) {
    bool flag = enemy->under_attack(damage);
    if (flag) {
        kill_count += 1;
        veterancy_check();
    }
}

bool CybranAssaultBot::under_attack(size_t damage) {
    health = health - damage;
    if (health <= 0) {
        return true;
    }
    return false;
}

CybranAssaultBot::~CybranAssaultBot() {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void AeonSiegeTank::attack(SiegeTank* enemy) {
    enemy->under_attack(damage);
}

void AeonSiegeTank::attack(AssaultBot* enemy) {
    enemy->under_attack(damage);
}

bool AeonSiegeTank::under_attack(size_t damage) {
    health -= damage;
    if (health <= 0) {
        return true;
    }
    return false;
}

AeonSiegeTank::~AeonSiegeTank() {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CybranSiegeTank::attack(SiegeTank* enemy) {
    enemy->under_attack(damage);
}

void CybranSiegeTank::attack(AssaultBot* enemy) {
    enemy->under_attack(damage);
}

bool CybranSiegeTank::under_attack(size_t damage) {
    health -= damage;
    if (health <= 0) {
        return true;
    }
    return false;
}

CybranSiegeTank::~CybranSiegeTank() {};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////