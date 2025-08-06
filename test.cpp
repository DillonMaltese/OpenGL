// g++ test.cpp ./src/glad.c -I./include/ -o test.exe -lSDL2

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <iostream>

//Global Variables
int gScreenWidth = 640;
int gScreenHeight = 480;
SDL_Window* gGraphicsAppWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;

bool gQuit = false; //If true, quit the app

void GetOpenGLVersionInfo() {
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void InitializeProgram() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL2 could not initialize video subsystem" << std::endl;
        exit(1);
    }

    //For OpenGL version and context we set up
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    //Create the window
    gGraphicsAppWindow = SDL_CreateWindow("OpenGL First Program", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gScreenWidth, gScreenHeight, SDL_WINDOW_OPENGL);
    if(gGraphicsAppWindow == nullptr) {
        std::cout << "SDL Window could not be created" << std::endl;
        exit(1);
    }

    //Create the Context
    gOpenGLContext = SDL_GL_CreateContext(gGraphicsAppWindow);
    if(gOpenGLContext == nullptr) {
        std::cout << "OpenGL Context not available" << std::endl;
        exit(1);
    }

    //Initialize the GLAD Library
    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        std::cout << "Could not initialize glad" << std::endl;
        exit(1);
    }

    GetOpenGLVersionInfo();
}

void Input() {
    SDL_Event e;

    while(SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT) {
            std::cout << "See ya" << std::endl;
            gQuit = true;
        }
    }
}

void PreDraw() {

}

void Draw() {

}

void MainLoop() {
    while(!gQuit) {
        Input();

        PreDraw();

        Draw();

        //Update the Window
        SDL_GL_SwapWindow(gGraphicsAppWindow);
    }
}

void CleanUp() {
    SDL_DestroyWindow(gGraphicsAppWindow);

    SDL_Quit();
}

int main() {
    //Sets up SDL Window + OpenGL
    InitializeProgram();

    MainLoop();

    CleanUp();

    return 0;
}