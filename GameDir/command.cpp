using std::cout;
using std::cin;
using std::vector;
using std::endl;
using std::sort;

void GameManager::Initialization() {
    aeon_commander = Aeon::commander_unit();
    cybran_commander = Cybran::commander_unit();
    Army aeon_army;
    aeon_commander->army = &aeon_army;
    Army cybran_army;
    cybran_commander->army = &cybran_army;
    cout << "Choose the side you want to play for" << endl << "Aeon - 0, Cybran - 1" << endl;
    cin >> value;
    if (value == 0) {
        Player = Aeon::commander_unit().get();
        Computer = Cybran::commander_unit().get();
    } else {
        Player = Cybran::commander_unit().get();
        Computer = Aeon::commander_unit().get();
    }
}

bool GameManager::PlayerTurn() {
    bool flag = false;
    vector<UnitInArmy> units_list_pl, units_list_comp;
    Army pl = *Player->army;
    Army comp = *Computer->army;
    Iterator::get_units_stat(pl, units_list_pl);
    Iterator::get_units_stat(comp , units_list_comp);
    for (int i = 0; i < units_list_pl.size(); ++i) {
        cout << "Choose target for unit" << i << endl;
        cin >> value;
        if (value == 0) {
            return false;
        } else if (value == 1) {
            flag = Command::AttackUnit(units_list_pl[i].unit, Computer);
        } else {
            flag = Command::AttackUnit(units_list_pl[i].unit, units_list_comp[value - 2].unit);
        }
        if (flag) {
            return true;
        }
    }
    size_t tank = 0, bot = 0;
    Player->GetCost(tank, bot);
    flag = ComCommand::Action(*Player, *Computer, tank, bot, units_list_comp);
    return flag;
}

bool GameManager::ComputerTurn() {
    bool flag = false;
    vector<UnitInArmy> units_list_pl;
    vector<UnitInArmy> units_list_comp;
    vector<size_t> health, damage;
    Army pl = *Player->army;
    Army comp = *Computer->army;
    Iterator::get_health_stat(pl, health);
    Iterator::get_damage_stat(comp, damage);
    Iterator::get_units_stat(pl, units_list_pl);
    Iterator::get_units_stat(comp, units_list_comp);
    sort(health.begin(), health.end());
    sort(damage.begin(), damage.end(), std::greater<>());
    int index = 0;
    for (int i = 0; i < units_list_comp.size(); ++i) {
        if (index > units_list_pl.size()) {
            flag = Command::AttackUnit(units_list_comp[i].unit, Player);
            if (flag) {
                return true;
            }
        }
        flag = Command::AttackUnit(units_list_comp[i].unit, units_list_pl[index].unit);
        if (flag) {
            return true;
        }
        health[index] -= damage[i];
        if (health[index] < 0) {
            index += 1;
        }
    }
    size_t tank = 0, bot = 0;
    Computer->GetCost(tank, bot);
    vector<Unit *> new_squad;
    while (Computer->spawning_points >= tank + bot) {
        new_squad.push_back(Computer->ProduceTank());
        new_squad.push_back(Computer->ProduceBot());
    }
    Computer->army->Add(new_squad);
    return false;
}

void GameManager::Run() {
    bool flag = false;
    Initialization();
    int round = 0;
    while (!flag) {
        if (round % 2 == 0) {
            flag = PlayerTurn();
        } else {
            flag = ComputerTurn();
        }
        round += 1;
    }
    if (round % 2 == 0) {
        cout << "Computer won!";
    } else {
        cout << "Player won!";
    }
}