//
// Created by 黄志鸿 on 2022/10/31.
//

#ifndef SKIPLIST_TOOLS_H
#define SKIPLIST_TOOLS_H

#include <random>

class Random_int_generator {
public:
    static Random_int_generator& get_instance() {
        static Random_int_generator instance;
        return instance;
    }

    int random_int(int ub, double p) {
        std::uniform_int_distribution<double> r(0.0, 1.0);
        int res = 1;
        while(r(rd) < p && res < ub) {
            ++ res;
        }
        return res;
    }

    Random_int_generator(const Random_int_generator &rhs) = delete;
    Random_int_generator(const Random_int_generator &&rhs) = delete;

    Random_int_generator& operator= (const Random_int_generator &rhs) = delete;
    Random_int_generator& operator= (const Random_int_generator &&rhs) = delete;


private:
    Random_int_generator() = default;
    ~Random_int_generator() = default;

    std::random_device rd;
};

#endif //SKIPLIST_TOOLS_H
