#include <string>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <vector>

class IGameObject {
    public:
        virtual ~IGameObject() {};

        virtual void ObjectPlayDefaultAnimation() = 0;
        virtual void ObjectMoveInGame() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
};

class Plane : public IGameObject {
    public:
        Plane (int x, int y) {
            std::cout<< "create plane"<<std::endl;
            ObjectCreated++;
        }

        void ObjectPlayDefaultAnimation () override{}
        void ObjectMoveInGame () override{}
        void Update () override{}
        void Render () override{}
        static IGameObject* Create () {
            return new Plane (0, 0);
        }

        static void print () {
            std::cout<<"created " << ObjectCreated << " plane." << std::endl;
        }
    private:
        static int ObjectCreated;

};

class Boat : public IGameObject {
    public:
        Boat (int x, int y) {
            std::cout<< "create boat"<<std::endl;
            ObjectCreated++;
        }
        void ObjectPlayDefaultAnimation () override{}
        void ObjectMoveInGame () override{}
        void Update () override{}
        void Render () override{}
        static IGameObject* Create () {
            return new Boat (0, 0);
        }
        static void print () {
            std::cout<<"created " << ObjectCreated << " plane." << std::endl;
        }
    private:
        static int ObjectCreated;

};

class MyGameObjectFactory {
    typedef IGameObject *(*CreateObjectCallback) ();

    public:
        static void RegisterObject(const std::string& type, CreateObjectCallback cb) {
            std::cout<<"register " << type << std::endl;
            s_Objects[type] = cb;
        }

        static void UnregisterOjbect(const std::string& type) {
            std::cout<<"unregister " << type << std::endl;
            s_Objects.erase(type);
        }


        static IGameObject* CreateSingleObject(const std::string& type) {
            CallbackHashmap::iterator it = s_Objects.find(type);

            if (it != s_Objects.end()) {
                return it -> second();
            }
            //throw error
            return nullptr;
        }

    private:
        typedef std::unordered_map<std::string, CreateObjectCallback> CallbackHashmap;

        static CallbackHashmap s_Objects;

};
MyGameObjectFactory::CallbackHashmap MyGameObjectFactory::s_Objects;

int Plane::ObjectCreated = 0;
int Boat::ObjectCreated = 0;


int main (){

    MyGameObjectFactory::RegisterObject("plane", &Plane::Create);
    MyGameObjectFactory::RegisterObject("boat", &Boat::Create);

    std::vector<IGameObject*> gameCollection;

    IGameObject* object1 = MyGameObjectFactory::CreateSingleObject("plane");
    IGameObject* object2 = MyGameObjectFactory::CreateSingleObject("plane");
    IGameObject* object3 = MyGameObjectFactory::CreateSingleObject("boat");
    IGameObject* object4 = MyGameObjectFactory::CreateSingleObject("plane");

    gameCollection.push_back(object1);
    gameCollection.push_back(object2);
    gameCollection.push_back(object3);
    gameCollection.push_back(object4);

    delete object1;
    delete object2;
    delete object3;
    delete object4;


    return 0;

}
