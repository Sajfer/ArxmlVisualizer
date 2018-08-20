#ifndef DRAW_OBJECT
#define DRAW_OBJECT

#include<string>
#include<vector>

enum ArxmlType {
    composition,
    component
};

class DrawObject {
public:
    DrawObject(const char* name, ArxmlType type);
    const std::string& getName();
    const ArxmlType& getType();
    const std::vector<DrawObject*>& getChildren();
private:
    std::string name;
    ArxmlType type;
    std::vector<DrawObject*> children;
};
#endif