#include <iostream>
#include <vector>

#include "rapidxml/rapidxml.hpp"

using namespace rapidxml;

struct Component {
    std::string name;
};

struct Composition {
    std::string name;
    std::vector<Component> components;
};

class Arxml {
    private:
        xml_document<> doc;
        std::vector<Composition> compositions;
        void findCompositions();
        std::vector<Component> findComponents(xml_node<> *composition);
    public:
        Arxml(std::string path);
        ~Arxml();
};