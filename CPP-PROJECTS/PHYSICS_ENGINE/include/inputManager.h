#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <array>
#include <raylib.h>


class InputManager
{
private:

    static constexpr int KEY_COUNT = KEY_KB_MENU + 1;
    static constexpr int MOUSE_BUTTON_COUNT = 8;

    std::array<bool, KEY_COUNT> currentKeys{};
    std::array<bool, KEY_COUNT> previousKeys{};

    std::array<bool, MOUSE_BUTTON_COUNT> currentMouseButtons{};
    std::array<bool, MOUSE_BUTTON_COUNT> previousMouseButtons{};

    Vector2 mousePosition{};
    Vector2 mouseDelta{};

    float mouseWheelMove = 0.0f;
    float deltaTime = 0.0f;

public:

    InputManager();

    void Update();

    // Keyboard
    bool IsKeyDown(int key) const;
    bool IsKeyPressed(int key) const;
    bool IsKeyReleased(int key) const;

    // Mouse
    bool IsMouseButtonDown(int button) const;
    bool IsMouseButtonPressed(int button) const;
    bool IsMouseButtonReleased(int button) const;

    Vector2 GetMousePosition() const;
    Vector2 GetMouseDelta() const;
    float GetMouseWheelMove() const;

    float GetFrameTime() const;
};



#endif
