#include "inputManager.h"


InputManager::InputManager()
{
}

void InputManager::Update()
{
    previousKeys = currentKeys;
    previousMouseButtons = currentMouseButtons;

    // Keyboard
    for (int key = 0; key < KEY_COUNT; key++)
    {
        currentKeys[key] = ::IsKeyDown(key);
    }

    // Mouse buttons
    for (int button = 0; button < MOUSE_BUTTON_COUNT; button++)
    {
        currentMouseButtons[button] = ::IsMouseButtonDown(button);
    }

    mousePosition = ::GetMousePosition();
    mouseDelta = ::GetMouseDelta();

    mouseWheelMove = ::GetMouseWheelMove();

    deltaTime = ::GetFrameTime();
}


// Keyboard

bool InputManager::IsKeyDown(int key) const
{
    return currentKeys[key];
}

bool InputManager::IsKeyPressed(int key) const
{
    return currentKeys[key] && !previousKeys[key];
}

bool InputManager::IsKeyReleased(int key) const
{
    return !currentKeys[key] && previousKeys[key];
}


// Mouse

bool InputManager::IsMouseButtonDown(int button) const
{
    return currentMouseButtons[button];
}

bool InputManager::IsMouseButtonPressed(int button) const
{
    return currentMouseButtons[button] &&
          !previousMouseButtons[button];
}

bool InputManager::IsMouseButtonReleased(int button) const
{
    return !currentMouseButtons[button] &&
            previousMouseButtons[button];
}


// Getters

Vector2 InputManager::GetMousePosition() const
{
    return mousePosition;
}

Vector2 InputManager::GetMouseDelta() const
{
    return mouseDelta;
}

float InputManager::GetMouseWheelMove() const
{
    return mouseWheelMove;
}

float InputManager::GetFrameTime() const
{
    return deltaTime;
}



