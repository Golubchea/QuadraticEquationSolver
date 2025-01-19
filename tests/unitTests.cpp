#include <QuadraticEquationSolver/QuadraticEquationSolver.h>
#include <gtest/gtest.h>

//3
// Тест на отсутствие действительных корней
TEST(QuadraticEquationSolverTest, NoRealRoots)
{
    auto result = QuadraticEquationSolver::solve(1, 0, 1);
    EXPECT_FALSE(result.first);
    EXPECT_FALSE(result.second);
}
//5
// Тест на корректное решение квадратного уравнения
TEST(QuadraticEquationSolverTest, twoRoots)
{
    auto result = QuadraticEquationSolver::solve(1.0, 0, -1.0);
    ASSERT_TRUE(result.first && result.second);
    EXPECT_NEAR(*result.first, 1.0, QuadraticEquationSolver::gQESepsilon);
    EXPECT_NEAR(*result.second, -1.0, QuadraticEquationSolver::gQESepsilon);
}

//7
// Тест на корректное решение квадратного уравнения
TEST(QuadraticEquationSolverTest, oneRoot)
{
    auto result = QuadraticEquationSolver::solve(1, 2, 1);
    ASSERT_TRUE(result.first && result.second);
    EXPECT_NEAR(*result.first, -1.0, QuadraticEquationSolver::gQESepsilon);
    EXPECT_NEAR(*result.second, -1.0, QuadraticEquationSolver::gQESepsilon);
}

//9
// Тест на выбрасывание исключения при делении на почти ноль
TEST(QuadraticEquationSolverTest, ThrowsOnNearlyZeroCoefficientA)
{
    EXPECT_THROW(QuadraticEquationSolver::solve(0, 1.0, 1.0), std::invalid_argument);
}
//11
// Тест для случая, когда дискриминант практически равен нулю
TEST(QuadraticEquationSolverTest, SolvesQuadraticEquationWithNearlyZeroDiscriminant)
{
    auto result = QuadraticEquationSolver::solve(1.0,
                                                 2.0,
                                                 1.0 + QuadraticEquationSolver::gQESepsilon);
    ASSERT_TRUE(result.first && result.second);
    EXPECT_NEAR(*result.first, -1.0, 1e-9);
    EXPECT_NEAR(*result.second, -1.0, 1e-9);
}
//13 Посмотреть какие еще значения могут принимать числа типа double, кроме числовых и
//написать тест с их использованием на все коэффициенты. solve должен выбрасывать исключение.
TEST(QuadraticEquationSolverTest, HandlesNaNCoefficients)
{
    double nan_value = std::numeric_limits<double>::quiet_NaN();
    EXPECT_THROW(QuadraticEquationSolver::solve(nan_value, 1.0, 1.0), std::invalid_argument);
    EXPECT_THROW(QuadraticEquationSolver::solve(1.0, nan_value, 1.0), std::invalid_argument);
    EXPECT_THROW(QuadraticEquationSolver::solve(1.0, 1.0, nan_value), std::invalid_argument);

    // Все коэффициенты NaN
    EXPECT_THROW(QuadraticEquationSolver::solve(nan_value, nan_value, nan_value),
                 std::invalid_argument);
}
//13
// Проверка на Infinity для всех коэффициентов
TEST(QuadraticEquationSolverTest, HandlesInfinityCoefficients)
{
    const double inf_value = std::numeric_limits<double>::infinity();
    const double neg_inf_value = -std::numeric_limits<double>::infinity();

    // Положительная бесконечность
    EXPECT_THROW(QuadraticEquationSolver::solve(inf_value, 1.0, 1.0), std::invalid_argument);
    EXPECT_THROW(QuadraticEquationSolver::solve(1.0, inf_value, 1.0), std::invalid_argument);
    EXPECT_THROW(QuadraticEquationSolver::solve(1.0, 1.0, inf_value), std::invalid_argument);

    // Отрицательная бесконечность
    EXPECT_THROW(QuadraticEquationSolver::solve(neg_inf_value, 1.0, 1.0), std::invalid_argument);
    EXPECT_THROW(QuadraticEquationSolver::solve(1.0, neg_inf_value, 1.0), std::invalid_argument);
    EXPECT_THROW(QuadraticEquationSolver::solve(1.0, 1.0, neg_inf_value), std::invalid_argument);

    // Смешанные случаи
    EXPECT_THROW(QuadraticEquationSolver::solve(inf_value, inf_value, inf_value),
                 std::invalid_argument);
    EXPECT_THROW(QuadraticEquationSolver::solve(neg_inf_value, neg_inf_value, neg_inf_value),
                 std::invalid_argument);
    EXPECT_THROW(QuadraticEquationSolver::solve(inf_value, neg_inf_value, inf_value),
                 std::invalid_argument);
}
