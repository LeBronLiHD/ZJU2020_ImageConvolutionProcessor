#ifndef RANDOMMATRIX_H
#define RANDOMMATRIX_H

#include <random>
#include <stdlib.h>

// or: using std::default_random_engine;
//     // 随机数引擎
// or: using std::uniform_real_distribution;
//     // 连续均匀分布类模板

class RandomMatrixConvolution
{
private:

public:
    RandomMatrixConvolution(){}

    ~RandomMatrixConvolution(){}

    long double generatorRandomDouble()
    {
        // or: default_random_engine engine;
        //     uniform_real_distribution<double> range(0,2);
        //     long double res = range(engine);
        long double res = rand();
        while(!(res > 0 && res < 20000))
        {
            res = rand();
            // 0~RAND_MAX(32767)
            // 可以使用 void srand(unsigned int seed); srand(time(NULL));
            // 更新种子
        }
        return res/10000.0; // 限定卷积核元素0~2
    }
};

#endif // RANDOMMATRIX_H
