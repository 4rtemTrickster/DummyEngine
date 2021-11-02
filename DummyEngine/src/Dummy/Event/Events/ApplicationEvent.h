#pragma once

#include "DEpch.h"

#include "../Event.h"


namespace Dummy
{
    class DUMMY_API WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height) {}

        unsigned int GetWidth() const { return m_Width; }
        unsigned int GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(ET_WindowResize)
        EVENT_CLASS_CATEGORY(EC_Application)

    private:
        unsigned int m_Width;
        unsigned int m_Height;
    };

    class DUMMY_API WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent() {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowCloseEvent";
            return ss.str();
        }

        EVENT_CLASS_TYPE(ET_WindowClose)
        EVENT_CLASS_CATEGORY(EC_Application)
    };

    class DUMMY_API AppTickEvent : public Event
    {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(ET_AppTick)
        EVENT_CLASS_CATEGORY(EC_Application)
    };

    class DUMMY_API AppUpdateEvent : public Event
    {
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(ET_AppUpdate)
        EVENT_CLASS_CATEGORY(EC_Application)
    };

    class DUMMY_API AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(ET_AppRender)
        EVENT_CLASS_CATEGORY(EC_Application)
    };
}
