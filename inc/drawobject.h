#ifndef DRAW_OBJECT
#define DRAW_OBJECT

#include<string>
#include<vector>

#include "wx/wx.h"
#include "arxmlparser.h"

enum ArxmlType {
    composition,
    component
};

class DrawObject {
public:
    DrawObject(const Arxml& arxml);
    DrawObject(Component component);
    const std::string& getName() const;
    const std::string& getInfo() const;
    const ArxmlType& getType() const;
    const std::vector<DrawObject*>& getChildren() const;
    void draw(wxDC&  dc, int x, int y) const;
    void addChild(DrawObject* child);
private:
    std::string name;
    ArxmlType type;
    std::string info;
    std::vector<DrawObject*> children;
};
#endif