#include "RandomInt.h"
#include <random>

int RandomInt(const int & from, const int & to)
{
    std::default_random_engine e(std::random_device{}());
    return  std::uniform_int_distribution<>(from, to)(e);
}
