#include <SDL3/SDL.h>
#include <vector>

class Screen{
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> points;

    public:
    Screen(){
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer("Spinning Cube", 640*2, 480*2, SDL_WINDOW_RESIZABLE, &window, &renderer);
        SDL_SetRenderScale(renderer, 2.0f, 2.0f);
    }

    // Draw the pixels
    void pixel(float x, float y){
        points.emplace_back(x, y); // Creates a new point (struct) and adds it to this points vector
        // If emplace_back is not available, push_back can be used instead:
        // points.push_back({x, y}); 

    }

    // Displays the points on the screen
    void display(){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Set background color to black
        SDL_RenderClear(renderer); // Clear the screen

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set drawing color to white
        for(auto& point : points){
            SDL_RenderPoint(renderer, static_cast<int>(point.x), static_cast<int>(point.y)); // Draw each point
        }
        SDL_RenderPresent(renderer); // Update the screen with the drawn points
    }

    // Call this function to clear the points vector
    void clear(){
        points.clear();
    }

    void input(){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_EVENT_QUIT){
                SDL_Quit();
                exit(0);
            }
        }
    }

};