#include <screen.h>
#include <numeric>

// Define vec3 type
struct vec3 {
    float x, y, z;
};

struct connection{
    int a, b;
};

// Function to rotate a point in 3D space
void rotate(vec3& point, float x = 1, float y = 1, float z = 1){
    float rad = 0; // Definding radian variable

    // Take every value and assign it to rad and do the rrotation w/ the assigned value
    rad = x;
    point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
    point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;

    rad = y;
    point.x = std::cos(rad) * point.x + std::sin(rad) * point.z;
    point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;

    rad = z;
    point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
    point.y = std::sin(rad) * point.x + std::cos(rad) * point.y;
}

// x1 and y1 are starting coords while x2 and y2 are ending coords
void line(Screen& screen, float x1, float y1, float x2, float y2){
    // Calculate the difference in coordinates
    float dx = x2 - x1;
    float dy = y2 - y1;

    // Getting the length of the line
    float length = std::sqrt(dx * dx + dy * dy);

    // Calculate the angle of the line
    float angle = std::atan2(dy, dx);

    for(float i = 0; i < length; i++){
        screen.pixel(
            x1 + i * std::cos(angle), // Calculate the x coordinate
            y1 + i * std::sin(angle)  // Calculate the y coordinate
        );
    }
}

int main(){
    Screen screen; // Create an instance of the screen class

    /*for(int i = 0; i < 100; i++){
        screen.pixel(rand()%640, rand()%480); // Draw random pixels on the screen
    }

    line(screen, 100, 100, 300, 300);
    line(screen, 200, 100, 200, 200);
    line(screen, 200, 200, 100, 200);
    line(screen, 100, 200, 100, 100);*/

    // All of these points are going to be ran through
    std::vector<vec3> points{
        {100, 100, 100},
        {200, 100, 100},
        {200, 200, 100},
        {100, 200, 100},

        {100, 100, 200},
        {200, 100, 200},
        {200, 200, 200},
        {100, 200, 200}
    };

    std::vector<connection> connections{
        {0, 4}, {1, 5}, {2, 6}, {3, 7}, // Vertical connections
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // Bottom square connections
        {4, 5}, {5, 6}, {6, 7}, {7, 4}  // Top square connections
    };

    // Calculate the center of the cube (centeriod)
    vec3 c{0, 0, 0}; // Initialize the center point
    for(auto& p : points){
        c.x += p.x; // Sum up the x coordinates
        c.y += p.y; // Sum up the y coordinates
        c.z += p.z; // Sum up the z coordinates
    }
    c.x /= points.size(); // Average the x coordinates
    c.y /= points.size(); // Average the y coordinates
    c.z /= points.size(); // Average the z coordinates

    // Main loop to keep the application running
    while(true){

        for(auto& p : points){
            p.z -= c.z; // Center the points around the z-axis
            p.x -= c.x; // Center the points around the x-axis
            p.y -= c.y; // Center the points around the y-axis

            // Rotate each point around the x, y, and z axes
            rotate(p, 0.02, 0.01, 0.04);

            p.x += c.x; // Recenter the points around the x-axis
            p.y += c.y; // Recenter the points around the y-axis
            p.z += c.z; // Recenter the points around the z-axis

            screen.pixel(p.x, p.y); // Draw the pixel on the screen
        }

        // Draw lines between connected points
        for(auto& conn : connections){
            line(screen, points[conn.a].x, points[conn.a].y, points[conn.b].x, points[conn.b].y);

        screen.display();
        screen.clear(); // Clear the points vector for the next frame
        screen.input(); // Handle input events, checking for quit events (if user clicked X button)
        SDL_Delay(30); // Delay for 3 msec
    }


    return 0; // Exit the program
}