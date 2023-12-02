#include "GUI.h"

bool spe::GUI::Button(const std::string& content)
{
    return ImGui::Button(content.c_str());
}

void spe::GUI::SetCursorCamera(const spe::Vector2& position)
{
    ImVec2 new_cursor = ImVec2(spe::GUI::s_ptr_Camera->Position.x * -1 + 960, 540 + spe::GUI::s_ptr_Camera->Position.y * -1);
    new_cursor.x += position.x;
    new_cursor.y -= position.y;
    
    ImGui::SetCursorPos(new_cursor);
}

void spe::GUI::SetCursor(const spe::Vector2& position)
{
    ImVec2 new_cursor = ImVec2(960, 540);
    new_cursor.x += position.x;
    new_cursor.y -= position.y;

    ImGui::SetCursorPos(new_cursor);
}

void spe::GUI::SetFontScale(float scale)
{
    ImGui::SetWindowFontScale(scale);
}

void spe::GUI::Window(const std::string& id, const spe::Vector2& pos, const spe::Vector2& size)
{
    ImGui::Begin(id.c_str(), NULL, DEFAULT_FLAGS);
    ImGui::SetWindowSize(spe::Vector2::toSFVector(size));
    ImGui::SetWindowPos(sf::Vector2f(960 + pos.x, 540 - pos.y));
}

void spe::GUI::End()
{
    ImGui::End();
}

const spe::Camera* spe::GUI::s_ptr_Camera = nullptr;