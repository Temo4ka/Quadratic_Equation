#include <string>
//! /!-------------------------------------------------------------------------------
//! \brief This program solves quadratic equation ax^2 + bx + c = 0
//! \author Artemy Bukin
//! \param [in] a, b, c coefficients of equation
//! \param [out] numberOfRoots numbers of roots
//! \param [out] x1, x2 roots
//!
//!-------------------------------------------------------------------------------
#include "equation.h"

int main(int argc, char *argv[]) {

    system(("chcp " + std::to_string(CP_UTF8)).c_str());
    if (argc > 1 && !strcmp(argv[1], "--test")) {
        unitTest();
        return 0;
    }

    Coefficients equation = {};
    if (getEquation(&equation)) {
        fprintf(stderr, "U, clown, take ur symbols and getEquation away\n");
        return EXIT_FAILURE;
    }

    Solution solution = {};

    solveQuadratic(&equation, &solution);
    printSolution(&solution);

    return 0;
}


bool isZero(const double x){

    return abs(x) < EPS;
}

bool getEquation(Coefficients *equation){

    assert(equation != nullptr);

    printf("Enter three numbers(a, b, c) without anything else:\n");
    for (int i = 0; i < 5; i++)
        if (scanf("%lf %lf %lf", &equation -> a, &equation-> b, &equation -> c) != 3 || getchar() != '\n') {
            cashCleaner();
            printf("Please reenter three numbers:\n");
        } else
            return false;
    return true;
}

void cashCleaner(){
    while (getchar() != '\n')
        ;
}

void printSolution(const Solution *solution){

    assert(solution != nullptr);

    switch(solution -> numberOfRoots) {
        case NoRoots:
            printf("0 roots\n");
            break;

        case OneRoot:
            printf("1 root: %lf\n", solution->x1);
            break;

        case Infinity:
            printf("Infinite amount of roots\n");
            break;

        case TwoRoots:
            printf("2 roots: x1 = %lg, x2 = %lg \n", solution->x1, solution->x2);
            break;

        default: printf("Error number of roots: %d\n", solution -> numberOfRoots);
    }
}

void solveQuadratic(const Coefficients *equation, Solution *solution){

    assert(equation != nullptr);
    assert(solution != nullptr);

    double d = equation -> b * equation -> b - 4 * equation -> a * equation -> c;
    if (isZero(equation -> a)) {
        solveLine(equation, solution);
        return;
    }
    if (isZero(d)) {
        solution -> x1 = -equation -> b / (2 * equation -> a);
        solution -> x2 = -equation -> b / (2 * equation -> a);
        solution -> numberOfRoots = OneRoot;
    } else if (d > 0) {
        solution -> x1 = (-equation -> b - sqrt(d)) / (2 * equation -> a);
        solution -> x2 = (-equation -> b + sqrt(d)) / (2 * equation -> a);
        solution -> numberOfRoots = TwoRoots;
    } else {
        solution -> numberOfRoots = NoRoots;
        solution -> x1 = 0;
        solution -> x2 = 0;
    }
}

void solveLine(const Coefficients *equation, Solution *solution){

    assert(equation != nullptr);
    assert(solution != nullptr);

    if (isZero(equation -> b)) {
        solution -> numberOfRoots = ((isZero(equation -> c)) ? Infinity : NoRoots);
        solution -> x1 = 0;
        solution -> x2 = 0;
        return;
    }
    solution -> numberOfRoots = OneRoot;
    solution -> x1 = -equation -> c / equation -> b;
    solution -> x2 = solution ->  x1;
}


//find modifier to print float pointing numbers with appropriate accuracy