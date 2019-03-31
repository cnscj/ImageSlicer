#ifndef MATHUTIL_H
#define MATHUTIL_H


class MathUtil
{
public:
    template<typename T>
    static T limit(T src, T min, T max);
private:
    MathUtil();
};

#endif // MATHUTIL_H
