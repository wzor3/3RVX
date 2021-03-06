// Copyright (c) 2015, Matthew Malensek.
// Distributed under the BSD 2-Clause License (see LICENSE.txt for details)

#pragma once

#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus.lib")

#include "../Window.h"

class D3DDevice;

class LayeredWnd : public Window {
public:
    LayeredWnd(LPCWSTR className, LPCWSTR title, HINSTANCE hInstance = NULL,
        Gdiplus::Bitmap *bitmap = NULL, DWORD exStyles = NULL);
    ~LayeredWnd();

    virtual bool AlwaysOnTop();
    virtual void AlwaysOnTop(bool onTop);

    virtual Gdiplus::Bitmap *Bitmap();
    virtual void Bitmap(Gdiplus::Bitmap *bitmap);

    /// <summary>
    /// Enables the blurred 'glass' background available on Vista and Windows 7.
    /// Has no effect on other Windows versions.
    /// </summary>
    /// <param name="mask">
    /// Bitmap that defines the region that should show glass. Black pixels will
    /// reveal the glass effect underneath, whereas white pixels obscure the
    /// glass.
    /// </param>
    /// <returns>true if successful, false otherwise.</returns>
    virtual bool EnableGlass(Gdiplus::Bitmap *mask);

    /// <summary>Disables the blurred glass effect.</summary>
    virtual bool DisableGlass();

    /// <summary>
    /// Reports whether this window displays when a full-screen application is
    /// focused.
    /// </summary>
    bool NoShowFullscreen();

    /// <summary>
    /// Sets whether this window should display when a full-screen application
    /// is focused.
    /// </summary>
    void NoShowFullscreen(bool enable);

    /// <summary>
    /// Reports whether this window displays when a DirectX application is
    /// focused and is occluding the screen. Basically, when a game or
    /// application has exclusive control of the display.
    /// </summary>
    bool NoShowD3DOccluded();

    /// <summary>
    /// Sets whether this window should display when a DirectX application
    /// is occluding the screen.
    /// </summary>
    void NoShowD3DOccluded(bool enable);

    virtual byte Transparency();
    virtual void Transparency(byte transparency);

    virtual void Show();
    virtual void Hide();

    int X();
    int Y();
    void X(int x);
    void Y(int y);

    int Width();
    int Height();

    POINT Position();
    void Position(int x, int y);

protected:
    bool _visible;
    POINT _location;
    SIZE _size;
    byte _transparency;

    Gdiplus::Bitmap *_bitmap;
    Gdiplus::Bitmap *_glassMask;

    bool _noShowFull;
    bool _noShowD3D;
    D3DDevice *_d3dDevice;

    /// <summary>
    /// Updates layered window properties. Called after the window bitmap
    /// changes.
    /// </summary>
    /// <param name="dirtyRect">
    /// If non-NULL, specifies a 'dirty region' of the window to update.
    /// Otherwise, the entire window is updated.
    /// </param>
    void UpdateWindow(RECT *dirtyRect = NULL);

    /// <summary>
    /// Updates the transparency level (0 - 255) of the window.
    /// </summary>
    void UpdateTransparency();
    void UpdateWindowPosition();

    virtual LRESULT WndProc(HWND hWnd, UINT message,
        WPARAM wParam, LPARAM lParam);
};