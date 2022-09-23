#include <string>
#include <iostream>
#include <memory>
#include <vector>

//reciever
class Character{
    public:
    std::string name;
    Character(std::string _name) : name(_name) {};
    void move() {
        std::cout << name <<" move"<<std::endl;
    }
    void jump() {
        std::cout << name <<" jump"<<std::endl;
    }
};

//command
class Command {
    public:
    Command(std::shared_ptr<Character> _c) : c{_c} {};
    virtual ~Command() {};
    virtual void execute() = 0;
    virtual void undo() = 0;
    protected:
    std::shared_ptr<Character> c;
};

class Move : public Command {
    using Command::Command;
    void execute() override {
        c->move();
    }

    void undo() override {
        std::cout << c->name << " undo move" << std::endl;
    }
};

class Jump : public Command {
    using Command::Command;
    void execute() override {
        c->jump();
    }

    void undo() override {
        std::cout << c->name << " undo jump" << std::endl;
    }
};

//invoker
class Command_Queue {
    public:
    Command_Queue() {};

    void order(std::unique_ptr<Command> command) {
        commandList.push_back(std::move(command));
    }

    void run() {
        for (int i = 0; i < commandList.size(); ++i) {
            commandList[i]->execute();
        }
    }


    private:
    std::vector<std::unique_ptr<Command>> commandList;
};

int main() {

    std::shared_ptr<Character> c1 = std::make_shared<Character>("h");
    std::shared_ptr<Character> c2 = std::make_shared<Character>("g");

    std::unique_ptr<Command> cmd1 = std::make_unique<Move>(c1);
    std::unique_ptr<Command> cmd2 = std::make_unique<Move>(c1);
    std::unique_ptr<Command> cmd3 = std::make_unique<Jump>(c1);
    std::unique_ptr<Command> cmd4 = std::make_unique<Jump>(c2);

    Command_Queue cq;
    cq.order(std::move(cmd1));
    cq.order(std::move(cmd2));
    cq.order(std::move(cmd4));
    cq.order(std::move(cmd3));

    cq.run();

    return 0;
};

