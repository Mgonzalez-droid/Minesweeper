#ifndef Random_h
#define Random_h

#include <random>

class Random{
    
    static std::mt19937 random;
    
public:
    static int Int(int min, int max);
    static float Float(float min, float max);
};

#endif /* Random_h */
