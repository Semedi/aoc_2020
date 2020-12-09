#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

struct instruction;

struct tprogram {
    int PC;
    int acc;
    int prev;
    vector<shared_ptr<instruction>> instructions;

    tprogram(): 
        PC(0),
        prev(-1),
        acc(0){}

    void run();
    void reset();
    void fix();
    void output();
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

    void swap(){
        op = op == "nop" ? "jmp" : "nop";
    }
};

void tprogram::output()
{
    cout << "Program finished!" << endl;
    cout << "acc: " << acc << endl;
}

// part 1:
void tprogram::run()
{
    while (PC < instructions.size()){
        if (instructions[PC]->counter == 1)
            goto EXCEPTION;

        instructions[PC]->execute();
    }
    output();

    return;
EXCEPTION:
    cout << "infinite loop exception raised!:" << endl;
    cout << "next instruction: ";
    cout << instructions[PC]->op << " " << instructions[PC]->arg << endl;
    cout << "acc: " << acc << endl;
}

// part 2
void tprogram::reset()
{
    PC   = 0;
    acc  = 0;

    if (prev != -1)
        instructions[prev]->swap();

    auto set = true;
    for (int i = 0; i < instructions.size(); i++){
        instructions[i]->counter = 0;
        if (prev < i && set){
            if (instructions[i]->op == "jmp" || instructions[i]->op == "nop"){
                instructions[i]->swap();
                prev = i;
                set = false;
            }
        }
    }
}

void tprogram::fix()
{
    while (PC < instructions.size()){
        if (instructions[PC]->counter == 1)
            goto RESET;

        instructions[PC]->execute();
    }

    output();

    return;
RESET:
    cout << "-----------------------------------------------" << endl;
    cout << "infinite loop exception raised!:" << endl;
    cout << "    next instruction: ";
    cout << instructions[PC]->op << " " << instructions[PC]->arg << endl;

    cout << "    prev instruction: ";
    cout << instructions[prev]->op << " " << instructions[prev]->arg << endl;
    cout << "    acc:  " << acc << endl;
    cout << "The system is going to reset..." << endl;
    cout << endl;

    reset();
    fix();

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
    //program->run();
    program->fix();

    return 0;
}
