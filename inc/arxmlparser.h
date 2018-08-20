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

struct Connector {
    std::string name;
};

class Arxml {
    private:
        xml_document<> doc;
        std::vector<Composition> compositions;
        std::vector<Connector> connectors;

        void findCompositions();
        void findConnectors(xml_node<> *composition);
        std::vector<Component> findComponents(xml_node<> *composition);
    public:
        Arxml(std::string path);
        ~Arxml();
};