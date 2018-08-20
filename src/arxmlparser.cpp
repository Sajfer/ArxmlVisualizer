#include <iostream>
#include <fstream>
#include <algorithm>

#include "arxmlparser.h"


Arxml::Arxml(std::string path) {
    
    std::ifstream in(path);
    std::string contents((std::istreambuf_iterator<char>(in)), 
    std::istreambuf_iterator<char>());

    doc.parse<0>(const_cast<char*>(contents.c_str()));

    findCompositions();

    std::cout << "Composition:" << std::endl;
    for(auto const& comp: compositions) {
        std::cout << comp.name << std::endl;
        for(auto const& value: comp.components) {
           std::cout << "   -" << value.name << "(" << value.type << ")" << std::endl;
        }
    }
    std::cout << "Connectors:" << std::endl;
    for(auto const& conn: connectors) {
        std::cout << conn.name << std::endl;
    }
}

Arxml::~Arxml() {

}

std::vector<Component> Arxml::findComponents(xml_node<> *composition) {

    Component tmp_component;

    xml_node<> *component_node = composition->first_node("COMPONENTS");

    std::vector<Component> components;
    for (xml_node<> *child = component_node->first_node("SW-COMPONENT-PROTOTYPE"); child; child = child->next_sibling()) {
        tmp_component = {child->first_node("SHORT-NAME")->value(), child->first_node("TYPE-TREF")->value()};
        components.push_back(tmp_component);
    }
    return components;
}

void Arxml::findCompositions() {

    Composition tmp_composition;

    xml_node<> *composition = doc.first_node("AUTOSAR")->first_node("AR-PACKAGES");

    for (xml_node<> *child = composition->first_node("AR-PACKAGE"); child; child = child->next_sibling()) {
        xml_node<> *package = child->first_node("ELEMENTS");
        for (xml_node<> *child = package->first_node("COMPOSITION-SW-COMPONENT-TYPE"); child; child = child->next_sibling()) {
            tmp_composition = {child->first_node("SHORT-NAME")->value(),};
            tmp_composition.components = findComponents(child);

            findConnectors(child);

            compositions.push_back(tmp_composition);
        }
    }
}

void Arxml::findConnectors(xml_node<> *composition) {

    Connector tmp_connector;

    xml_node<> *component_node = composition->first_node("CONNECTORS");

    std::vector<Component> components;
    for (xml_node<> *child = component_node->first_node("ASSEMBLY-SW-CONNECTOR"); child; child = child->next_sibling()) {
        xml_node<> *component = child->first_node("SHORT-NAME");
        tmp_connector = {component->value()};

        connectors.push_back(tmp_connector);
    }
}
