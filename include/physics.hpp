#pragma once

#include <vector>

namespace physics {

    struct Vector2D {
        double x{0.0};
        double y{0.0};
    };

    struct RigidBody {
        int id;
        Vector2D position;
        Vector2D velocity;
        double mass;
        char symbol;
    };

    class PhysicsEngine {
        private:
            std::vector<RigidBody> bodies;
            int arena_width;
            int arena_height;
            Vector2D gravity;

        public:
            PhysicsEngine(int width, int height, Vector2D g_force);
            
            void add_body(const RigidBody& body);
            void update(double dt);
            void render() const;
    };
}
