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

std::shared_ptr<IGameObject> MakeGameObjectFactory(ObjectType type) {
    if (ObjectType::PLANE == type) {
        return std::make_shared<Plane>();
    } else if (ObjectType::BOAT == type) {
        return std::make_shared<Boat>();
    }

    return nullptr;
}

int main (){
    std::shared_ptr<IGameObject> myObj1 = MakeGameObjectFactory(ObjectType::PLANE);
    std::shared_ptr<IGameObject> myObj2 = MakeGameObjectFactory(ObjectType::BOAT);

    return 0;

}
