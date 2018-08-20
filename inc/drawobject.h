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
    const std::string& getName() const;
    const ArxmlType& getType() const;
    const std::vector<DrawObject*>& getChildren() const;
    void draw(wxDC&  dc, int x, int y) const;
private:
    std::string name;
    ArxmlType type;
    std::vector<DrawObject*> children;
};
#endif