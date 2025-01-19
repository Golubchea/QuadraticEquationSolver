#include <QuadraticEquationSolver/QuadraticEquationSolver.h>
#include <cmath>
#include <stdexcept>

std::pair<std::optional<double>, std::optional<double> > QuadraticEquationSolver::solve(double A,
                                                                                        double B,
                                                                                        double C)
{
    if (!std::isfinite(A) || !std::isfinite(B) || !std::isfinite(C)) {
        throw std::invalid_argument("Invalid coefficients: A, B, or C is NaN or infinity.");
    }
    double discriminant = B * B - 4 * A * C;
    if (discriminant > 0) {
        if (std::fabs(A) < gQESepsilon) {
            throw std::invalid_argument("Division by nearly zero coefficient A.");
        }
        const double sqrt_discriminant = std::sqrt(discriminant);
        const double x1 = (-B + sqrt_discriminant) / (2 * A);
        const double x2 = (-B - sqrt_discriminant) / (2 * A);
        return {x1, x2};
        //D==0
    } else if (std::fabs(discriminant) <= gQESepsilon) {
        if (std::fabs(A) < gQESepsilon) {
            throw std::invalid_argument("Division by nearly zero coefficient A.");
        }
        //возможно будет быстрее fabs
        //((unsigned long long *) (&discriminant & 0x7FFFFFFFFFFFFFFF)
        // < QuadraticEquationSolver::gQESepsilon) {
        // Дискриминант практически равен нулю
        const double x1 = (-B) / (2 * A);
        return {x1, x1};
    } else {
        return {std::nullopt, std::nullopt};
    }
}
