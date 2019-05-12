using std::cout;
using std::cin;
using std::vector;
using std::endl;
using std::sort;

class GameManager {

    friend class Command;

protected:

    std::shared_ptr<AeonCommander> aeon_commander;

    std::shared_ptr<CybranCommander> cybran_commander;

    Commander* Player;

    Commander* Computer;

public:

    size_t value;

    void Initialization();

    bool PlayerTurn();

    bool ComputerTurn();

    void Run();

};

class Command {
public:
    static bool AttackUnit(Unit *from, Unit *to) {
        from->attack(to);
        if (!to->destroyed) {
            to->attack(from);
        } else if ((to == Aeon::commander_unit().get()) || (to == Cybran::commander_unit().get())) {
            return true;
        }
        return false;
    }
};

class ComCommand: public Command {
public:

    static void Produce(Commander* com, size_t tank, size_t bot, vector<Unit*>& new_squad) {
        size_t value = 0;
        cout << "how many tanks to produce?" << endl;
        cin >> value;
        if (value * tank <= com->spawning_points) {
            for (int i = 0; i < value; ++i) {
                new_squad.push_back(com->ProduceTank());
            }
        }
        cout << "how many bots to produce?" << endl;
        cin >> value;
        if (value * bot <= com->spawning_points) {
            for (int i = 0; i < value; ++i) {
                new_squad.push_back(com->ProduceBot());
            }
        }
        cout << "To finish the production insert 1, to continue insert 0" << endl;
        cin >> value;
        if (value == 1) {
            return;
        }
        Produce(com, tank, bot, new_squad);
    }

    static bool Action(Commander& player, Commander& computer, size_t tank, size_t bot, vector<UnitInArmy>& units_list_comp) {
        size_t value = 0;
        bool flag = false;
        cout << "Choose target for commander" << endl;
        cin >> value;
        if (value == 0) {
            return false;
        } else if (value == 1) {
            flag = AttackUnit(&player, &computer);
        } else {
            flag = AttackUnit(&player, units_list_comp[value - 2].unit);
        }
        if (flag) {
            return true;
        }
        value = player.spawning_points;
        cout << "You have " << value << " spawning points. Would you like to produce new units? ( bot cost - " << bot <<
             " , tank cost - " << tank << ") 0 - no, 1 - yes" << endl;
        cin >> value;
        if (value == 0) {
            return false;
        }
        vector<Unit*> new_squad;
        Produce(&player, tank, bot, new_squad);
        player.army->Add(new_squad);
        return false;
    }
};