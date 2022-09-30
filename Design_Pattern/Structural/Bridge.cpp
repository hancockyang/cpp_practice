#include <iostream>

class IDrawer 
{
    public:
        virtual ~IDrawer() {}
        virtual void draw() = 0;

};

class DrawerMethod1 : public IDrawer
{
    public:
        DrawerMethod1() {}
        virtual ~DrawerMethod1() {}

        void draw () override
        {
            std::cout<<"call DrawerMethod1"<<std::endl;
        }
        
};

class DrawerMethod2 : public IDrawer
{
    public:
        DrawerMethod2() {}
        virtual ~DrawerMethod2() {}

        void draw () override
        {
            std::cout<<"call DrawerMethod2"<<std::endl;
        }
        
};


class IShape
{
    public:
        IShape(IDrawer* drawer) : drawerMachine {drawer} {};
        virtual ~IShape() {drawerMachine = nullptr;}

        virtual void draw () = 0;
    protected:
        IDrawer* drawerMachine;

};

class Square : public IShape
{
    public: 
        Square(IDrawer* drawer, double side) :
            IShape(drawer), _side(side){}

        void draw () 
        {
            IShape::drawerMachine -> draw();
        }

    private:
        double _side;
};

class Sphere : public IShape
{
    public: 
        Sphere(IDrawer* drawer, double side) :
            IShape(drawer), _side(side){}


        void draw () 
        {
            IShape::drawerMachine -> draw();
        }

    private:
        double _side;
};

int main () 
{
    IDrawer *d1 = new DrawerMethod1();
    IDrawer *d2 = new DrawerMethod2();

    IShape *s1 = new Sphere(d1, 1.0);
    IShape *s2 = new Square(d2, 1.0);

    s1 -> draw();
    s2 -> draw();

    delete s1;
    delete s2;
    delete d1; 
    delete d2; 

    return 0;
}
