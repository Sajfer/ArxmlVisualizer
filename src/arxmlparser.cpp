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

    for(auto const& value: compositions) {
        std::cout << value.name << std::endl;
    }
}

Arxml::~Arxml() {

}

void Arxml::findCompositions() {

    xml_node<> *composition = doc.first_node("AUTOSAR")->first_node("AR-PACKAGES");
    composition = composition->first_node("AR-PACKAGE");
    composition = composition->first_node("ELEMENTS");

    Composition tmp_composition;

    for (xml_node<> *child = composition->first_node("COMPOSITION-SW-COMPONENT-TYPE"); child; child = child->next_sibling()) {
        tmp_composition = {child->first_node("SHORT-NAME")->value()};
        compositions.push_back(tmp_composition);
    }
}

void Arxml::findComponents(Composition composition) {

}