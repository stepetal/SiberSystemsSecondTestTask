#ifndef POINT_H
#define POINT_H

/*
 *
 *
 * Point in cartesian coordinates
 *
 */
class Point
{
    int x;
    int y;
public:
    Point(){};
    Point(int xpos,int ypos) : x(xpos),y(ypos) {}
    void setX(int xpos){ x = xpos; }
    void setY(int ypos){ y = ypos; }
    int getX() { return x; }
    int getY() { return y; }
    bool isNull(){ return ((x == 0) && (y == 0)) ? true : false; }
};

#endif // POINT_H
