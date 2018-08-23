#ifndef DRAW_OBJECT
#define DRAW_OBJECT

#include<string>
#include<vector>

#include "wx/wx.h"
#include "arxmlparser.h"

class DrawObject {
public:
    DrawObject(const Arxml& arxml);
    DrawObject(Component component);
    const std::string& getName() const;
    const std::string& getInfo() const;
    const std::vector<DrawObject*>& getChildren() const;
    void draw(wxDC&  dc, int x, int y);
    void addChild(DrawObject* child);
private:
    std::string name;
    std::string type;
    std::vector<DrawObject*> children;

    int start_x;
    int start_y;
    int end_x;
    int end_y;
};
#endif