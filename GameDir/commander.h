// В этом header'е лежат классы связанные с реализацие командиров: командир Aeon (AeonCommander), командир Cybran
// (CybranCommander), singleton для хранения командира Aeon (Aeon), singleton для хранения командира Cybran (Cybran)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AeonCommander {

    friend class Commanders_Fixture;

protected:

    size_t damage = 5;

    size_t tank_cost = 5; // сколько тратится на постройку танка

    size_t bot_cost = 3; // и, соответственно бота

    AeonUnitFactory factory; // фабрика для создания соответствующих юнитов

    size_t health = 100;

    size_t spawning_points = 10; // на создание юнитов


public:

    void attack(SiegeTank* enemy);

    void attack(AssaultBot* enemy);

    SiegeTank* ProduceTank();

    AssaultBot* ProduceBot();

    ~AeonCommander();

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CybranCommander {

    friend class Commanders_Fixture;

protected:

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