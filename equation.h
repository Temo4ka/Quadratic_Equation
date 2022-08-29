#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include <cmath>
#include <windows.h>
#include <iostream>

const double EPS            =  1e-14;
const char   TESTFILENAME[] =  "tests.txt";
const char   SETRED[]       =  "\033[0;31m";
const char   SETNONE[]      =  "\033[0;0m";
const char   SETGREEN[]     =  "\033[0;32m";

enum RootsNumber {
    Infinity  = -1,
    NoRoots   =  0,
    OneRoot   =  1,
    TwoRoots  =  2,
};

//!-------------------------------------------------------------------------------
//! \brief This structure contains coefficients of equation
//!
//!-------------------------------------------------------------------------------
struct Coefficients {
    double a = NAN;
    double b = NAN;
    double c = NAN;
};

//!-------------------------------------------------------------------------------
//! \brief This structure contains number of roots and roots
//!
//!-------------------------------------------------------------------------------
struct Solution {
    int numberOfRoots = NoRoots;
    double x1 = NAN;
    double x2 = NAN;
};

//!-------------------------------------------------------------------------------
//! \brief This structure is made for tests
//!
//!-------------------------------------------------------------------------------
struct Test {
    Coefficients coefficients = {};
    Solution     wantSolution = {};
};

//!-------------------------------------------------------------------------------
//! \brief This function checks if input variable equals zero
//!
//!-------------------------------------------------------------------------------
bool isZero(const double x);

//!-------------------------------------------------------------------------------
//! \brief This procedure checks if the input test was solved properly
//!
//!-------------------------------------------------------------------------------
bool checkTest(const Test *test, size_t testNumber, size_t k);

//!-------------------------------------------------------------------------------
//! \brief This procedure solves quadratic equation
//! \param [in] equation coefficients of equation
//! \param [out] solution solution of equation
//!
//!-------------------------------------------------------------------------------
void solveQuadratic(const Coefficients *equation, Solution *solution);

//!-------------------------------------------------------------------------------
//! \brief This procedure solves linear equation
//! \param [in] equation coefficients of equation
//! \param [out] solution solution of equation
//!
//!-------------------------------------------------------------------------------
void solveLine(const Coefficients *equation, Solution *solution);

//!-------------------------------------------------------------------------------
//! \brief This procedure prints the solution of equation
//! \param [in] solution solution of equation
//!
//!-------------------------------------------------------------------------------
void printSolution(const Solution *solution);

//!-------------------------------------------------------------------------------
//! \brief This function gets the coefficients of equation from input
//! \param [out] equation coefficients of equation
//!
//!-------------------------------------------------------------------------------
bool getEquation(Coefficients *equation);

//!-------------------------------------------------------------------------------
//! \brief This function checks if test was solved correctly
//! \param [in] wantSolution true solution of the test
//! \param [in] solution solution given by the program
//!
//!-------------------------------------------------------------------------------
bool isEqualSolutions(Solution *wantSolution, Solution *solution);

//!-------------------------------------------------------------------------------
//! \brief This procedure checks some prepared test in order to find mistakes
//!
//!-------------------------------------------------------------------------------
void unitTest();

//!-------------------------------------------------------------------------------
//! \brief This procedure clears input data in case it is incorrect
//!
//!-------------------------------------------------------------------------------
void cashCleaner();

//!-------------------------------------------------------------------------------
//! \brief This procedure reads tests from txt file
//!
//!-------------------------------------------------------------------------------
size_t readFromFile(Test **fileTests, FILE *testFile);