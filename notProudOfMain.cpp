#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

#include "src/Renderer.h"
#include "src/VertexBuffer.h"
#include "src/VertexBufferLayout.h"
#include "src/IndexBuffer.h"
#include "src/VertexArray.h"
#include "src/Figures.h"

#include "Shader/Shader.h"
#include "textures/Textures.h"

#include "outside/imGui/imgui.h"
#include "outside/imGui/imgui_impl_glfw_gl3.h"

void ChangeQuadPos(Vertex* quad, glm::vec2 position ,float size, float rotation)
{
    auto q1 = CreateSquare(position.x, position.y, size, rotation);
    memcpy(quad, q1.data(), q1.size() * sizeof(Vertex));
}

bool ColisionDetection(glm::vec3 objA, glm::vec3 objB, float objA_size, float objB_size)
{
    bool collisionX = objA.x + objA_size >= objB.x && objB.x + objB_size >= objA.x;
    bool collisionY = objA.y + objA_size >= objB.y && objB.y + objB_size >= objA.y;

    return collisionX && collisionY;
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
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    {
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "mamy problem klej nie dziala" << std::endl;

    
    unsigned int Quad[] = {
        0 , 1 , 2,
        2 , 3 , 0,
    };
    

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    
    
    #pragma region "plane init"
        glm::vec3 planev3 = { -4.0f, 0.0f, 0.0f };
        glm::vec2 planeSize = { 1.5f, 1.0f };
        VertexArray va;
        VertexBuffer vb(nullptr, sizeof(Vertex) * 4);
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(Quad, sizeof(Quad));
    
    #pragma endregion

    #pragma region "bird A init"

        VertexArray birdAvA;
        VertexBuffer birdAvB(nullptr, sizeof(Vertex) * 4);
        VertexBufferLayout birdAvBL;
        birdAvBL.Push<float>(2);
        birdAvBL.Push<float>(2);
        birdAvA.AddBuffer(birdAvB, birdAvBL);

        IndexBuffer birdAiB(Quad, sizeof(Quad));

    #pragma endregion

    #pragma region "Bird B init"
        VertexArray birdBvA;
        VertexBuffer birdBvB(nullptr, sizeof(Vertex) * 4);
        VertexBufferLayout birdBvBL;
        birdBvBL.Push<float>(2);
        birdBvBL.Push<float>(2);
        birdBvA.AddBuffer(birdBvB, birdBvBL);

        IndexBuffer birdBiB(Quad, sizeof(Quad));
    #pragma endregion

    #pragma region "Bird C init"
        VertexArray birdCvA;
        VertexBuffer birdCvB(nullptr, sizeof(Vertex) * 4);
        VertexBufferLayout birdCvBL;
        birdCvBL.Push<float>(2);
        birdCvBL.Push<float>(2);
        birdCvA.AddBuffer(birdCvB, birdCvBL);

        IndexBuffer birdCiB(Quad, sizeof(Quad));
    #pragma endregion

    #pragma region "Bird D init"
        VertexArray birdDvA;
        VertexBuffer birdDvB(nullptr, sizeof(Vertex) * 4);
        VertexBufferLayout birdDvBL;
        birdDvBL.Push<float>(2);
        birdDvBL.Push<float>(2);
        birdDvA.AddBuffer(birdDvB, birdDvBL);

        IndexBuffer birdDiB(Quad, sizeof(Quad));
    #pragma endregion

    #pragma region "Bg init"

        Vertex bgVt[4];
        glm::vec3 bg_v3(-8.0f, -4.5f, 0.0f);
        glm::vec2 bg_Size(16.0f, 9.0f); 
        auto bg = CreateRectangle(bg_v3, bg_Size, 0.0f);
        memcpy(bgVt, bg.data(), bg.size() * sizeof(Vertex));

        VertexArray bgVa;
        VertexBuffer bgVb(bgVt, sizeof(Vertex) * 4);
        VertexBufferLayout bgVbL;
        bgVbL.Push<float>(2);
        bgVbL.Push<float>(2);
        bgVa.AddBuffer(bgVb, bgVbL);

        IndexBuffer bgIb(Quad, sizeof(Quad));
    #pragma endregion

    #pragma region "arrow init"

        VertexArray arrowvA;
        VertexBuffer arrowvB(nullptr, sizeof(Vertex) * 4);
        VertexBufferLayout arrowvBL;
        arrowvBL.Push<float>(2);
        arrowvBL.Push<float>(2);
        arrowvA.AddBuffer(arrowvB, arrowvBL);

        IndexBuffer arrowiB(Quad, sizeof(Quad));
    #pragma endregion
    glm::mat4 proj = glm::ortho(-8.0f, 8.0f, -4.5f, 4.5f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


    //teraz -8 to jest nasze max left
    //-7 lub -4.5 nasze bottom nie wiem 

    //Shader
    Shader shader("Shader.shader");
    shader.Bind();



    Renderer renderer;
    /*
    ImGui::CreateContext();
    ImGui_ImplGlfwGL3_Init(window, true);
    ImGui::StyleColorsDark();
    */

    #pragma region "Tekstury"
    Texture Planetex("textures/PNG/plane1.png");
    {
        Planetex.AddNewTexture("textures/PNG/plane2.png");
        Planetex.AddNewTexture("textures/PNG/plane3.png");
        Planetex.AddNewTexture("textures/PNG/plane4.png");
        Planetex.AddNewTexture("textures/PNG/plane5.png");
        Planetex.AddNewTexture("textures/PNG/plane6.png");
        Planetex.AddNewTexture("textures/PNG/plane7.png");
        Planetex.AddNewTexture("textures/PNG/plane8.png");
    }

    Texture birdAtex("textures/PNG/bird1-2.png");
    {
        birdAtex.AddNewTexture("textures/PNG/bird1-3.png");
        birdAtex.AddNewTexture("textures/PNG/bird1-4.png");
        birdAtex.AddNewTexture("textures/PNG/bird1-5.png");
    }
    Texture birdBtex("textures/PNG/bird2-2.png");
    {
        birdBtex.AddNewTexture("textures/PNG/bird2-3.png");
        birdBtex.AddNewTexture("textures/PNG/bird2-4.png");
        birdBtex.AddNewTexture("textures/PNG/bird2-5.png");
    }
    Texture birdDD("textures/PNG/menuArrow.png");
    Texture arrowtex("textures/PNG/menuArrow.png");

    Texture birdCtex("textures/PNG/bird3-2.png");
    {
        birdCtex.AddNewTexture("textures/PNG/bird3-3.png");
        birdCtex.AddNewTexture("textures/PNG/bird3-4.png");
        birdCtex.AddNewTexture("textures/PNG/bird3-5.png");
    }
    
    Texture birdDtex("textures/PNG/bird4-2.png");
    {
        birdDtex.AddNewTexture("textures/PNG/bird4-3.png");
        birdDtex.AddNewTexture("textures/PNG/bird4-4.png");
        birdDtex.AddNewTexture("textures/PNG/bird4-5.png");
    }

    Texture destroyedPlane("textures/PNG/damagedplane-00.png");
    {
        destroyedPlane.AddNewTexture("textures/PNG/damagedplane-01.png");
        destroyedPlane.AddNewTexture("textures/PNG/damagedplane-02.png");
        destroyedPlane.AddNewTexture("textures/PNG/damagedplane-03.png");
        destroyedPlane.AddNewTexture("textures/PNG/damagedplane-04.png");
        destroyedPlane.AddNewTexture("textures/PNG/damagedplane-05.png");
        destroyedPlane.AddNewTexture("textures/PNG/damagedplane-06.png");
        destroyedPlane.AddNewTexture("textures/PNG/damagedplane-07.png");
        destroyedPlane.AddNewTexture("textures/PNG/damagedplane-08.png");
        destroyedPlane.AddNewTexture("textures/PNG/damagedplane-09.png");
    }

    Texture background("textures/PNG/bgStart.png");
        background.AddNewTexture("textures/PNG/howToPlay.png");
        background.AddNewTexture("textures/PNG/bg.png");
        background.AddNewTexture("textures/PNG/bgPause.png");
        background.AddNewTexture("textures/PNG/bgEnd.png");

    background.Bind(0);
    Planetex.Bind(1);
    birdAtex.Bind(2);   //A
    birdBtex.Bind(3);   //B
    birdCtex.Bind(4);   //C
    birdDtex.Bind(5);   //D
    destroyedPlane.Bind(6);
    arrowtex.Bind(7);
    birdDD.Bind(8);

    #pragma endregion


    //Unbinding VertexArray, VertexBuffers, indexBuffer and Shader
    va.Unbind();
    vb.Unbind();
    shader.Unbind();
    ib.Unbind();
    

    float birdSpeed = 0.07f; 
    
    glm::vec3 birds[4];
    /*
    birds[0] = { 10.0f , -7.0f , 0 };
    birds[1] = { 12.0f ,  1.5f , 0 };
    birds[2] = {  9.0f , -1.5f , 0 };
    birds[3] = { 14.0f , -3.0f , 0 };
    */

    glm::vec3 arrowV3 = { -5.5f , -1.0f , 0.0f };

    int birdIndex = 2;
    int birdChangeTimer = 0;


    int planeTextureIndex = 1;
    int arrowPosIndex = 0;
    bool destroyed = false;
    int j = 0;

    bool game = false;
    bool paused = false;
    bool releasedUp = true;
    bool releasedDown = true;
    bool releasedEsc = true;
    bool releasedEnter = true;

    bool visibleArrow = true;
    //glm::vec3 BirdTransform(birdpos_x, birdpos_y, 0);

    //Update 
    while (!glfwWindowShouldClose(window))
    {
        renderer.Clear();

        //ImGui_ImplGlfwGL3_NewFrame();

        shader.Bind();
#pragma region "Main Menu"
        if(!game)
        {
            {
                shader.SetUniform1i("u_Texture", 0);
                glm::mat4 model = glm::translate(glm::mat4(1.0f), bg_v3);
                glm::mat4 mvp = proj * view;// *model;
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(bgVa, bgIb, shader);
            }
            //background

            Vertex arrow[4];
            ChangeQuadPos(arrow, arrowV3, 1.0f, 0.0f);
            arrowvB.Bind();
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(arrow), arrow);
            //arrow position

            if(visibleArrow)
            {
                shader.SetUniform1i("u_Texture", 7);
                glm::mat4 mvp = proj * view;
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(arrowvA, arrowiB, shader);
                //arrow render
            }
        }

#pragma endregion

#pragma region "GameLevel"
        if (game)
        {
#pragma region "zas poz obiektow"
            {
                Vertex bird[4];
                ChangeQuadPos(bird, birds[0], 1.0f, 0.0f);

                birdAvB.Bind();
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bird), bird);
            }
            //ptak A

            {
                Vertex bird[4];
                ChangeQuadPos(bird, birds[1], 1.0f, 0.0f);

                birdBvB.Bind();
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bird), bird);
            }
            //Ptak B
            {
                Vertex bird[4];
                ChangeQuadPos(bird, birds[2], 1.0f, 0.0f);

                birdCvB.Bind();
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bird), bird);
            }
            //Ptak C
            {
                Vertex bird[4];
                ChangeQuadPos(bird, birds[3], 1.0f, 0.0f);

                birdDvB.Bind();
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(bird), bird);
            }
            //Ptak D
            {
                Vertex plane[4];
                auto q1 = CreateRectangle(planev3, planeSize, 0.0f);
                memcpy(plane, q1.data(), q1.size() * sizeof(Vertex));

                vb.Bind();
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(plane), plane);
            }

            if (paused)
            {
                Vertex arrow[4];
                ChangeQuadPos(arrow, arrowV3, 1.0f, 0.0f);

                arrowvB.Bind();
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(arrow), arrow);
            }
#pragma endregion


#pragma region "rysowanie obiektow"
            {
                shader.SetUniform1i("u_Texture", 0);
                glm::mat4 model = glm::translate(glm::mat4(1.0f), bg_v3);
                glm::mat4 mvp = proj * view;// *model;
                shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(bgVa, bgIb, shader);
            }
            //background
            if (j != 15)
            {
                if (!paused && game)
                {
                    {
                        shader.SetUniform1i("u_Texture", planeTextureIndex);
                        glm::mat4 model = glm::translate(glm::mat4(1.0f), planev3);
                        glm::mat4 mvp = proj * view;// *model;
                        shader.SetUniformMat4f("u_MVP", mvp);
                        renderer.Draw(va, ib, shader);
                    }
                    //Samolot
                    {
                        shader.SetUniform1i("u_Texture", 2);
                        //glm::mat4 model = glm::translate(glm::mat4(1.0f), birds[0]);
                        glm::mat4 mvp = proj * view;// *model;
                        shader.SetUniformMat4f("u_MVP", mvp);
                        renderer.Draw(birdAvA, birdAiB, shader);
                    }
                    //Ptak A
                    {
                        shader.SetUniform1i("u_Texture", 3);
                        //glm::mat4 model = glm::translate(glm::mat4(1.0f), birds[1]);
                        glm::mat4 mvp = proj * view;// *model;
                        shader.SetUniformMat4f("u_MVP", mvp);
                        renderer.Draw(birdBvA, birdBiB, shader);
                    }
                    //Ptak B
                    {
                        shader.SetUniform1i("u_Texture", 4);
                        //glm::mat4 model = glm::translate(glm::mat4(1.0f), birds[2]);
                        glm::mat4 mvp = proj * view;// *model;
                        shader.SetUniformMat4f("u_MVP", mvp);
                        renderer.Draw(birdCvA, birdCiB, shader);
                    }
                    //Ptak C
                    {
                        shader.SetUniform1i("u_Texture", 5);
                        //glm::mat4 model = glm::translate(glm::mat4(1.0f), birds[3]);
                        glm::mat4 mvp = proj * view;// *model;
                        shader.SetUniformMat4f("u_MVP", mvp);
                        renderer.Draw(birdDvA, birdDiB, shader);
                    }
                    //Ptak D
                }
                if (paused || !game)
                {
                    shader.SetUniform1i("u_Texture", 7);
                    glm::mat4 mvp = proj * view;
                    shader.SetUniformMat4f("u_MVP", mvp);
                    renderer.Draw(arrowvA, arrowiB, shader);
                }
#pragma endregion

#pragma region "animate"
                if (birdChangeTimer < 10)
                    birdChangeTimer++;
                else
                {
                    birdChangeTimer = 0;
                    if (!destroyed)
                        Planetex.ChangeImage();
                    else
                    {
                        j++;
                        if (j == 14)
                        {
                            arrowPosIndex = 0;
                            background.ChangeImage(4);
                        }
                        if (j <= 9)
                            destroyedPlane.ChangeImage();
                    }
                    birdAtex.ChangeImage();
                    birdBtex.ChangeImage();
                    birdCtex.ChangeImage();
                    birdDtex.ChangeImage();
                }
#pragma endregion


#pragma region "Przesuwanie obiektów"
                if (!paused)
                {


                    for (int i = 0; i < 4; i++)
                    {
                        if (ColisionDetection(planev3, birds[i], 1.0f, 1.0f) && !destroyed)
                        {
                            destroyed = true;
                            planeTextureIndex = 6;
                        }

                        if (birds[i].x > -8.0f)
                        {
                            birds[i].x -= birdSpeed;
                        }
                        else
                        {
                            if (i == 3)
                                birdSpeed += 0.01f;
                            birds[i].x = rand() % 4 + 10.0f;
                            birds[i].y = rand() % 9 - 4.5f;
                        }
                    }

                    if (planev3.y > -5.0f)
                        planev3.y -= 0.05f;
                    else
                    {
                        if (!destroyed)
                        {
                            destroyed = true;
                            planeTextureIndex = 6;
                        }
                    }
                    if ((planev3.x < -8.0f || planev3.x > 8.0f || planev3.y > 5.0f) && !destroyed)
                    {
                        destroyed = true;
                        planeTextureIndex = 6;
                    }
                }
#pragma endregion


                int right = glfwGetKey(window, GLFW_KEY_RIGHT);
                int left = glfwGetKey(window, GLFW_KEY_LEFT);
                int esc = glfwGetKey(window, GLFW_KEY_ESCAPE);


                if (esc == GLFW_PRESS)
                {
                    if (releasedEsc)
                    {
                        releasedEsc = false;
                        if (!paused)
                        {
                            background.ChangeImage(3);
                            paused = true;
                            arrowPosIndex = 0;
                            arrowV3 = { -5.5f , -1.0f , 0.0f };
                        }
                        else
                        {
                            background.ChangeImage(2);
                            paused = false;
                        }
                    }
                }

                if (esc != GLFW_PRESS && !releasedEsc)
                    releasedEsc = true;
                if (right == GLFW_PRESS && !destroyed)
                    planev3.x += 0.1f;
                if (left == GLFW_PRESS && !destroyed)
                    planev3.x -= 0.1f;

            }
        }
   #pragma endregion
        
        int space = glfwGetKey(window, GLFW_KEY_SPACE);
        int up = glfwGetKey(window, GLFW_KEY_UP);
        int down = glfwGetKey(window, GLFW_KEY_DOWN);
        int enter = glfwGetKey(window, GLFW_KEY_ENTER);

        if (space == GLFW_PRESS)
        {
            if (!destroyed && !paused)
                planev3.y += 0.1f;

            if (destroyed && j==15)
            {
                background.ChangeImage(0);
                game = false;
                arrowPosIndex = 0;
            }
            if (!game && arrowPosIndex == 3)
            {
                background.ChangeImage(0);
                visibleArrow = true;
                arrowPosIndex = 1;
            }
        }

        if (up == GLFW_PRESS)
            if (releasedUp)
            {
                releasedUp = false;
                if (paused)
                    if (arrowV3.y == -3.5f)
                    {
                        arrowV3.y = -1.0f;
                        arrowPosIndex = 0;
                    }

                if (!game && visibleArrow)
                {
                    if (arrowV3.y < -1.0f)
                    {
                        arrowPosIndex--;
                        arrowV3.y += 1.5f;
                    }
                }
            }

        if (down == GLFW_PRESS)
            if (releasedDown)
            {
                releasedDown = false;
                if (paused)
                    if (arrowV3.y == -1.0f)
                    {
                        arrowV3.y = -3.5f;
                        arrowPosIndex = 1;
                    }

                if (!game && visibleArrow)
                {
                    if (arrowV3.y > -3.0f)
                    {
                        arrowPosIndex++;
                        arrowV3.y += -1.5f;
                    }
                }
            }
        
        if (down != GLFW_PRESS && !releasedDown)
        {
            releasedDown = true;
        }
        if (up != GLFW_PRESS && !releasedUp)
        {
            releasedUp = true;
        }

        if (enter == GLFW_PRESS)
            if(releasedEnter)
        {
                releasedEnter = false;
            if (!game)
            {
                if (arrowPosIndex == 0)
                {
                    background.ChangeImage(2);
                    game = true;
                    paused = false;

                #pragma region "Setting Start Variables"

                    destroyed = false;
                    planeTextureIndex = 1;
                    Planetex.ChangeImage(0);
                    destroyedPlane.ChangeImage(0);
                    j = 0;
                    arrowPosIndex = 0;

                    planev3 = { -4.0f, 0.0f, 0.0f };
                    
                    for (int i = 0; i < 4; i++)
                    {
                        birds[i].x = rand() % 4 + 10.0f;
                        birds[i].y = rand() % 9 - 4.5f;
                        birds[i].z = 0.0f;
                    }

                #pragma endregion



                }
                if (arrowPosIndex == 1)
                {
                    background.ChangeImage(1);
                    arrowPosIndex = 3;
                    visibleArrow = false;
                }
                if (arrowPosIndex == 2)
                {
                    glfwSetWindowShouldClose(window, true);
                }
            }
            else
            {
                if (arrowPosIndex == 0)
                {
                    background.ChangeImage(2);
                    paused = false;
                }
                if(arrowPosIndex == 1)
                {
                    background.ChangeImage(0);
                    paused = false;
                    game = false;
                    arrowPosIndex = 0;
                    arrowV3 = { -5.5f , -1.0f , 0.0f };
                }
            }
        }

        if (enter != GLFW_PRESS && !releasedEnter)
            releasedEnter = true;
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}

    glfwTerminate();
    return 0;
}