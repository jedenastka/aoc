#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

enum class Opcode {
    Acc,
    Jmp,
    Nop
};

struct Instruction {
    Opcode opcode;
    int parameter;
};

class Vm {

    public:
        Vm();

        void loadCode(std::vector<Instruction>*);
        void reset();

        void step();

        int getInstructionPointer();
        int getAccumulator();
        bool isOn();
    
    private:
        std::vector<Instruction> *code;

        int instructionPointer;
        int accumulator;

        void executeInstruction(Instruction);
    
};

Vm::Vm() {
    reset();
}

void Vm::loadCode(std::vector<Instruction> *code) {
    this->code = code;
}

void Vm::reset() {
    instructionPointer = 0;
    accumulator = 0;
}

void Vm::step() {
    executeInstruction(code->operator[](instructionPointer));
}

int Vm::getInstructionPointer() {
    return instructionPointer;
}

int Vm::getAccumulator() {
    return accumulator;
}

bool Vm::isOn() {
    return instructionPointer < code->size();
}

void Vm::executeInstruction(Instruction instruction) {
    if (instruction.opcode == Opcode::Acc) {
        accumulator += instruction.parameter;
        ++instructionPointer;
    } else if (instruction.opcode == Opcode::Jmp) {
        instructionPointer += instruction.parameter;
    } else if (instruction.opcode == Opcode::Nop) {
        ++instructionPointer;
    }
}

Instruction parseInstruction(std::string instructionLine) {
    Instruction instruction;

    int splitPos = instructionLine.find(' ');

    std::string instructionTypeString = instructionLine.substr(0, splitPos);
    if (instructionTypeString == "acc") {
        instruction.opcode = Opcode::Acc;
    } else if (instructionTypeString == "jmp") {
        instruction.opcode = Opcode::Jmp;
    } else if (instructionTypeString == "nop") {
        instruction.opcode = Opcode::Nop;
    }

    instruction.parameter = stoi(instructionLine.substr(splitPos + 1));
    
    return instruction;
}

bool willLoop(Vm &vm, int *accumulatorBeforeStep = nullptr) {
    vm.reset();

    std::vector<int> visitedInstructions = {0};

    while (vm.isOn()) {
        if (accumulatorBeforeStep != nullptr) {
            *accumulatorBeforeStep = vm.getAccumulator();
        }

        vm.step();

        if (std::find(visitedInstructions.begin(), visitedInstructions.end(), vm.getInstructionPointer()) != visitedInstructions.end()) {
            return true;
        }
        visitedInstructions.push_back(vm.getInstructionPointer());
    }
    return false;
}

void replaceJmpNop(Instruction &instruction) {
    if (instruction.opcode == Opcode::Jmp) {
        instruction.opcode = Opcode::Nop;
    } else {
        instruction.opcode = Opcode::Jmp;
    }
}

int main() {
    std::vector<Instruction> instructions;

    std::string line;
    while (getline(std::cin, line)) {
        instructions.push_back(parseInstruction(line));
    }

    Vm vm;
    vm.loadCode(&instructions);

    int accumulatorBeforeStep;
    willLoop(vm, &accumulatorBeforeStep);
    std::cout << accumulatorBeforeStep << '\n';

    for (Instruction &instruction: instructions) {
        if (instruction.opcode == Opcode::Jmp || instruction.opcode == Opcode::Nop) {
            replaceJmpNop(instruction);

            if (!willLoop(vm)) {
                std::cout << vm.getAccumulator() << '\n';
                break;
            } else {
                replaceJmpNop(instruction);
            }
        }
    }
}