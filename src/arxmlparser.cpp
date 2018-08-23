#include <iostream>
#include <fstream>
#include <algorithm>

#include <cstring>

#include "arxmlparser.h"


Arxml::Arxml(std::string path) {
    
    std::ifstream in(path);
    std::string contents((std::istreambuf_iterator<char>(in)), 
    std::istreambuf_iterator<char>());

    doc.parse<0>(const_cast<char*>(contents.c_str()));

    findCompositions();
    findInterfaces();

    std::cout << "Composition:" << std::endl;
    for(auto const& comp: compositions) {
        std::cout << comp.name << " (package: " << comp.package << ")" << std::endl;
        for(auto const& value: comp.components) {
           std::cout << "   -" << value.name << "(" << value.type << ")" << std::endl;
        }
    }
    std::cout << "Connectors:" << std::endl;
    for(auto const& conn: connectors) {
        std::cout << conn.name << std::endl;
        std::cout << "  Provider:" << std::endl;
        std::cout << "    -" << conn.provider.component_ref << std::endl;
        std::cout << "    -" << conn.provider.port_ref << std::endl;
        std::cout << "  Requester:" << std::endl;
        std::cout << "    -" << conn.requester.component_ref << std::endl;
        std::cout << "    -" << conn.requester.port_ref << std::endl;
    }
    std::cout << "Interfaces:" << std::endl;
    for(auto const& iface: interfaces) {
        std::cout << iface.name << " (package: " << iface.package  << ")" << std::endl;
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
    std::string package_name;

    xml_node<> *composition = doc.first_node("AUTOSAR")->first_node("AR-PACKAGES");

    for (xml_node<> *child = composition->first_node("AR-PACKAGE"); child; child = child->next_sibling()) {
        package_name = child->first_node("SHORT-NAME")->value();
        xml_node<> *package = child->first_node("ELEMENTS");
        for (xml_node<> *child = package->first_node("COMPOSITION-SW-COMPONENT-TYPE"); child; child = child->next_sibling()) {
            tmp_composition = {child->first_node("SHORT-NAME")->value(), package_name};
            tmp_composition.components = findComponents(child);

            findConnectors(child);

            compositions.push_back(tmp_composition);
        }
    }
}

void Arxml::findInterfaces() {

    std::string package_name;
    Interface tmp_interface;


    xml_node<> *composition = doc.first_node("AUTOSAR")->first_node("AR-PACKAGES");

    for (xml_node<> *child = composition->first_node("AR-PACKAGE"); child; child = child->next_sibling()) {
        package_name = child->first_node("SHORT-NAME")->value();
        xml_node<> *package = child->first_node("ELEMENTS");

        for (xml_node<> *child = package->first_node("SENDER-RECEIVER-INTERFACE"); child; child = child->next_sibling()) {
            tmp_interface = {child->first_node("SHORT-NAME")->value(), package_name};

            interfaces.push_back(tmp_interface);
        }
    }
}

const Composition* Arxml::getComposition() const {
    if (compositions.size() != 0) {
        return &compositions[0];
    } 
    return nullptr;
}
void Arxml::findConnectors(xml_node<> *composition) {

    Connector tmp_connector;

    xml_node<> *component_node = composition->first_node("CONNECTORS");


    std::vector<Component> components;
    for (xml_node<> *child = component_node->first_node("ASSEMBLY-SW-CONNECTOR"); child; child = child->next_sibling()) {
        xml_node<> *component = child->first_node("SHORT-NAME");
        for (xml_node<> *child = component->next_sibling(); child; child = child->next_sibling()) {
            if(strcmp(child->name(), "PROVIDER-IREF") == 0) {
                tmp_connector.provider.component_ref = child->first_node("CONTEXT-COMPONENT-REF")->value();
                tmp_connector.provider.port_ref = child->first_node("TARGET-P-PORT-REF")->value();
            }
            if(strcmp(child->name(), "REQUESTER-IREF") == 0) {
                tmp_connector.requester.component_ref = child->first_node("CONTEXT-COMPONENT-REF")->value();
                tmp_connector.requester.port_ref = child->first_node("TARGET-R-PORT-REF")->value();
            }
        }
        tmp_connector.name = component->value();
        connectors.push_back(tmp_connector);
    }
}
