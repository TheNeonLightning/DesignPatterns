#include <iostream>

using std::cin;
using std::cout;

class AssaultBot;

class SiegeTank {
private:
    size_t damage;
    size_t health;
public:

    void attack(SiegeTank* enemy);

    void attack(AssaultBot* enemy);

    bool under_attack(size_t damage) {
        health = health - damage;
        if (health <= 0) {
            return true;
        }
        return false;
    }

    virtual ~SiegeTank() {};
};

class AssaultBot {
private:
    virtual void veterancy_check() = 0;
    size_t damage;
    size_t health;
    size_t kill_count;
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

    virtual ~AssaultBot() {};
};

class AeonSiegeTank: public SiegeTank {
private:
    size_t health = 12;
    size_t damage = 3;
};

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
};

class CybranSiegeTank: public SiegeTank {
private:
    size_t health = 15;
    size_t damage = 2;
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
};

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

int main() {
    AeonUnitFactory Aeon;
    SiegeTank *tank = Aeon.create_tank();
    CybranUnitFactory Cybran;
    AssaultBot *bot = Cybran.create_bot();
    bot->attack(tank);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SiegeTank::attack(SiegeTank* enemy) {
    enemy->under_attack(damage);
}

void SiegeTank::attack(AssaultBot* enemy) {
    enemy->under_attack(damage);
}
