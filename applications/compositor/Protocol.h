#pragma once

#include <libgraphic/Shape.h>
#include <libwidget/Cursor.h>
#include <libwidget/Event.h>

enum CompositorMessageType
{
    COMPOSITOR_MESSAGE_INVALID,
    COMPOSITOR_MESSAGE_ACK,
    COMPOSITOR_MESSAGE_GREETINGS,
    COMPOSITOR_MESSAGE_EVENT,
    COMPOSITOR_MESSAGE_CHANGED_RESOLUTION,

    COMPOSITOR_MESSAGE_CREATE_WINDOW,
    COMPOSITOR_MESSAGE_DESTROY_WINDOW,
    COMPOSITOR_MESSAGE_RESIZE_WINDOW,
    COMPOSITOR_MESSAGE_MOVE_WINDOW,
    COMPOSITOR_MESSAGE_FLIP_WINDOW,
    COMPOSITOR_MESSAGE_EVENT_WINDOW,
    COMPOSITOR_MESSAGE_CURSOR_WINDOW,
    COMPOSITOR_MESSAGE_SET_RESOLUTION,
    COMPOSITOR_MESSAGE_SET_WALLPAPER,

    COMPOSITOR_MESSAGE_GET_MOUSE_POSITION,
    COMPOSITOR_MESSAGE_MOUSE_POSITION,
};

#define WINDOW_NONE (0)
#define WINDOW_BORDERLESS (1 << 0)
#define WINDOW_RESIZABLE (1 << 1)
#define WINDOW_ALWAYS_FOCUSED (1 << 2)
#define WINDOW_SWALLOW (1 << 3)
#define WINDOW_TRANSPARENT (1 << 4)
#define WINDOW_NO_FOCUS (1 << 5)

typedef unsigned int WindowFlag;

enum WindowType
{
    WINDOW_TYPE_POPOVER,
    WINDOW_TYPE_PANEL,
    WINDOW_TYPE_DIALOG,
    WINDOW_TYPE_REGULAR,
    WINDOW_TYPE_DESKTOP,
};

struct CompositorGreetings
{
    Rectangle screen_bound;
};

struct CompositorEvent
{
    Event event;
};

struct CompositorCreateWindow
{
    int id;
    WindowFlag flags;
    WindowType type;

    int frontbuffer;
    Vec2i frontbuffer_size;
    int backbuffer;
    Vec2i backbuffer_size;

    Rectangle bound;
};

struct CompositorDestroyWindow
{
    int id;
};

struct CompositorResizeWindow
{
    int id;

    Rectangle bound;
};

struct CompositorMoveWindow
{
    int id;

    Vec2i position;
};

struct CompositorFlipWindow
{
    int id;

    int frontbuffer;
    Vec2i frontbuffer_size;
    int backbuffer;
    Vec2i backbuffer_size;

    Rectangle bound;
};

struct CompositorEventWindow
{
    int id;

    Event event;
};

struct CompositorCursorWindow
{
    int id;

    CursorState state;
};

struct CompositorSetResolution
{
    int width;
    int height;
};

struct CompositorSetWallaper
{
    int wallpaper;
    Vec2i resolution;
};

struct CompositorChangedResolution
{
    Rectangle resolution;
};

struct CompositorMousePosition
{
    Vec2i position;
};

struct CompositorMessage
{
    CompositorMessageType type;

    union
    {
        CompositorGreetings greetings;
        CompositorEvent event;
        CompositorCreateWindow create_window;
        CompositorDestroyWindow destroy_window;
        CompositorResizeWindow resize_window;
        CompositorMoveWindow move_window;
        CompositorFlipWindow flip_window;
        CompositorEventWindow event_window;
        CompositorCursorWindow cursor_window;
        CompositorSetResolution set_resolution;
        CompositorSetWallaper set_wallaper;
        CompositorChangedResolution changed_resolution;

        CompositorMousePosition mouse_position;
    };
};
