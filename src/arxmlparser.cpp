#include <iostream>
#include <fstream>
#include <algorithm>

#include <cstring>

#include "arxmlparser.h"
#include "autosar_type_defines.h"


using namespace std;

void find_nodes_of_type(vector<xml_node<>*>& result_vector, xml_node<>& parent, string& type) {
    xml_node<>* current = parent.first_node();

    while (current) {
        if (strcmp(current->name(), type.c_str()) != 0) {
            find_nodes_of_type(result_vector, *current, type);
        } else {
            result_vector.push_back(current);
        }
        current = current->next_sibling();
    }
}

vector<xml_node<>*> find_nodes_of_type(rapidxml::xml_document<>& doc, string& type) {
    vector<xml_node<>*> result;

    xml_node<>* top = doc.first_node();
    find_nodes_of_type(result, *top, type);

    return result;
}

std::string get_autosar_path_of_node(xml_node<>& node) {
    auto name_node = node.first_node(SHORT_NAME);
    auto parent_node = node.parent();
    
    if (!name_node)
        return "";
    
    std::string path(name_node->value());

    while(parent_node) {
        name_node = parent_node->first_node(SHORT_NAME);

        if (name_node) {
            path.insert(0, "/");
            path.insert(0, name_node->value());
        }

        parent_node = parent_node->parent();
    }

    return path;
}

Arxml::Arxml(string path) {
    
    ifstream in(path);
    string contents((istreambuf_iterator<char>(in)), 
    istreambuf_iterator<char>());

    doc.parse<0>(const_cast<char*>(contents.c_str()));

    component_type_map = getComponentTypes();
    findCompositions();
    findInterfaces();
    findPorts();

    cout << "Composition:" << endl;
    for(auto const& comp: compositions) {
        cout << comp.name << " (package: " << comp.package << ")" << endl;
        for(auto const& value: comp.components) {
           cout << "   -" << value.name << "(" << value.type.name << ")" << endl;
        }
    }
    cout << "Connectors:" << endl;
    for(auto const& conn: connectors) {
        cout << conn.name << endl;
        cout << "  Provider:" << endl;
        cout << "    -" << conn.provider.component_ref << endl;
        cout << "    -" << conn.provider.port_ref << endl;
        cout << "  Requester:" << endl;
        cout << "    -" << conn.requester.component_ref << endl;
        cout << "    -" << conn.requester.port_ref << endl;
    }
    cout << "Interfaces:" << endl;
    for(auto const& iface: interfaces) {
        cout << iface.name << " (package: " << iface.package  << ")" << endl;
    }
    cout << "Connections:" << endl;
    for(auto const& conn: connections) {
        cout << conn.first << endl;
        for(auto const& port: conn.second) {
            cout << "   - " << port.name << endl;
        }
    }

    cout << "Types:" << endl;
    for(auto& type: component_type_map) {
        cout << type.first << endl;
    }
}

std::map<std::string, ComponentType> Arxml::getComponentTypes() {
    string type(APPLICATION_SW_COMPONENT_TYPE);
    auto xml_nodes = find_nodes_of_type(doc, type);

    map<string, ComponentType> result;
    for (auto& node : xml_nodes) {
        ComponentType comp;
        comp.name = node->first_node(SHORT_NAME)->value();
        result.insert(pair<string, ComponentType> (get_autosar_path_of_node(*node), comp));
    }

    return result;
}

Arxml::~Arxml() {

}

void Arxml::findPorts() {
    string package_name;
    xml_node<> *ports;

    xml_node<> *composition = doc.first_node("AUTOSAR")->first_node("AR-PACKAGES");

    for (xml_node<> *child = composition->first_node("AR-PACKAGE"); child; child = child->next_sibling()) {
        package_name = child->first_node("SHORT-NAME")->value();
        xml_node<> *package = child->first_node("ELEMENTS");
        for (xml_node<> *applType = package->first_node("APPLICATION-SW-COMPONENT-TYPE"); applType; applType = applType->next_sibling()) {
            auto typeName = package_name + "/" + applType->first_node("SHORT-NAME")->value();
            vector<Port> vPorts;

            ports = applType->first_node("PORTS");

            for (xml_node<> *port = ports->first_node(); port; port = port->next_sibling()) {

                if(strcmp(port->name(), "P-PORT-PROTOTYPE") == 0) {
                    PPort tmp;
                    tmp.name = port->first_node("SHORT-NAME")->value();
                    tmp.provInterface = port->first_node("PROVIDED-INTERFACE-TREF")->value();
                    vPorts.push_back(tmp);
                }
                if(strcmp(port->name(), "R-PORT-PROTOTYPE") == 0) {
                    RPort tmp;
                    tmp.name = port->first_node("SHORT-NAME")->value();
                    tmp.reqInterface = port->first_node("REQUIRED-INTERFACE-TREF")->value();
                    vPorts.push_back(tmp);
                }
            }
            connections.insert( pair<string, vector<Port>>(typeName, vPorts) );
        }
    }
}

vector<Component> Arxml::findComponents(xml_node<> *composition) {

    Component tmp_component;
    ComponentType tmp_type;
    string composition_name = composition->first_node("SHORT-NAME")->value();
    xml_node<> *component_node = composition->first_node("COMPONENTS");

    vector<Component> components;
    for (xml_node<> *child = component_node->first_node("SW-COMPONENT-PROTOTYPE"); child; child = child->next_sibling()) {
        auto component_name = child->first_node("SHORT-NAME")->value();
        tmp_component.name = component_name;
        
        auto type = child->first_node("TYPE-TREF")->value();
        tmp_type.name = type;
        tmp_component.type = tmp_type;

        components.push_back(tmp_component);
    }
    return components;
}

void Arxml::findCompositions() {

    Composition tmp_composition;
    string package_name;

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

    string package_name;
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


    vector<Component> components;
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
