#include <fstream>
#include <iostream>
#include "include/lorenz.hpp"
#include "include/euler.hpp"
#include "include/rk4.hpp"

int main() {
    LorenzParams params{10.0, 8.0/3.0, 28.0};
    LorenzState state{0.0, 1.0, 1.05};
    double dt = 0.001;
    int steps = 100000;
    std::string method;

    std::cout << "Technique for solving ODEs\n"
                 "Euler (1) , RK4 (2): ";
    std::cout.flush();
    std::cin >> method;
    if (method == "1") method = "euler";
    else if (method == "2") method = "rk4";
    else {
        std::cerr << "No such method!";
        return -1;
    }


    std::string filename = "lorenz_output_" + method + ".csv";
    std::ofstream file("../visualization/" + filename);
    file << "step,x,y,z\n";  // header

    for (int i = 0; i <= steps; i++) {
        file << i << "," << state.x << "," << state.y << "," << state.z << "\n";
        LorenzState deriv = lorenzCompute(state, params);
        method == "euler" ?
            state = eulerStepCompute(state, deriv, dt) : state = rk4StepCompute(state, deriv, params,dt);
    }

    file.close();
    std::cout << "Data written to " << filename << " ✅" << std::endl;
    std::cout.flush();

    std::string pythonPlotPath = "../visualization/plot.py";
    std::string command = "python3 " + pythonPlotPath + " " + filename;
    system(command.c_str());
    return 0;
}