#include<iostream>
#include<string>
#include<vector>

// thread safe
class Single {
    public:
    static Single& getInstance () {
        static Single signal;
        return signal;
    }

    void printMessages() {
        std::cout << "print signals" << std::endl;
        for (const auto& e : m_messages) {
            std::cout << e << std::endl;
        }
    }

    void addMessage(const std::string& s) {
        m_messages.push_back(s);
    }

    private:
    Single() {
        std::cout << "constructor" << std::endl;
    }
    ~Single() {
        std::cout << "destructor" << std::endl;
    }
    Single(const Single& copy);

    const Single &operator=(const Single& copy);

    std::vector<std::string> m_messages;
};

int main() {
    Single::getInstance().addMessage("hell 1");
    Single::getInstance().addMessage("hell 2");
    Single::getInstance().addMessage("hell 3");

    Single::getInstance().printMessages();
    return 0;
}