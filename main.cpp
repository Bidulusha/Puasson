#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <matplot/matplot.h>
#include <format>
#include <chrono>

#ifdef OMP_VERSION
#include <omp.h>
#endif

#include <fraction>
#include <matrix.hpp>

#include <base_function.hpp>

namespace plt = matplot;
namespace chr = std::chrono;

int main() {
    // const double a = 0, b = 3, step = .5;
    // const int N = (b - a) / step + 1;

    const int N = 30;
    const double a = 0, b = 3, step = (b - a) / (N - 1);
    // func::draw_plots(a, b, step, N, false);
    auto start = chr::system_clock::now();
    
    Matrix U(N, N, 1);
    Matrix A((N-2)*(N-2), (N-2)*(N-2));
    Matrix B((N-2)*(N-2), 1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == 0) {
                U[i][j] = func::f3(j * step + a, a);
            } 
            else if (i == N - 1) {
                U[i][j] = func::f4(j * step + a, b);
            }
            else {
                U[i][0] = func::f1(a, i * step + a);
                U[i][N-1] = func::f2(b, i * step + a);
            }
        }
    }
    // std::cout << U << std::endl;
    // std::cout << A << std::endl;
    // std::cout << B << std::endl;

    double h1 = 1 / (step * step);
    int m = N - 2;

    for (int i = 1; i < N - 1; i++) {
        for (int j = 1; j < N - 1; j++) {
            int idx =  (i - 1) * m + j - 1;
            int idx_top     = idx - m;
            int idx_bot     = idx + m;
            int idx_left    = idx - 1;
            int idx_rigth   = idx + 1;

            if (i == 1) {
                B[idx][0] -= U[0][j];
            }
            else {
                A[idx][idx_top] = 1;
            }

            if (j == 1) {
                B[idx][0] -= U[i][0];
            }
            else {
                A[idx][idx_left] = 1;
            }

            if (i == N - 2) {
                B[idx][0] -= U[N-1][j];
            }
            else {
                A[idx][idx_bot] = 1;
            }
            if (j == N - 2) {
                B[idx][0] -= U[i][N-1];
            }
            else {
                A[idx][idx_rigth] = 1;
            }
            A[idx][idx] = -4;
            B[idx][0] += func::f(j * step + a, i * step + a) / h1; // OR MINUS, IDK
        }
    }

    // std::cout << A << std::endl;
    // std::cout << B << std::endl;
    
    
    try {
        Matrix ans = A.gauss_method(B);
        Matrix vis_ans(U);
        // std::cout << ans << std::endl;

        #ifdef OMP_VERSION
        #pragma omp parallel for num_threads(NUM_THREADS)
        #endif
        for (int i = 0; i < ans.csize(); i++) {
            // std::cout << 1 + i / (N-2) << " " << 1 + i % (N-2) << std::endl; 
            vis_ans[1 + i / (N-2)][1 + i % (N-2)] = ans[i][0];
        }
        
        // std::cout << vis_ans << std::endl;
        auto diff = chr::system_clock::now() - start;
        std::cout << "Time of execution: " << std::setprecision(9) << 1.0 * chr::duration_cast<chr::nanoseconds>(diff).count() / 1e9 << std::endl;

        auto [X, Y] = plt::meshgrid(plt::iota(a, step, b));
        plt::meshz(X, Y, vis_ans.get_matrix())->palette_map_at_surface(true).face_alpha(0.5);
        // plt::hold(plt::on);
        // func::draw_plots(a, b, step, N);
        plt::show();
        
    } catch(char const* err) {
        std::cout << err << std::endl;
    }

    
    return 0;
}