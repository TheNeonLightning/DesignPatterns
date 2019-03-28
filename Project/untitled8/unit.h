// В этом header'е лежат фабричные классы для реализации AbstractFactory, а также классы юнитов


class SiegeTank;

class AssaultBot;

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
class AssaultBot { // абстрактный интерфейс bot
protected:

    virtual void veterancy_check() = 0; // проверка количесвта убийств (вызывается в ходе каждой атаки, при достижении
    // определённого значения восстанавливает часть здоровья [например каждое 4 убийство])

public:

    virtual void attack(AssaultBot* enemy) = 0;

    virtual void attack(SiegeTank* enemy) = 0;

    virtual bool under_attack(size_t damage) = 0; // вызывается в случае, если данный юнит атакован, возвращает true,
    // если юнит был уничтожен

    virtual ~AssaultBot() {};

};

class SiegeTank { // абстрактный интерфейс tank
public:

    virtual void attack(AssaultBot* enemy) = 0;

    virtual void attack(SiegeTank* enemy) = 0;

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

    void attack(AssaultBot* enemy);

    void attack(SiegeTank* enemy);

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

    void attack(AssaultBot* enemy);

    void attack(SiegeTank* enemy);

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

    void attack(AssaultBot* enemy);

    void attack(SiegeTank* enemy);

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

    void attack(AssaultBot* enemy);

    void attack(SiegeTank* enemy);

    virtual bool under_attack(size_t damage);

    ~CybranSiegeTank();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


