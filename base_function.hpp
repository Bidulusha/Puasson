#pragma once

#include <cmath>
#include <matplot/matplot.h>


namespace plt = matplot;


struct func {
    #ifndef PUASSON_2
    static inline double f(double x, double y) {
        return y - x;
    }
    
    static inline double f1(double x, double y) {
        return exp(y) + y * y;  
    }
    
    static inline double f2(double x, double y) {
        return ((f4(3,0)-f3(3,0)) / 3) * y + f3(3, 0);
    }
    
    static inline double f3(double x, double y) {
        return 1 - x * x * x;
    }
    
    static inline double f4(double x, double y) {
        return x * x + f1(0, 3);
    }
    #endif

    #ifdef PUASSON_2
    static inline double f(double x, double y) {
        return sin(x) - cos(y);
    }

    static inline double f1(double x, double y) {
        return 1 - y * y;  
    }
    
    static inline double f2(double x, double y) {
        return y + f3(3, 0);
    }
    
    static inline double f3(double x, double y) {
        return sin(x) + f1(0, 0);
    }
    
    static inline double f4(double x, double y) {
        return ((f2(3,3) - f1(0, 3))/3) * x + f1(0,3);
    }
    #endif

    static void draw_plots(double a, double b, double step, int N, bool draw_f = true) {
        // f(x, y) 
        auto [X, Y] = plt::meshgrid(plt::iota(a, step, b));
        auto Z = plt::transform(
            X, Y, func::f
        );

        // f1(x, y)
        auto x1 = std::vector<double>(N, 0);
        auto y1 = plt::iota(a, step, b);
        auto z1 = plt::transform(
            x1, y1, func::f1
        );

        // f2(x,y)
        auto x2 = std::vector<double>(N, b);
        auto y2 = plt::iota(a, step, b);
        auto z2 = plt::transform(
            x2, y2, func::f2
        );

        // f3(x, y)
        auto x3 = plt::iota(a, step, b);
        auto y3 = std::vector<double>(N, 0);
        auto z3 = plt::transform(
            x3, y3, func::f3
        );

        // f4(x, y)
        auto x4 = plt::iota(a, step, b);
        auto y4 = std::vector<double>(N, b);
        auto z4 = plt::transform(
            x4, y4, func::f4
        );

        // Make plot
        plt::plot3(x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
        if (draw_f) {
            plt::hold(plt::on);
            plt::meshz(X, Y, Z)->palette_map_at_surface(true).face_alpha(0.5);
        }

        plt::xlabel("x");
        plt::ylabel("y");
        plt::zlabel("z");

        // Show
        plt::show();
    }
};