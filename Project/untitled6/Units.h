#pragma once
#include "UnitFactory.h"

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

    void attack(Units* enemy);

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

