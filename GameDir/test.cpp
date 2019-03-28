#include <iostream>
#include <memory>
#include "unit.h"
#include "unit.cpp"
#include "commander.h"
#include "commander.cpp"
#include <gtest/gtest.h>


class Units_and_Factories_Fixture : public ::testing::Test {

protected:

    virtual void SetUp() {}

    AeonUnitFactory aeon_factory;

    SiegeTank* aeon_tank;

    AssaultBot* aeon_bot;

    CybranUnitFactory cybran_factory;

    SiegeTank* cybran_tank;

    AssaultBot* cybran_bot;

    CybranSiegeTank* c_tank;

    CybranAssaultBot* c_bot;

    AeonSiegeTank* a_tank;

    AeonAssaultBot* a_bot;

    virtual size_t Health(CybranSiegeTank* tank) {
        return tank->health;
    }

    virtual size_t Health(AeonSiegeTank* tank) {
        return tank->health;
    }

    virtual size_t Health(CybranAssaultBot* tank) {
        return tank->health;
    }

    virtual size_t Health(AeonAssaultBot* tank) {
        return tank->health;
    }

};

class Commanders_Fixture : public ::testing::Test {
public:

    std::shared_ptr<AeonCommander> aeon_com_first;

    std::shared_ptr<AeonCommander> aeon_com_second;

    AssaultBot* bot;

    SiegeTank* tank;

    CybranSiegeTank* c_tank;

    AeonAssaultBot* a_bot;

    std::shared_ptr<CybranCommander> cybran_com_first;

    std::shared_ptr<CybranCommander> cybran_com_second;

    virtual size_t spawning_points_aeon() { // важно отметить, что возвращаем показатели по второму сохранённому указателю, и,
        // значит, проверяя правильность значения после операции над первым указателем также проверим и корректность
        // работы singleton'а
        return aeon_com_second->spawning_points;
    }

    virtual size_t spawning_points_cybran() { // важно отметить, что возвращаем показатели по второму сохранённому указателю, и,
        // значит, проверяя правильность значения после операции над первым указателем также проверим и корректность
        // работы singleton'а
        return cybran_com_second->spawning_points;
    }

    virtual size_t Health(AeonAssaultBot* tank) {
        return tank->health;
    }

    virtual size_t Health(CybranSiegeTank* tank) {
        return tank->health;
    }

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Запуск первого теста из данного набора обязателен, третий по счету проверяет корректно только после второго (решил
// вынести отдельно, т.к. второй и так велик)

TEST_F(Units_and_Factories_Fixture, AeonFactoryTest) {
    ASSERT_NO_THROW(aeon_tank = aeon_factory.create_tank(); aeon_bot = aeon_factory.create_bot(););
}

TEST_F(Units_and_Factories_Fixture, CybranFactoryTest) {
    ASSERT_NO_THROW(cybran_tank = cybran_factory.create_tank(); cybran_bot = cybran_factory.create_bot(););
}


TEST_F(Units_and_Factories_Fixture, UnitsInteractionTest) { // проверяем юниты на взаимодействие (сравниваем здоровье
    // после атаки с расчитанным
    aeon_tank->attack(cybran_tank);
    ASSERT_NO_THROW(c_tank = dynamic_cast<CybranSiegeTank*>(cybran_tank)); // заодно проверяем корректность приведения
    // типов в иерархии
    EXPECT_EQ(Health(c_tank), 12);
    aeon_tank->attack(cybran_bot);
    ASSERT_NO_THROW(c_bot = dynamic_cast<CybranAssaultBot*>(cybran_bot));
    EXPECT_EQ(Health(c_bot), 7);
    aeon_bot->attack(cybran_tank);
    EXPECT_EQ(Health(c_tank), 10);
    aeon_bot->attack(cybran_bot);
    EXPECT_EQ(Health(c_bot), 5);
    cybran_tank->attack(aeon_tank);
    ASSERT_NO_THROW(a_tank = dynamic_cast<AeonSiegeTank*>(aeon_tank));
    EXPECT_EQ(Health(a_tank), 10);
    cybran_tank->attack(aeon_bot);
    ASSERT_NO_THROW(a_bot = dynamic_cast<AeonAssaultBot*>(aeon_bot));
    EXPECT_EQ(Health(a_bot), 10);
    cybran_bot->attack(aeon_tank);
    EXPECT_EQ(Health(a_tank), 7);
    cybran_bot->attack(aeon_bot);
    EXPECT_EQ(Health(a_bot), 7);
}

TEST_F(Units_and_Factories_Fixture, UnitDeathTest) { // запускается строго после предыдущего теста (после предыдущего
    // теста у юнитов остаётся меньшее количество hp), сначала наносим юнитам несмертельный урон, затем добиваем
    EXPECT_FALSE(cybran_tank->under_attack(1)); // ещё жив (возвращает true если умер)
    EXPECT_TRUE(cybran_tank->under_attack(9)); // должен умереть
    EXPECT_FALSE(aeon_tank->under_attack(1)); // ещё жив
    EXPECT_TRUE(aeon_tank->under_attack(6)); // должен умереть
    EXPECT_FALSE(cybran_bot->under_attack(1)); // ещё жив
    EXPECT_TRUE(cybran_bot->under_attack(4)); // должен умереть
    EXPECT_FALSE(aeon_bot->under_attack(1)); // ещё жив
    EXPECT_TRUE(aeon_bot->under_attack(6)); // должен умереть
}

TEST_F(Units_and_Factories_Fixture, AbstractFactoryTest) {
    ASSERT_NO_THROW(aeon_tank = aeon_factory.create_tank()); // на место (возможно уничтоженных после пред. теста)
    // юнитов создаём новые
    ASSERT_NO_THROW(aeon_bot = aeon_factory.create_bot());
    ASSERT_NO_THROW(cybran_bot = cybran_factory.create_bot());
    ASSERT_NO_THROW(cybran_tank = cybran_factory.create_tank());
    ASSERT_EQ(dynamic_cast<CybranSiegeTank*>(aeon_tank), nullptr); // пытаемся по кругу совершить некорректные
    // приведения типов, должны получать nullptr
    ASSERT_EQ(dynamic_cast<AeonAssaultBot*>(cybran_tank), nullptr);
    ASSERT_EQ(dynamic_cast<CybranAssaultBot*>(aeon_bot), nullptr);
    ASSERT_EQ(dynamic_cast<AeonSiegeTank*>(cybran_bot), nullptr);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Выделенный набор тестов - набор тестов над синглетонами: предполгается запуск тестов по порядку и без пропуска (т.к.
// например в третьем тесте полагаемся на корректность работы синглетонов, которая проверяется в первых двух)

TEST_F(Commanders_Fixture, AeonSingletonRealizationTest) {
    ASSERT_NO_THROW(aeon_com_first = Aeon::commander_unit()); // в private поле Aeon должен сохраниться указатель на
    // этот же юнит
    ASSERT_NO_THROW(aeon_com_second = Aeon::commander_unit()); // должен вернуться указатель на уже созданный юнит

    ASSERT_TRUE(aeon_com_first == aeon_com_second);
}

TEST_F(Commanders_Fixture, CybranSingletonRealizationTest) { // аналогично с предыдущим тестом
    ASSERT_NO_THROW(cybran_com_first = Cybran::commander_unit());

    ASSERT_NO_THROW(cybran_com_second = Cybran::commander_unit());

    ASSERT_TRUE(cybran_com_first == cybran_com_second);
}

TEST_F(Commanders_Fixture, CommandersProducingTest) {
    aeon_com_first = Aeon::commander_unit();
    aeon_com_second = Aeon::commander_unit();
    cybran_com_first = Cybran::commander_unit();
    cybran_com_second = Cybran::commander_unit();
    ASSERT_NO_THROW(bot = aeon_com_first->ProduceBot());
    EXPECT_EQ(spawning_points_aeon(), 7);
    ASSERT_NO_THROW(tank = cybran_com_first->ProduceTank());
    EXPECT_EQ(spawning_points_cybran(), 6);
}

TEST_F(Commanders_Fixture, CommandersAttackTest) {
    aeon_com_first = Aeon::commander_unit();
    aeon_com_second = Aeon::commander_unit();
    cybran_com_first = Cybran::commander_unit();
    cybran_com_second = Cybran::commander_unit();
    aeon_com_first->attack(tank);
    ASSERT_NO_THROW(c_tank = dynamic_cast<CybranSiegeTank*>(tank));
    EXPECT_EQ(Health(c_tank), 10);
    aeon_com_second->attack(bot); // friendly fire
    ASSERT_NO_THROW(a_bot = dynamic_cast<AeonAssaultBot*>(bot));
    EXPECT_EQ(Health(a_bot), 7);
    cybran_com_first->attack(bot);
    EXPECT_EQ(Health(a_bot), 1);
    cybran_com_second->attack(tank); // friendly fire
    EXPECT_EQ(Health(c_tank), 4);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
