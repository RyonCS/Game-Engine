#include "../include/Application.hpp"

// Main entry into our program.
int main(int argc, char* argv[]) {

    std::cout << "Length of arguments: " << argc << "\n";

    Application app;

    app.Loop(60.0f);

    return 0;
}