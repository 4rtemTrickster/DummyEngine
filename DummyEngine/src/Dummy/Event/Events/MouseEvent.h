#pragma once

#include "DEpch.h"

#include "Dummy/Event/Event.h"

namespace Dummy
{
    class DUMMY_API MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(ET_MoseMoved)
        EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)

    private:
        float m_MouseX;
        float m_MouseY;
    };

    class DUMMY_API MouseScrollEvent : public Event
    {
    public:
        MouseScrollEvent(float xOffest, float yOffset)
            : m_XOffset(xOffest), m_YOffset(yOffset) {}

        float GetXOffset() const { return m_XOffset; }
        float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrollEvent: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }

        EVENT_CLASS_TYPE(ET_MouseScrolled)
        EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)

    private:
        float m_XOffset;
        float m_YOffset;
    };

    class DUMMY_API MouseButtonEvent : public Event
    {
    public:
        int GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EC_Mouse | EC_Input)
    protected:

        MouseButtonEvent(int button) : m_Button(button) {}
        
        int m_Button;
    };

    class DUMMY_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(ET_MouseButtonPressed)
    };

    class DUMMY_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(ET_MouseButtonReleased)
    };
}
