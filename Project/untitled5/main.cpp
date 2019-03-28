#include <iostream>
#include <bits/shared_ptr.h>

using std::cin;
using std::cout;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AssaultBot;

class SiegeTank;

class SiegeTank {
public:

    virtual void attack(SiegeTank* enemy) = 0;

    virtual void attack(AssaultBot* enemy) = 0;

    virtual bool under_attack(size_t damage) = 0;

    virtual ~SiegeTank() {};
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AeonSiegeTank: public SiegeTank {
private:

    size_t health = 12;

    size_t damage = 3;

public:

    void attack(SiegeTank* enemy) {
        enemy->under_attack(damage);
    }

    void attack(AssaultBot* enemy) {
        enemy->under_attack(damage);
    }

    virtual bool under_attack(size_t damage) {
        health -= damage;
        if (health <= 0) {
            return true;
        }
        return false;
    }

    ~AeonSiegeTank() {};

};

class CybranSiegeTank: public SiegeTank {
private:

    size_t health = 15;

    size_t damage = 2;

public:

    void attack(SiegeTank* enemy) {
        enemy->under_attack(damage);
    }

    void attack(AssaultBot* enemy) {
        enemy->under_attack(damage);
    }

    virtual bool under_attack(size_t damage) {
        health -= damage;
        if (health <= 0) {
            return true;
        }
        return false;
    }

    ~CybranSiegeTank() {};
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class AeonAssaultBot: public AssaultBot {
private:

    size_t health = 12;

    size_t damage = 2;

    size_t kill_count = 0;

    virtual void veterancy_check() {
        if (kill_count % 4 == 0) {
            health += 2;
        }
    }

public:

    void attack(AssaultBot* enemy) {
        bool flag = enemy->under_attack(damage);
        if (flag) {
            kill_count += 1;
            veterancy_check();
        }
    }

    void attack(SiegeTank* enemy) {
        bool flag = enemy->under_attack(damage);
        if (flag) {
            kill_count += 1;
            veterancy_check();
        }
    }

    bool under_attack(size_t damage) {
        health = health - damage;
        if (health <= 0) {
            return true;
        }
        return false;
    }

    virtual ~AeonAssaultBot() {};
};

class CybranAssaultBot: public AssaultBot {
private:

    size_t health = 10;

    size_t damage = 3;

    size_t kill_count = 0;

    virtual void veterancy_check() {
        if (kill_count % 6 == 0) {
            health += 3;
        }
    }

public:

    void attack(AssaultBot* enemy) {
        bool flag = enemy->under_attack(damage);
        if (flag) {
            kill_count += 1;
            veterancy_check();
        }
    }

    void attack(SiegeTank* enemy) {
        bool flag = enemy->under_attack(damage);
        if (flag) {
            kill_count += 1;
            veterancy_check();
        }
    }

    bool under_attack(size_t damage) {
        health = health - damage;
        if (health <= 0) {
            return true;
        }
        return false;
    }

    virtual ~CybranAssaultBot() {};
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
    SiegeTank* create_tank() {
        return new AeonSiegeTank();
    }
    AssaultBot* create_bot() {
        return new AeonAssaultBot();
    }
};

class CybranUnitFactory: public UnitFactory {
public:
    SiegeTank* create_tank() {
        return new CybranSiegeTank();
    }
    AssaultBot* create_bot() {
        return new CybranAssaultBot();
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Commander {
public:

    virtual void attack(SiegeTank* enemy) = 0;

    virtual void attack(AssaultBot* enemy) = 0;

    virtual SiegeTank* ProduceTank() = 0;

    virtual AssaultBot* ProduceBot() = 0;

    virtual Commander* clone() const = 0;

    virtual ~Commander() {};

protected:

    size_t health = 100;

    size_t spawning_points = 10;

};

class AeonCommander: public Commander {
private:

    size_t damage = 5;

    size_t tank_cost = 5;

    size_t bot_cost = 3;

    AeonUnitFactory factory;

public:

    void attack(SiegeTank* enemy) {
        enemy->under_attack(damage);
    }

    void attack(AssaultBot* enemy) {
        enemy->under_attack(damage);
    }
    SiegeTank* ProduceTank() {
        spawning_points -= tank_cost;
        return factory.create_tank();
    }

    AssaultBot* ProduceBot() {
        spawning_points -= bot_cost;
        return factory.create_bot();
    }


    AeonCommander* clone() const {
        return new AeonCommander(*this);
    }

    ~AeonCommander() {}

}aeon;

class CybranCommander: public Commander {
private:

    size_t damage = 6;

    size_t tank_cost = 4;

    size_t bot_cost = 4;

    CybranUnitFactory factory;

public:

    void attack(SiegeTank* enemy) {
        enemy->under_attack(damage);
    }

    void attack(AssaultBot* enemy) {
        enemy->under_attack(damage);
    }
    SiegeTank* ProduceTank() {
        spawning_points -= tank_cost;
        return factory.create_tank();
    }

    AssaultBot* ProduceBot() {
        spawning_points -= bot_cost;
        return factory.create_bot();
    }


    CybranCommander* clone() const {
        return new CybranCommander(*this);
    }

    ~CybranCommander() {}

}cybran;

class Aeon {
private:
    static AeonCommander* commander;

    bool flag = true;
public:
    Aeon() = delete;

    ~Aeon() = delete;

    Aeon(const AeonCommander&) = delete;

    Aeon &operator=(const Aeon&) = delete;

    AeonCommander* commander_unit() {
        if (flag) {
            commander = new AeonCommander;

            flag = false;
        }
        return commander;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {

    CybranCommander* seraphim = cybran.clone();

    Singleton<AeonCommander> aeon_ = Singleton<AeonCommander>.commander_unit();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

