using std::queue;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UnitInArmy::UnitInArmy(Unit incoming_unit) {
    unit = &incoming_unit;
    leaf = true;
}

bool UnitInArmy::operator==(const UnitInArmy& compared) {
    if (compared.unit == unit) {
        return true;
    }
    return false;
}

size_t UnitInArmy::health_value() {
    return unit->health_value();
}

size_t UnitInArmy::damage_value() {
    return unit->damage_value();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Army::Army() {
    leaf = false;
}

void Army::Add(vector<Unit*>& new_squad) {
    for (int i = 0; i < new_squad.size(); ++i) {
        squads.emplace_back(UnitInArmy(*new_squad[i]));
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


















