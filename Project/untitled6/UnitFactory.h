class SiegeTank;

class AssaultBot;

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

class AeonSiegeTank: public Units {
private:

    size_t health = 12;

    size_t damage = 3;

public:

    void attack(AssaultBot* enemy);

    void attack(SiegeTank* enemy);

    virtual bool under_attack(size_t damage);

    ~AeonSiegeTank();

};

class CybranSiegeTank: public Units {
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
