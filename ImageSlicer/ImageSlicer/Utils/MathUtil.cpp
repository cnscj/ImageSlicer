#include "MathUtil.h"
#include <cmath>

template<typename T>
T MathUtil::limit(T src, T min, T max)
{
    src = (src > max) ? max : src;
    src = (src < min) ? min : src;
    return src;
}

MathUtil::MathUtil()
{

}
