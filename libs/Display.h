#include <iostream>


class Display
{
    private:
        int width = 0;
        int height = 0;
    public:
        Display(int, int);
        void draw();
};

Display::Display(int width, int height)
{
    this->width = width;
    this->height = height;
}