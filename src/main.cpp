#include "physics.hpp"
#include <chrono>
#include <thread>
#include <iostream>
using namespace physics;
using namespace std;

int main() {
    PhysicsEngine engine(50, 20, {0.0, 9.81});
    engine.add_body({1, {5.0, 2.0}, {15.0, 0.0}, 1.0, '*'});
    engine.add_body({2, {25.0, 1.0}, {0.0, 0.0}, 10.0, 'O'});

    cout << "\033[2J";

    for (int frame = 0; frame < 100; ++frame) {
        engine.update(0.1); //0.1s delta step
        engine.render();
        this_thread::sleep_for(std::chrono::milliseconds(33));
    }
    return 0;
}
