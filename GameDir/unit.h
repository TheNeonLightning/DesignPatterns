// В этом header'е лежат фабричные классы для реализации AbstractFactory, а также классы юнитов
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////New1////////////////////////////////////////////////////////////

class SiegeTank;

class AssaultBot;

class Unit {

public:

    bool destroyed = false;

    virtual size_t health_value() {
        return 0;
    }

    virtual size_t damage_value() {
        return 0;
    }

    virtual void attack(Unit* enemy) {

    }

    virtual bool under_attack(size_t damage) {
        return false;
    }

};

/////////////////////////////////////////////AbstractFactory////////////////////////////////////////////////////////////

class UnitFactory { // абстрактная фабрика
public:
    virtual SiegeTank* create_tank() = 0;

    virtual AssaultBot* create_bot() = 0;

    virtual ~UnitFactory() {};
};

class AeonUnitFactory: public UnitFactory {
public:

    SiegeTank* create_tank();

    AssaultBot* create_bot();

    ~AeonUnitFactory() {};

};

class CybranUnitFactory: public UnitFactory {
public:

    SiegeTank* create_tank();

    AssaultBot* create_bot();

    ~CybranUnitFactory() {};

};

//////////////////////////////////////UnitInterface/////////////////////////////////////////////////////////////////////
class AssaultBot: public Unit { // абстрактный интерфейс bot
protected:

    virtual void veterancy_check() = 0; // проверка количесвта убийств (вызывается в ходе каждой атаки, при достижении
    // определённого значения восстанавливает часть здоровья [например каждое 4 убийство])

public:

    virtual size_t health_value() = 0;

    virtual size_t damage_value() = 0;

    virtual void attack(Unit* enemy) = 0;

    virtual bool under_attack(size_t damage) = 0; // вызывается в случае, если данный юнит атакован, возвращает true,
    // если юнит был уничтожен

    virtual ~AssaultBot() {};

};

class SiegeTank: public Unit { // абстрактный интерфейс tank
public:

    virtual size_t health_value() = 0;

    virtual size_t damage_value() = 0;

    virtual void attack(Unit* enemy) = 0;

    virtual bool under_attack(size_t damage) = 0;

    virtual ~SiegeTank() {};
};

///////////////////////////////////////////AssaultBotInterfaces/////////////////////////////////////////////////////////

class AeonAssaultBot: public AssaultBot { // Aeon bot

    friend class Units_and_Factories_Fixture;

    friend class Commanders_Fixture;

protected:

    size_t health = 12;

    size_t damage = 2;

    size_t kill_count = 0;

    virtual void veterancy_check();

public:

    size_t health_value() {
        return health;
    }

    size_t damage_value() {
        return damage;
    }

    void attack(Unit* enemy);

    bool under_attack(size_t damage);

    virtual ~AeonAssaultBot();
};

class CybranAssaultBot: public AssaultBot {

    friend class Units_and_Factories_Fixture;

    friend class Commanders_Fixture;

protected:

    size_t health = 10;

    size_t damage = 3;

    size_t kill_count = 0;

    virtual void veterancy_check();

public:

    size_t health_value() {
        return health;
    }

    size_t damage_value() {
        return damage;
    }

    void attack(Unit* enemy);

    bool under_attack(size_t damage);

    virtual ~CybranAssaultBot();
};

///////////////////////////////////////////SiegeTankInterfaces//////////////////////////////////////////////////////////

class AeonSiegeTank: public SiegeTank {

    friend class Units_and_Factories_Fixture;

    friend class Commanders_Fixture;

protected:

    size_t health = 12;

    size_t damage = 3;

public:

    size_t health_value() {
        return health;
    }

    size_t damage_value() {
        return damage;
    }

    void attack(Unit* enemy);

    virtual bool under_attack(size_t damage);

    ~AeonSiegeTank();

};

class CybranSiegeTank: public SiegeTank {

    friend class Units_and_Factories_Fixture;

    friend class Commanders_Fixture;

protected:

    size_t health = 15;

    size_t damage = 2;

public:

    size_t health_value() {
        return health;
    }

    size_t damage_value() {
        return damage;
    }

    void attack(Unit* enemy);

    virtual bool under_attack(size_t damage);

    ~CybranSiegeTank();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


