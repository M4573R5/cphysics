#include "physics.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

namespace physics {

    PhysicsEngine::PhysicsEngine(int width, int height, Vector2D g_force) : arena_width(width), arena_height(height), gravity(g_force) {}

    void PhysicsEngine::add_body(const RigidBody& body) {
        bodies.push_back(body);
    }

    void PhysicsEngine::update(double dt) {
        for (auto& body : bodies) {
            body.velocity.x += gravity.x * dt;
            body.velocity.y += gravity.y * dt;

            body.position.x += body.velocity.x * dt;
            body.position.y += body.velocity.y * dt;

            if (body.position.y >= arena_height - 1) {
                body.position.y = arena_height - 1;
                body.velocity.y = -body.velocity.y * 0.75; // Reverse velocity and apply 25% energy dampening (rebound bounciness)
            }

            // Collision Detection (x-axis)
            if (body.position.x <= 0) {
                body.position.x = 0;
                body.velocity.x = -body.velocity.x * 0.8;
            } else if (body.position.x >= arena_width - 1) {
                body.position.x = arena_width - 1;
                body.velocity.x = -body.velocity.x * 0.8;
            }
        }
    }

    void PhysicsEngine::render() const {
        vector<string> grid(arena_height, string(arena_width, ' '));

        //border boundaries
        for (int x = 0; x < arena_width; ++x) grid[arena_height - 1][x] = '#';
        for (int y = 0; y < arena_height; ++y) {
            grid[y][0] = '#';
            grid[y][arena_width - 1] = '#';
        }

        for (const auto& body : bodies) {
            int px = static_cast<int>(body.position.x);
            int py = static_cast<int>(body.position.y);

            if (px >= 0 && px < arena_width && py >= 0 && py < arena_height) {
                grid[py][px] = body.symbol;
            }
        }

        // Animate frame 
        cout << "\033[H"; 
        for (const auto& row : grid) {
            cout << row << endl;
        }
    }
}
