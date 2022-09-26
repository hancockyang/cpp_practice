
#include <string>
#include <memory>
#include <iostream>

class IGameObject {
    public:
        virtual ~IGameObject() {};
        virtual void Update() = 0;
        virtual void Render() = 0;
};

class Plane : public IGameObject {
    public:
        Plane () {
            std::cout<< "create plane"<<std::endl;
        }
        void Update () override{}
        void Render () override{}

};

class Boat : public IGameObject {
    public:
        Boat () {
            std::cout<< "create boat"<<std::endl;
        }
        void Update () override{}
        void Render () override{}

};

enum class ObjectType {PLANE, BOAT};

class FactoryGameObjects{
    public:
    static std::shared_ptr<IGameObject> CreateObj(ObjectType type) {
        if (ObjectType::PLANE == type) {
            s_plane++;
            return std::make_shared<Plane>();
        } else if (ObjectType::BOAT == type) {
            s_boat++;
            return std::make_shared<Boat>();
        }

        return nullptr;
    }

    static void printCounts() {
        std::cout << "planes: " << s_plane << std::endl;
        std::cout << "boats: " << s_boat << std::endl;
    }
    private:
        FactoryGameObjects() {};
        ~FactoryGameObjects() {};
        FactoryGameObjects(const FactoryGameObjects& o){};

        static int s_plane, s_boat;

};

int FactoryGameObjects::s_plane = 0;
int FactoryGameObjects::s_boat = 0;

int main (){

    std::shared_ptr<IGameObject> myObject  = FactoryGameObjects::CreateObj(ObjectType::PLANE);
    std::shared_ptr<IGameObject> myObject2 = FactoryGameObjects::CreateObj(ObjectType::BOAT);
    std::shared_ptr<IGameObject> myObject3 = FactoryGameObjects::CreateObj(ObjectType::BOAT);

    FactoryGameObjects::printCounts();

    return 0;

}
