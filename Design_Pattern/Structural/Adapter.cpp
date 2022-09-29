#include <iostream>
#include <memory>

typedef int Coordinate;
typedef int Dimension;

class Rectangle
{
    public:
        virtual void draw() = 0;
};


class LegacyRectangle
{
    public:
        LegacyRectangle(Coordinate x1, Coordinate y1, Coordinate x2, Coordinate y2) :
            _x1(x1), _y1(y1), _x2(x2), _y2(y2)
        {
            std::cout << "LegacyRectangle: Create" << "(" << _x1 <<", " << _y1 << " ) => (" << _x2 << ", " << _y2 <<")" <<std::endl;
        }

        void draw() 
        {
            std::cout << "LegacyRectangle: oldDraw" << "(" << _x1 <<", " << _y1 << " ) => (" << _x2 << ", " << _y2 <<")" <<std::endl;
        }
    private:
        Coordinate _x1, _y1, _x2, _y2;
};

class RectangleAdapter : public Rectangle, private LegacyRectangle
{
    public:
        RectangleAdapter(Coordinate x, Coordinate y, Dimension w, Dimension h) :
            LegacyRectangle(x, y, x + w, y + h) 
        {

            std::cout << "RectangleAdapter: Create" << "(" << x <<", " << y << " ), width = " << w << ", height = " << h <<")" <<std::endl;
        }

        void draw() override
        {
            std::cout<<"RectangleAdapter: draw. " << std::endl;
            LegacyRectangle::draw();
        }
};


int main() 
{
    std::unique_ptr<Rectangle> re = std::make_unique<RectangleAdapter>(120, 200, 60, 40);
    re -> draw();
    return 0;
}