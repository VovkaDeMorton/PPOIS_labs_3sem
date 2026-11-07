#ifndef POSTMACHINE_H
#define POSTMACHINE_H

#include <vector>
#include <iostream>

class PostMachine {
private:
    std::vector<int> tape;
    int headPos;
    bool halted;

public:
    PostMachine();
    PostMachine(const std::vector<int>& initialTape, int startPos);
    PostMachine(const PostMachine& other);
    ~PostMachine();

    PostMachine& operator=(const PostMachine& other);
    bool operator==(const PostMachine& other) const;
    bool operator!=(const PostMachine& other) const;
    friend std::ostream& operator<<(std::ostream& os, const PostMachine& machine);
    friend std::istream& operator>>(std::istream& is, PostMachine& machine);

    void moveLeft();
    void moveRight();
    void write(int value);
    void halt();

    int getHeadPos() const;
    int getCell(int index) const;
    bool isHalted() const;
    int getTapeSize() const;
};

#endif