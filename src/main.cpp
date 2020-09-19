#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Object.h"
#include "Box.h"
#include "Line.h"
#include "Pyramid.h"
#include "Scene.h"
#include "Timeline.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/string_cast.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

/*
    What does static mean in this context?
        - Outside of a class or struct, then a static variable or function will only be "visible" in the c++ file its declared in.
        - If I had another c++ file and tried to call CompileShader( ), it would raise an error.
        - Try to have all variables/functions marked as static UNLESS its needed across translation units
*/

unsigned int Object::current_id = 0;

void processInput(GLFWwindow* window, Camera& cam, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam.handleInput(GLFW_KEY_W, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam.handleInput(GLFW_KEY_S, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam.handleInput(GLFW_KEY_A, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam.handleInput(GLFW_KEY_D, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        cam.handleInput(GLFW_KEY_LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        cam.handleInput(GLFW_KEY_RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cam.handleInput(GLFW_KEY_UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cam.handleInput(GLFW_KEY_DOWN, deltaTime);
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;
    
    std::cout << glGetString(GL_VERSION) << std::endl;

    {   
        /* Enable Color Blending */
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        /* Enable Z-Buffer */
        GLCall(glEnable(GL_DEPTH_TEST)); 

        /* AFTER CLASS ABSTRACTION*/
        VertexArray va;
        Timeline tl;
        Scene scene(tl);

        glm::vec3 origin(0.f);
        glm::vec4 red(0.863f, 0.078f, 0.235f, 1.0f);
        glm::vec4 blue(0.416f, 0.353f, 0.804f, 1.f);
        glm::vec4 yellow(1.f, 0.894f, 0.710f, 1.f);

        float length = 5.f;
        float tmp = 0.05f;
        Box *xaxis = new Box(origin, tmp, length, tmp, 0.f, glm::vec3(1.f), red);
        Box* yaxis = new Box(origin, tmp, length, tmp, 90.f, glm::vec3(0.f,0.f,1.f), blue);
        Box* zaxis = new Box(origin, tmp, length, tmp, 90.f, glm::vec3(0.f,1.f,0.f), yellow);
        Pyramid* xArrow1 = new Pyramid(glm::vec3(2.5f, 0.f, 0.f), 0.1f, 45.f, -90.f, glm::vec3(0.f,0.f,1.f), red);
        Pyramid* xArrow2 = new Pyramid(glm::vec3(-2.5f, 0.f, 0.f), 0.1f, 45.f, 90.f, glm::vec3(0.f, 0.f, 1.f), red);
        Pyramid* yArrow1 = new Pyramid(glm::vec3(0.f, 2.5f, 0.f), 0.1f, 45.f, 0.f, glm::vec3(0.f, 0.f, 1.f), blue);
        Pyramid* yArrow2 = new Pyramid(glm::vec3(0.f, -2.5f, 0.f), 0.1f, 45.f, 180.f, glm::vec3(0.f, 0.f, 1.f), blue);
        Pyramid* zArrow1 = new Pyramid(glm::vec3(0.f, 0.f, 2.5f), 0.1f, 45.f, 90.f, glm::vec3(1.f, 0.f, 0.f), yellow);
        Pyramid* zArrow2 = new Pyramid(glm::vec3(0.f, 0.f, -2.5f), 0.1f, 45.f, -90.f, glm::vec3(1.f, 0.f, 0.f), yellow);
        scene.Push(xaxis);
        scene.Push(yaxis);
        scene.Push(zaxis);
        scene.Push(xArrow1);
        scene.Push(xArrow2);
        scene.Push(yArrow1);
        scene.Push(yArrow2);
        scene.Push(zArrow1);
        scene.Push(zArrow2);



        scene.Setup(va);

        /* Model Matrix -> Positions model in World Space*/
        glm::mat4 model = glm::mat4(1.0f);
        /* View Matrix -> Camera */
        glm::mat4 view = glm::mat4(1.0f);
        /* Projection -> Normalizes the vector for easy clipping*/
        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        glm::mat4 mvp;

        /* Shader */
        Shader shader("res/shaders/Basic.shader");
        shader.Bind();

        shader.SetUniform1i("u_Texture", 0);
        shader.SetUniform3f("lightColor", 1.f, 1.f, 1.f);
        shader.SetUniform4f("lightPos", -2.f, 3.f, -1.f, 1.f);

        /* Textures */
        Texture texture("res/textures/box.png");
        Texture texture2("res/textures/gradient.png");
        
        va.Unbind();
        shader.Unbind();

        Renderer renderer;

        /* imgui setup */
        const char* glsl_version = "#version 130";
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glsl_version);
        ImGui::StyleColorsDark();

        /* imgui variables*/
        bool show_demo_window = true;
        bool show_another_window = false;
        ImVec4 clear_color = ImVec4(0.2f, 0.2f, 0.2f, 1.00f);

        /* Camera Setup */
        glm::vec3 camPos = glm::vec3(0.f, 0.f, 5.f);
        glm::vec3 camFront = glm::vec3(0.f, 0.f, -5.f);
        glm::vec3 camUp = glm::vec3(0.f, 1.f, 0.f);
        glm::vec3 direction(0.f);

        Camera lookAtCam(camPos, camUp);

        /* rendering variables */
        float deltaTime = 0.0f;	// time between current frame and last frame
        float lastFrame = 0.0f;
        float radius = 0.f;

        float x = -5.f;
        bool* open = (bool*)0;
        /* 
            Loop until the user closes the window 
        */
        while (!glfwWindowShouldClose(window))
        {
            // per-frame time logic
            // --------------------
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            processInput(window, lookAtCam, deltaTime);

            /* Render here */
            renderer.Clear();

            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

            shader.Bind();
            va.Bind();

            texture.BindUnit(0);
            texture2.BindUnit(1);

            lookAtCam.update();
            
            glm::mat4 view;
            view = lookAtCam.getViewMatrix();

            glm::mat4 model = glm::mat4(1.f);

            mvp = projection * view * model;
            shader.SetUniformMat4f("u_MVP", mvp);

            scene.Render(shader, deltaTime);

            /* imgui window */
            {
                static float f = 0.0f;
                static int counter = 0;

                ImGui::Begin("Graphics Tutorial", open, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize);                          // Create a window called "Hello, world!" and append into it.

                ImGui::TextWrapped("Welcome to an educational OpenGL experience. Here I will go through some of the fundamental topics of graphics programming. Please choose a topic below to start!");
                ImGui::Button("Linear Algebra Fundamentals");
                ImGui::Button("The Model Matrix");
                ImGui::Button("The View Matrix");
                ImGui::Button("The Perspective Matrix");
                ImGui::Button("Look-At Camera");
                ImGui::Button("Orthographic Projection");
                ImGui::Button("Perspective Projection");
                ImGui::End();
            }

            ImGui::Render();
            int display_w, display_h;
            glfwGetFramebufferSize(window, &display_w, &display_h);
            glViewport(0, 0, display_w, display_h);
            glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();
    return 0;
}