#ifndef ARXML_PARSER
#define ARXML_PARSER
#include <iostream>
#include <vector>

#include "rapidxml/rapidxml.hpp"

using namespace rapidxml;

struct Component {
    std::string name;
    std::string type;
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
        const Composition* getComposition() const;
        Arxml(std::string path);
        ~Arxml();
};

#endif