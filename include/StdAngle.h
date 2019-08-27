#ifndef STDANGLE_H
#define STDANGLE_H



class StdAngle
{
    public:
        StdAngle() = delete;
        StdAngle(const StdAngle& other) = delete;
        StdAngle& operator=(const StdAngle& other) = delete;

        static constexpr double PI = 3.1415926535897;

        static float CalculateStdAngle(int Degrees);
};

#endif // STDANGLE_H
