#include <iostream>

class Widget {
public:
  Widget() = default;

  Widget(int w)
  : Widget{w, getHeight(w)}
  {}

  Widget(int w, int h)
  : width{w}
  , height{h}
  {}

  void show()
  {
    std::cout << std::boolalpha << width << "x" << height << ", frame: " << frame << ", visible: " << visible
              << std::endl;
  }

private:
  static int getHeight(int w) { return w * 3 / 4; }
  const int  width{640};
  const int  height{480};
  const bool frame{false};
  const bool visible{true};
};

int main()
{
  Widget wVGA;
  Widget wSVGA(800);
  Widget wHD(1280, 720);

  wVGA.show();
  wSVGA.show();
  wHD.show();
}
