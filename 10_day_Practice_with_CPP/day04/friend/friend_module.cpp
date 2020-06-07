#include <iostream>
#include <cmath>

using namespace std;

class Point {
    private:
        int x, y;
    
    public:
        Point(int _x = 0, int _y = 0): x(_x), y(_y){}

        int GetX() const{
            return x;
        }
        
        friend float Distance(Point& a, Point& b); 
};

//通过将一个模块声明为另一个模块的友元，该模块能够引用到另一个模块中本是被隐藏的信息。 
//破坏了隐藏性
float Distance(Point& a, Point& b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy * dy);
}

int main()
{
    Point p1(3.0, 5.0);
    Point p2(4.0, 6.0);
    cout <<"Distance = " << Distance(p1, p2) << endl;

    return 0;
}