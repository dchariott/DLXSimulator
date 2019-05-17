#include <iostream>
#include "DataPath.h"

int main(int argc, char* argv[]) {
    DataPath executable;
    if (executable.LoadProgramCode(argv[1])) executable.RunProgram();
    return 0;
}