#ifndef ARXML_PARSER
#define ARXML_PARSER

#include <iostream>
#include <vector>
#include <map>
#include "rapidxml/rapidxml.hpp"

using namespace rapidxml;

struct Port {
    std::string name;
};

struct Interface {
    std::string name;
    std::string package;  
};

struct Component {
    std::string name;
    std::string type;
    std::vector<Port> ports;
};

struct Composition {
    std::string name;
    std::string package;
    std::vector<Component> components;
};

struct iref {
    std::string component_ref;
    std::string port_ref;
};

struct Connector {
    std::string name;
    iref provider;
    iref requester;
};

class Arxml {
    private:
        xml_document<> doc;
        std::vector<Composition> compositions;
        std::vector<Connector> connectors;
        std::vector<Interface> interfaces;

        std::map<std::string, std::string> connections;

        void findCompositions();
        void findInterfaces();
        void findConnectors(xml_node<> *composition);
        std::vector<Component> findComponents(xml_node<> *composition);
    public:
        const Composition* getComposition() const;
        Arxml(std::string path);
        ~Arxml();
};

#endif // ARXML_PARSER