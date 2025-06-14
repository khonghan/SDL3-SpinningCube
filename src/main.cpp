#include "screen.h" // Adjusted to use quotes for local header file
#include <numeric>

// Define vec3 type
struct vec3 {
    float x, y, z;
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

    

    // Main loop to keep the application running
    while(true){
        screen.display();
        screen.input(); // Handle input events, checking for quit events (if user clicked X button)
    }


    return 0; // Exit the program
}
