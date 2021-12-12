#pragma once

namespace Dummy
{
    class Timestep
    {
    public:
        Timestep(float time = 0.0f) : Time(time) {}

        operator float() const { return Time; }

        float GetSeconds() const { return Time; }
        float GetMilliseconds() const { return Time * 1000.0f; }
    protected:
        float Time;
    };
}
