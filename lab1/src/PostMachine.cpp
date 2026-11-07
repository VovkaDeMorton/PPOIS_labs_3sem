#include "PostMachine.h"

PostMachine::PostMachine() : tape(10, 0), headPos(0), halted(false) {}

PostMachine::PostMachine(const std::vector<int>& initialTape, int startPos) 
    : tape(initialTape), headPos(startPos), halted(false) {
    if (headPos < 0) headPos = 0;
    if (headPos >= tape.size()) tape.resize(headPos + 1, 0);
}

PostMachine::PostMachine(const PostMachine& other) 
    : tape(other.tape), headPos(other.headPos), halted(other.halted) {}

PostMachine::~PostMachine() {}

PostMachine& PostMachine::operator=(const PostMachine& other) {
    if (this != &other) {
        tape = other.tape;
        headPos = other.headPos;
        halted = other.halted;
    }
    return *this;
}

bool PostMachine::operator==(const PostMachine& other) const {
    return tape == other.tape && headPos == other.headPos && halted == other.halted;
}

bool PostMachine::operator!=(const PostMachine& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const PostMachine& machine) {
    for (int i = 0; i < machine.getTapeSize(); ++i) {
        if (i == machine.headPos) os << "[" << machine.tape[i] << "] ";
        else os << machine.tape[i] << " ";
    }
    os << (machine.halted ? "(HALTED)" : "(RUNNING)");
    return os;
}

std::istream& operator>>(std::istream& is, PostMachine& machine) {
    int size, pos;
    if (is >> size >> pos) {
        machine.tape.assign(size, 0);
        machine.headPos = pos;
        machine.halted = false;
        for (int i = 0; i < size; ++i) {
            is >> machine.tape[i];
        }
    }
    return is;
}

void PostMachine::moveLeft() {
    if (halted) return;
    if (headPos > 0) {
        headPos--;
    } else {
        tape.insert(tape.begin(), 0);
    }
}

void PostMachine::moveRight() {
    if (halted) return;
    headPos++;
    if (headPos >= tape.size()) {
        tape.push_back(0);
    }
}

void PostMachine::write(int value) {
    if (halted || (value != 0 && value != 1)) return;
    tape[headPos] = value;
}

void PostMachine::halt() { halted = true; }
int PostMachine::getHeadPos() const { return headPos; }
bool PostMachine::isHalted() const { return halted; }
int PostMachine::getTapeSize() const { return tape.size(); }

int PostMachine::getCell(int index) const {
    if (index < 0 || index >= tape.size()) return 0; // За пределами ленты - пусто
    return tape[index];
}