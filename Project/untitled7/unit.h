class AssaultBot;
class SiegeTank;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

class AssaultBot: public Units {
protected:

    virtual void veterancy_check() = 0;

public:

    virtual void attack(AssaultBot* enemy) = 0;

    virtual void attack(SiegeTank* enemy) = 0;

    virtual bool under_attack(size_t damage) = 0;

    virtual ~AssaultBot() {};
};

class SiegeTank: public Units {
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