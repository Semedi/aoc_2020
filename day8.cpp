#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

struct instruction;

struct tprogram {
    int PC;
    int acc;
    vector<shared_ptr<instruction>> instructions;

    tprogram(): 
        PC(0),
        acc(0){}

    void run();
};

struct instruction {
    string op;
    int arg;
    int counter;
    weak_ptr<tprogram> p;

    instruction(string op, int arg, weak_ptr<tprogram> p):
        op(op),
        arg(arg),
        counter(0),
        p(p){}

    void execute(){
        if (op == "nop"){
            p.lock()->PC++;
        }
        else if (op == "acc"){
            p.lock()->acc+=arg;
            p.lock()->PC++;
        }
        else if (op == "jmp"){
            p.lock()->PC+=arg;
        }
        counter++;
    }
};

// part 1;
void tprogram::run(){
    while (PC < instructions.size()){
        if (instructions[PC]->counter == 1)
            goto EXCEPTION;

        instructions[PC]->execute();
    }

    cout << "Program finished!" << endl;
    cout << "acc: " << acc << endl;

    return;
EXCEPTION:
    cout << "infinite loop exception raised!:" << endl;
    cout << "next instruction: ";
    cout << instructions[PC]->op << " " << instructions[PC]->arg << endl;
    cout << "acc: " << acc << endl;
}

int main ()
{
    string str; 
    ifstream file("input/day8.txt");
    regex rgx("^(\\w+) ([+-]\\d+)$");

    shared_ptr<tprogram> program(new tprogram);
    vector<shared_ptr<instruction>> ins;

    while (getline(file, str)) {
        smatch matches;
        if (regex_search(str, matches, rgx)) {
            ins.push_back(
                    shared_ptr<instruction>(
                        new instruction(
                            matches[1].str(), 
                            stoi(matches[2].str()), 
                            program)
                        )
                    );
        }
        else
            return 1;
    }

    program->instructions = move(ins);
    program->run();

    return 0;
}
