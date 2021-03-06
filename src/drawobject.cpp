#include "drawobject.h"
#include "arxmlparser.h"

#define COMPONENT_SIZE_X 200
#define COMPONENT_SIZE_Y 100
#define COMPONENT_PADDING_X 50
#define COMPONENT_PADDING_Y 25

#define COMPOSITION_COLOUR wxColor(190,255,225)
#define COMPONENT_COLOUR wxColor(220,220,220)
DrawObject::DrawObject(const Arxml& arxml) {
    const Composition* root_comp = arxml.getComposition();
    name = root_comp->name;

    for (auto &component : root_comp->components) {
        addChild(new DrawObject(component));
    }
}

DrawObject::DrawObject(const Component& component) {
    name = component.name;
    type = component.type;
}

void DrawObject::addChild(DrawObject* child) {
    children.push_back(child);
}

const std::string& DrawObject::getName() const {
    return name;
}

const std::string& DrawObject::getInfo() const {
    return type.name;
}

const std::vector<DrawObject*>& DrawObject::getChildren() const {
    return children;
}

struct RectangleSize {
    int x;
    int y;
    int nbr_row_col;
};

RectangleSize calculateRectangleSize(const DrawObject& draw_object, int text_height) {
    int nbr_children = draw_object.getChildren().size();
    int iRoot = static_cast<int>(sqrt(static_cast<float>(nbr_children)) + .5f); // Calculate the closest integer square root

    // Ensure we can always fit the number of children into the packaged structure
    if (iRoot*iRoot < nbr_children)
        iRoot++;

    RectangleSize rect_size = RectangleSize {COMPONENT_SIZE_X, COMPONENT_SIZE_Y, iRoot};

    if (iRoot > 0) {
        rect_size.x = iRoot*COMPONENT_SIZE_X + (iRoot+1)*COMPONENT_PADDING_X;
        rect_size.y = iRoot*COMPONENT_SIZE_Y + (iRoot+1)*COMPONENT_PADDING_Y + text_height;
    }
    return rect_size;
}

void DrawObject::draw(wxDC& dc, int x, int y) {

    // Draw name
    auto name_text = wxString(this->getName());
    wxSize text_size = dc.GetTextExtent(name_text);
    auto rect_size = calculateRectangleSize(*this, text_size.GetHeight());

    // Draw Rectangle
    if (rect_size.nbr_row_col > 0)
        dc.SetBrush(COMPOSITION_COLOUR);
    else
        dc.SetBrush(COMPONENT_COLOUR);
    dc.SetPen( wxPen(wxColor(0,0,0), 5));
    dc.DrawRectangle(x, y, rect_size.x, rect_size.y);

    int name_text_pos_x = x + rect_size.x/2 - text_size.GetWidth()/2;
    int name_text_pos_y = y + 10;
    dc.DrawText(name_text, name_text_pos_x, name_text_pos_y);

    // Draw info

    wxFont font(8, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxFont default_font = dc.GetFont();
    dc.SetFont(font);

    auto info_text = wxString(this->getInfo());
    wxSize info_size = dc.GetTextExtent(info_text);
        
    int info_text_pos_x = x + rect_size.x/2 - info_size.GetWidth()/2;
    int info_text_pos_y = y + 25;
    dc.DrawText(info_text, info_text_pos_x, info_text_pos_y);


    dc.SetFont(default_font);

    // Store position and size
    start_x = x;
    start_y = y;
    end_x = x + rect_size.x;
    end_y = y + rect_size.y;

    // Draw Children
    int child_y = -1;
    for (uint i = 0; i < children.size(); ++i) {
        DrawObject* child = children[i];
        int child_x = i%rect_size.nbr_row_col;
        if (child_x == 0)
            child_y++;

        int x_pos = x + COMPONENT_PADDING_X + (COMPONENT_PADDING_X + COMPONENT_SIZE_X)*child_x;
        int y_pos = y + text_size.GetHeight() + COMPONENT_PADDING_Y + (COMPONENT_PADDING_Y + COMPONENT_SIZE_Y)*child_y;

        child->draw(dc, x_pos, y_pos);
    }
}

DrawObject* DrawObject::getComponentUnderCursor(wxPoint& cursor_position) {
    DrawObject* matching_component = nullptr;

    if (cursor_position.x < start_x || cursor_position.x > end_x)
        return matching_component;
    if (cursor_position.y < start_y || cursor_position.y > end_y)
        return matching_component;

    matching_component = this;

    for (auto& child : children) {
        DrawObject* matching_child = child->getComponentUnderCursor(cursor_position);
        if (matching_child)
            matching_component = matching_child;
    }
    return matching_component;
}

const std::vector<Port>& DrawObject::getPorts() const {
    return type.ports;
}