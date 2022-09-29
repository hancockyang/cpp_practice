#include <string>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>

class IGameObject {
    public:
        virtual ~IGameObject() {};

        virtual void ObjectPlayDefaultAnimation() = 0;
        virtual void ObjectMoveInGame() = 0;
        virtual void Update(int, int) = 0;
        virtual void Render() = 0;
        virtual std::shared_ptr<IGameObject> clone() = 0;
};

class Plane : public IGameObject {
    public:
        Plane (int x, int y) : _x(x), _y(y) {
            std::cout<< "create plane at " <<"x = " << _x << " y = " << _y <<std::endl;
            ObjectCreated++;
        }

        void ObjectPlayDefaultAnimation () override{}
        void ObjectMoveInGame () override{}
        void Update (int x, int y) override{
            _x = x;
            _y = y;
        }
        void Render () override{}
        static std::shared_ptr<IGameObject> Create () {
            return std::make_shared<Plane>(0, 0);
        }

        std::shared_ptr<IGameObject> clone() {
            return std::make_shared<Plane>(_x, _y);
        }
        static void print () {
            std::cout<<"created " << ObjectCreated << " plane." << std::endl;
        }
    private:
        static int ObjectCreated;
        int _x, _y;

};

class Boat : public IGameObject {
    public:
        Boat (int x, int y) : _x(x), _y(y) {
            std::cout<< "create boat at " <<"x = " << x << " y = " << y <<std::endl;
            ObjectCreated++;
        }
        void ObjectPlayDefaultAnimation () override{}
        void ObjectMoveInGame () override{}
        void Update (int x, int y ) override{
            _x = x;
            _y = y;
        }
        void Render () override{}
        static std::shared_ptr<IGameObject> Create () {
            return std::make_shared<Boat>(0, 0);
        }

        std::shared_ptr<IGameObject> clone() {
            return std::make_shared<Boat>(_x, _y);
        }

        static void print () {
            std::cout<<"created " << ObjectCreated << " plane." << std::endl;
        }
    private:
        static int ObjectCreated;
        int _x, _y;

};

class MyGameObjectFactory {
    //typedef std::shared_ptr<IGameObject> (*CreateObjectCallback) ();
    typedef std::function<std::shared_ptr<IGameObject>()> CreateObjectCallback;

    public:
        static void RegisterObject(const std::string& type, CreateObjectCallback cb) {
            std::cout<<"register " << type << std::endl;
            s_Objects[type] = cb;
        }

        static void UnregisterObject(const std::string& type) {
            std::cout<<"unregister " << type << std::endl;
            s_Objects.erase(type);
        }


        static std::shared_ptr<IGameObject> CreateSingleObject(const std::string& type) {
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

    std::vector<std::shared_ptr<IGameObject>> gameCollection;

    std::shared_ptr<IGameObject> object1 = MyGameObjectFactory::CreateSingleObject("plane");
    std::shared_ptr<IGameObject> object2 = MyGameObjectFactory::CreateSingleObject("plane");
    std::shared_ptr<IGameObject> object3 = MyGameObjectFactory::CreateSingleObject("boat");
    std::shared_ptr<IGameObject> object4 = MyGameObjectFactory::CreateSingleObject("plane");
    object1->Update(1, 0);
    
    std::shared_ptr<IGameObject> object5 = object1->clone();

    gameCollection.push_back(object1);
    gameCollection.push_back(object2);
    gameCollection.push_back(object3);
    gameCollection.push_back(object4);


    return 0;

}
