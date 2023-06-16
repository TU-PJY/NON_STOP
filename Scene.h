#pragma once

#include <Windows.h>

#include "Button.h"
#include "TextBox.h"


enum SceneID {
    Main, Game, Armory, Shop
};


class Scene {
protected:
    SceneID id;
    int horizontal_length;
    int vertical_length;
    RECT valid_area;

public:
    Scene(const SceneID& id);

protected:
    void drawBackground(const HDC& hdc, const COLORREF& color) const;
    virtual void draw(const HDC& hdc) const = 0;

public:
    virtual void show(const HDC& hdc) const;
    virtual void syncSize(const HWND& hWnd);
    SceneID getID() const;
    virtual int clickL(const POINT& point) const;
    virtual int clickR(const POINT& point) const;
};