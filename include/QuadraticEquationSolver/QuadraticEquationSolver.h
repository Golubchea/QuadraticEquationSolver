#pragma once

#include <optional>
#include <utility>

namespace QuadraticEquationSolver {

constexpr double gQESepsilon = 1e-24;

std::pair<std::optional<double>, std::optional<double>> solve(double A, double B, double C);

} // namespace QuadraticEquationSolver
