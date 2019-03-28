#include <iostream>
#include <memory>
#include "Units.h"
/*
class SiegeTank;

class AssaultBot;


class UnitFactory {
public:
    virtual SiegeTank* create_tank() = 0;

    virtual AssaultBot* create_bot() = 0;

    virtual ~UnitFactory() {};
};

class AeonUnitFactory: public UnitFactory {
public:

    SiegeTank* create_tank();

    AssaultBot* create_bot();

};

class CybranUnitFactory: public UnitFactory {
public:

    SiegeTank* create_tank();

    AssaultBot* create_bot();

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Units {
public:

    virtual void attack(AssaultBot* enemy) = 0;

    virtual void attack(SiegeTank* enemy) = 0;

    virtual bool under_attack(size_t damage) = 0;

    virtual ~Units() {};
};

class AssaultBot {
protected:

    virtual void veterancy_check() = 0;

public:

    virtual void attack(AssaultBot* enemy) = 0;

    virtual void attack(SiegeTank* enemy) = 0;

    virtual bool under_attack(size_t damage) = 0;

    virtual ~AssaultBot() {};
};

class SiegeTank {
public:

    virtual void attack(AssaultBot* enemy) = 0;

    virtual void attack(SiegeTank* enemy) = 0;

    virtual bool under_attack(size_t damage) = 0;

    virtual ~SiegeTank() {};
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AeonAssaultBot: public AssaultBot {
private:

    size_t health = 12;

    size_t damage = 2;

    size_t kill_count = 0;

    virtual void veterancy_check();

public:

    void attack(AssaultBot* enemy);

    void attack(SiegeTank* enemy);

    bool under_attack(size_t damage);

    virtual ~AeonAssaultBot();
};

class CybranAssaultBot: public AssaultBot {
private:

    size_t health = 10;

    size_t damage = 3;

    size_t kill_count = 0;

    virtual void veterancy_check();

public:

    void attack(AssaultBot* enemy);

    void attack(SiegeTank* enemy);

    bool under_attack(size_t damage);

    virtual ~CybranAssaultBot();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AeonSiegeTank: public SiegeTank {
private:

    size_t health = 12;

    size_t damage = 3;

public:

    void attack(AssaultBot* enemy);

    void attack(SiegeTank* enemy);

    virtual bool under_attack(size_t damage);

    ~AeonSiegeTank();

};

class CybranSiegeTank: public SiegeTank {
private:

    size_t health = 15;

    size_t damage = 2;

public:

    void attack(AssaultBot* enemy);

    void attack(SiegeTank* enemy);

    virtual bool under_attack(size_t damage);

    ~CybranSiegeTank();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AeonCommander {
private:

    size_t damage = 5;

    size_t tank_cost = 5;

    size_t bot_cost = 3;

    AeonUnitFactory factory;

    size_t health = 100;

    size_t spawning_points = 10;


public:

    void attack(SiegeTank* enemy);

    void attack(AssaultBot* enemy);

    SiegeTank* ProduceTank();

    AssaultBot* ProduceBot();

    ~AeonCommander();

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CybranCommander {
private:

    size_t damage = 6;

    size_t tank_cost = 4;

    size_t bot_cost = 4;

    CybranUnitFactory factory;

    size_t health = 100;

    size_t spawning_points = 10;

public:

    void attack(SiegeTank* enemy);

    void attack(AssaultBot* enemy);

    SiegeTank* ProduceTank();

    AssaultBot* ProduceBot();

    ~CybranCommander();

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Aeon {
private:

    static std::shared_ptr<AeonCommander> commander;

public:

    Aeon() = delete;

    ~Aeon() = delete;

    Aeon(const AeonCommander&) = delete;

    Aeon& operator=(const Aeon&) = delete;

    static AeonCommander* commander_unit();
};
std::shared_ptr<AeonCommander> Aeon::commander = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Cybran {
private:

    static std::shared_ptr<CybranCommander> commander;

public:

    Cybran() = delete;

    ~Cybran() = delete;

    Cybran(const CybranCommander&) = delete;

    Cybran& operator=(const Cybran&) = delete;

    static CybranCommander* commander_unit();
};
std::shared_ptr<CybranCommander> Cybran::commander = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
int main() {
/*
    auto aeon_commander = Aeon::commander_unit();
    SiegeTank* tank = aeon_commander->ProduceTank();
    auto aeon_commander2 = Aeon::commander_unit();
    AssaultBot* bot = aeon_commander->ProduceBot();
    auto cybran_commander = Cybran::commander_unit();
    SiegeTank* tank2 = cybran_commander->ProduceTank();
    tank2->attack(bot);
    tank2->attack(tank);
    tank->attack(tank2);
    bot->attack(tank2);*/
    return 0;
}
/*
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
*/
