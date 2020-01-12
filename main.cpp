#include "StringReverser.h"
#include "Main.h"

int main(int argc, char** argv) {
    int portAsInt = stoi(argv[1]);
    boot::Main().main(portAsInt);
    return 0;
}