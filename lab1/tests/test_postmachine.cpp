#include <gtest/gtest.h>
#include <sstream>
#include "PostMachine.h"

TEST(PostMachineTest, DefaultConstructor) {
    PostMachine pm;
    EXPECT_EQ(pm.getHeadPos(), 0);
    EXPECT_EQ(pm.getTapeSize(), 10);
    EXPECT_FALSE(pm.isHalted());
}

TEST(PostMachineTest, MoveAndExpand) {
    PostMachine pm;
    pm.moveRight();
    EXPECT_EQ(pm.getHeadPos(), 1);
    
    pm.moveLeft();
    pm.moveLeft();
    EXPECT_EQ(pm.getHeadPos(), 0);
    EXPECT_EQ(pm.getTapeSize(), 11); // Лента расширилась влево
}

TEST(PostMachineTest, WriteAndHalt) {
    PostMachine pm;
    pm.write(1);
    EXPECT_EQ(pm.getCell(0), 1);
    
    pm.halt();
    EXPECT_TRUE(pm.isHalted());
    
    pm.write(0); // После остановки писать нельзя
    EXPECT_EQ(pm.getCell(0), 1);
}

TEST(PostMachineTest, Operators) {
    PostMachine pm1;
    PostMachine pm2;
    EXPECT_TRUE(pm1 == pm2);
    
    pm1.write(1);
    EXPECT_TRUE(pm1 != pm2);
    
    PostMachine pm3 = pm1;
    EXPECT_TRUE(pm1 == pm3);
}

TEST(PostMachineTest, Streams) {
    PostMachine pm;
    std::stringstream ss;
    ss << pm;
    EXPECT_FALSE(ss.str().empty());
    
    std::stringstream input("3 0 1 0 1");
    input >> pm;
    EXPECT_EQ(pm.getTapeSize(), 3);
    EXPECT_EQ(pm.getCell(0), 1);
}

// ===== ДОБАВЛЕНО ДЛЯ ПОЛНОГО ПОКРЫТИЯ =====

// Тест 6: Конструктор с начальной лентой (непокрытые строки 15-20)
TEST(PostMachineTest, ConstructorWithInitialTape) {
    PostMachine pm({1, 0, 1, 1}, 2);
    EXPECT_EQ(pm.getTapeSize(), 4);
    EXPECT_EQ(pm.getHeadPos(), 2);
    EXPECT_EQ(pm.getCell(0), 1);

    // startPos за правым краем -> лента расширяется до startPos + 1
    PostMachine pm2({1, 0, 1}, 99);
    EXPECT_EQ(pm2.getHeadPos(), 99);
    EXPECT_EQ(pm2.getTapeSize(), 100);
    EXPECT_EQ(pm2.getCell(99), 0);
}

// Тест 7: Присваивание из другого объекта + самоприсваивание (строки 30-33)
TEST(PostMachineTest, CopyAssignmentFromOther) {
    PostMachine a;
    PostMachine b({1, 1, 0}, 1);

    a = b;                        // ветка this != &other
    EXPECT_TRUE(a == b);
    EXPECT_EQ(a.getCell(1), 1);

    a = a;                        // самоприсваивание
    EXPECT_TRUE(a == b);
}

// Тест 8: moveRight за правый край расширяет ленту (строка 68)
TEST(PostMachineTest, MoveRightExtendsTape) {
    PostMachine pm({0}, 0);
    EXPECT_EQ(pm.getTapeSize(), 1);

    pm.moveRight();               // headPos == size -> push_back(0)
    EXPECT_EQ(pm.getTapeSize(), 2);
    EXPECT_EQ(pm.getHeadPos(), 1);
    EXPECT_EQ(pm.getCell(1), 0);
}

// Тест 9: getCell с валидным индексом (строка 84)
TEST(PostMachineTest, GetCellValidIndex) {
    PostMachine pm({1, 0}, 0);
    EXPECT_EQ(pm.getCell(0), 1);
    EXPECT_EQ(pm.getCell(1), 0);
}



