#include "equation.h"

void unitTest(){
    Test tests[] = {
            {{0, 0,  0 },  {Infinity, 0,  0 }},
            {{1, 0,  0 },  {OneRoot,  0,  0 }},
            {{0, 1,  0 },  {OneRoot,  0,  0 }},
            {{0, 0,  1 },  {NoRoots,  0,  0 }},
            {{1, 2,  1 },  {OneRoot,  -1, -1}},
            {{1, -5, 6 },  {TwoRoots, 2,  3 }},
            {{0, 2,  -4},  {OneRoot,  2,  2 }},
    };

    FILE *testFile = fopen(TESTFILENAME, "r");
    if (testFile == nullptr){
        printf("Error occurred during opening %s file\n", TESTFILENAME);
    }

    Test *fileTests = nullptr;
    size_t numberOfFileTests = readFromFile(&fileTests, testFile);

    fclose(testFile);

    size_t passedTests       = 0;
    size_t numberOfTests     = sizeof(tests) / sizeof(Test);

    for (size_t testNumber = 0; testNumber < numberOfTests; testNumber++){
        if (checkTest(&tests[testNumber], testNumber, 1))
            passedTests++;
    }

    for (size_t fileTestNumber = 0; fileTestNumber < numberOfFileTests; fileTestNumber++){
        if (checkTest(&fileTests[fileTestNumber], fileTestNumber, 1 + numberOfTests))
            passedTests++;
    }
    numberOfTests += numberOfFileTests;

    free(fileTests);

    if (passedTests == numberOfTests)
        printf("%sTests passed: %zu out of %zu \n%s", SETGREEN, passedTests, numberOfTests, SETNONE);
    else
    printf("%sTests passed: %zu out of %zu \n%s", SETRED, passedTests, numberOfTests, SETNONE);

}

bool isEqualSolutions(const Solution *wantSolution, const Solution *solution){
    return (wantSolution -> numberOfRoots == solution -> numberOfRoots) &&
           ((isZero(wantSolution -> x1 - solution -> x1) && isZero(wantSolution -> x2 - solution -> x2)) ||
            (isZero(wantSolution -> x1 - solution -> x2) && isZero(wantSolution -> x2 - solution -> x1)));
}

bool checkTest(const Test *test, size_t testNumber, size_t k){
    Solution solution = {};
    solveQuadratic(&test -> coefficients, &solution);
    if (isEqualSolutions(&test -> wantSolution, &solution)) {
        printf("Test number %zu %spassed\n%s", testNumber + k, SETGREEN, SETNONE);
        return true;
    }

    printf("Test number %zu %sfailed:\n%s"
    "want:\n"
    "Number of roots: %d   x1: %lg, x2: %lg\n"
    "Got:\n"
    "Number of roots: %d   x1: %lg, x2: %lg\n",
            testNumber + k, SETRED, SETNONE, test->wantSolution.numberOfRoots, test->wantSolution.x1, test->wantSolution.x2,
            solution.numberOfRoots, solution.x1, solution.x2);

    return false;
}

size_t readFromFile(Test **fileTests, FILE *testFile){
    size_t numberOfTests = 0;
    fscanf(testFile, "%zu", &numberOfTests);

    Test *tests = nullptr;
    *fileTests = (Test*) calloc(numberOfTests, sizeof(Test));
    tests = *fileTests;
    if (tests == nullptr)
        printf("%sWarning!%s %s fileTests is NULL!\n", SETRED, SETNONE);

    for (size_t currentTest = 0; currentTest < numberOfTests; currentTest++){
        fscanf(testFile, "%lf %lf %lf", &tests->coefficients.a, &tests->coefficients.b, &tests->coefficients.c);
        fscanf(testFile, "%d  %lf %lf", &tests->wantSolution.numberOfRoots, &tests->wantSolution.x1, &tests->wantSolution.x2);
    }

    return numberOfTests;
}
