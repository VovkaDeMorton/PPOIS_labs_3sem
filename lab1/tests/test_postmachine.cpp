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