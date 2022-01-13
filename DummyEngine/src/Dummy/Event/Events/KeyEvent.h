#pragma once

#include "DEpch.h"

#include "Dummy/Event/Event.h"

namespace Dummy
{
    class DUMMY_API KeyEvent : public Event
    {
    public:
        int GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EC_Keyboard | EC_Input)

    protected:
        KeyEvent(int keycode) : m_KeyCode(keycode) {}

        int m_KeyCode;
        
    };

    class DUMMY_API KeyPressedEvent : public KeyEvent
    {
    public:
        KeyPressedEvent(int keycode, int repeatCount)
            : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

        int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(ET_KeyPressed)

    private:
       int m_RepeatCount;
    };

    class DUMMY_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(ET_KeyReleased)
    };

    class DUMMY_API KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_KeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(ET_KeyTyped)
    };
}
