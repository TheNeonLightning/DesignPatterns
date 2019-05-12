// В этом header'е лежат классы связанные с реализацие командиров: командир Aeon (AeonCommander), командир Cybran
// (CybranCommander), singleton для хранения командира Aeon (Aeon), singleton для хранения командира Cybran (Cybran)

class Army;

class Commander: public Unit {
public:

    size_t spawning_points = 10;

    virtual SiegeTank* ProduceTank() = 0;

    virtual AssaultBot* ProduceBot() = 0;

    virtual void GetCost(size_t& tank, size_t& bot) = 0;

    Army* army;

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AeonCommander: public Commander {

    friend class Commanders_Fixture;

    friend class GameManager;

protected:

    size_t damage = 5;

    size_t tank_cost = 5; // сколько тратится на постройку танка

    size_t bot_cost = 3; // и, соответственно бота

    AeonUnitFactory factory; // фабрика для создания соответствующих юнитов

    size_t health = 100;



public:

    void attack(Unit* enemy);

    size_t damage_value() {
        return damage;
    }

    bool under_attack(size_t value) {
        health -= value;
        if (health <= 0) {
            destroyed = true;
            return true;
        }
        return false;
    }

    size_t health_value() {
        return health;
    }

    void GetCost(size_t& tank, size_t& bot) {
        tank = tank_cost;
        bot = bot_cost;
    }

    SiegeTank* ProduceTank();

    AssaultBot* ProduceBot();

    ~AeonCommander();

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CybranCommander: public Commander {

    friend class Commanders_Fixture;

    friend class GameManager;

protected:

    size_t damage = 6;

    size_t tank_cost = 4;

    size_t bot_cost = 4;

    CybranUnitFactory factory;

    size_t health = 100;

public:

    void attack(Unit* enemy);

    size_t damage_value() {
        return damage;
    }

    bool under_attack(size_t value) {
        health -= value;
        if (health <= 0) {
            destroyed = true;
            return true;
        }
        return false;
    }

    size_t health_value() {
        return health;
    }

    void GetCost(size_t& tank, size_t& bot) {
        tank = tank_cost;
        bot = bot_cost;
    }

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

    static std::shared_ptr<AeonCommander> commander_unit();
};
std::shared_ptr<AeonCommander> Aeon::commander = nullptr; // static обязательно должен быть проинициализирован

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Cybran {
private:

    static std::shared_ptr<CybranCommander> commander;

public:

    Cybran() = delete;

    ~Cybran() = delete;

    Cybran(const CybranCommander&) = delete;

    Cybran& operator=(const Cybran&) = delete;

    static std::shared_ptr<CybranCommander> commander_unit();
};
std::shared_ptr<CybranCommander> Cybran::commander = nullptr;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////