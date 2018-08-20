#include "drawobject.h"

DrawObject::DrawObject(const char* name, ArxmlType type) {
    this->name = std::string(name);
    this->type = type;
}
const std::string& DrawObject::getName() {
    return this->name;
}
const ArxmlType& DrawObject::getType() {
    return this->type;
}
const std::vector<DrawObject*>& DrawObject::getChildren() {
    return this->children;
}