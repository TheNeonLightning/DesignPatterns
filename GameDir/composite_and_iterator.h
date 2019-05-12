using std::vector;
using std::queue;

class UnitInArmy;

class Army {

    friend class Iterator;

public:

    bool leaf;

    vector<UnitInArmy> squads;

    vector<UnitInArmy> created;

    explicit Army();

    void Add(vector<Unit*>& squad);
};

class UnitInArmy: public Army {
public:

    Unit* unit;

    explicit UnitInArmy(Unit incoming_unit);

    ~UnitInArmy() = default;

    bool operator==(const UnitInArmy& compared);

    size_t health_value();

    size_t damage_value();

};

class Iterator {
public:

    static void get_health_stat(Army& army, vector<size_t>& health) {
        health.clear();
        for (int i = 0; i < army.squads.size(); ++i) {
            if (army.squads[i].leaf) {
                health.push_back(army.squads[i].health_value());
            }
        }
    }

    static void get_units_stat(Army& army, vector<UnitInArmy>& units_list) {
        units_list.clear();
        for (int i = 0; i < army.squads.size(); ++i) {
            if (army.squads[i].leaf) {
                units_list.push_back(dynamic_cast<UnitInArmy&>(army.squads[i]));
            }
        }
    }

    static void get_damage_stat(Army& army, vector<size_t>& damage) {
        damage.clear();
        for (int i = 0; i < army.squads.size(); ++i) {
            if (army.squads[i].leaf) {
                damage.push_back(army.squads[i].damage_value());
            }
        }
    }

    static void get_health_stat_second(Army& army, vector<size_t> &health) {
        health.clear();
        queue<Army> buffer;
        buffer.push(army);
        while (!buffer.empty()) {
            Army current = buffer.front();
            buffer.pop();
            for (int i = 0; i < current.squads.size(); ++i) {
                if (current.squads[i].leaf) {
                    health.push_back(current.squads[i].health_value());
                } else {
                    buffer.push(current.squads[i]);
                }
            }
        }
    }

    static void get_units_stat_second(Army& army, vector<UnitInArmy>& units_list) {
        units_list.clear();
        queue<Army> buffer;
        buffer.push(army);
        while (!buffer.empty()) {
            Army current = buffer.front();
            buffer.pop();
            for (int i = 0; i < current.squads.size(); ++i) {
                if (current.squads[i].leaf) {
                    units_list.push_back(dynamic_cast<UnitInArmy&>(current.squads[i]));
                } else {
                    buffer.push(current.squads[i]);
                }
            }
        }
    }

    static void get_damage_stat_second(Army& army, vector<size_t>& damage) {
        damage.clear();
        queue<Army> buffer;
        buffer.push(army);
        while (!buffer.empty()) {
            Army current = buffer.front();
            buffer.pop();
            for (int i = 0; i < current.squads.size(); ++i) {
                if (current.squads[i].leaf) {
                    damage.push_back(current.squads[i].damage_value());
                } else {
                    buffer.push(current.squads[i]);
                }
            }
        }
    }
};