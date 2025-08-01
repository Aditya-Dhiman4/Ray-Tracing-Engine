#pragma once

class Interval
{
    public:
        double min, max;

        Interval() : min(+infinity), max(-infinity) {}
        Interval(double min, double max) : min(min), max(max) {}

        double size()
        {
            return max - min;
        }

        bool contains(double x) const
        {
            return x >= min && x <= max;
        }

        bool surrounds(double x) const
        {
            return x > min && x < max;
        }

        double clamp(double x) const
        {
            if (x < min) return min;
            if (x > max) return max;
            return x;
        }

        static const Interval empty, universe;
};

const Interval Interval::empty = Interval(+infinity, -infinity);
const Interval Interval::universe = Interval(-infinity, +infinity);
