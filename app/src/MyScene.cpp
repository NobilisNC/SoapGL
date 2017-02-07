#include "MyScene.hpp"


const std::string DATA_PATH = "/home/nobilis/coding/perso/c++/openGL/";

MyScene::MyScene(int h, int w) :
    soap::Scene(h,w) ,
    lightShader(DATA_PATH +"data/shaders/vertex/2.shader", DATA_PATH +"data/shaders/fragment/source_light.shader"),
    objectShader(DATA_PATH + "data/shaders/vertex/2.shader", DATA_PATH +"data/shaders/fragment/light.shader"),
    textCube(DATA_PATH +"data/textures/container2.png"),
    textCube_spec(DATA_PATH +"data/textures/container2_specular.png", soap::Texture::SPECULAR),
    grass(DATA_PATH+"data/textures/grass.png", soap::Texture::DIFFUSE),
    default_spec(DATA_PATH+"data/textures/default_spec.png", soap::Texture::SPECULAR),
    cubeMaterial({50, 50, 50}, &textCube, &textCube_spec, 16),
    lightMaterial({100,100,100}, soap::Color::white, soap::Color::white, 1),
    floorMaterial({40,40,40}, &grass, &default_spec, 2),
    cam(glm::vec3(0.0f, 0.0f, 5.0f)),
    light0(glm::vec3(0,1,0), new soap::SimpleMaterial(soap::Color::white, soap::Color::white, soap::Color::white, 16)),
    plight0(glm::vec3(1,-0.5,0), &lightMaterial, 1, 0.9f, 0.032),
    splight0(glm::vec3(-1,1,0), &lightMaterial, 1, 0.9f, 0.032, {0,-1,0}, 15.f, 15.f),
    nanosuit(DATA_PATH + "data/Obj/nanosuit/nanosuit.obj")
{

  this->init();
}

void MyScene::init()
{
    setProjection(glm::perspective(45.0f, GLfloat(width()) / height(), 0.1f, 100.0f));

    soap::VertexArray vertices ={
        // Positions           //Normals           // Texture Coords
        {{-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 0.0f}},
        {{0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 1.0f}},
        {{0.5f,  0.5f, -0.5f},  {0.0f,  0.0f, -1.0f},  {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f,  0.0f, -1.0f},  {0.0f, 0.0f}},

        {{-0.5f, -0.5f,  0.5f},  {0.0f,  0.0f, 1.0f},  {0.0f, 0.0f}},
        {{0.5f, -0.5f,  0.5f},   {0.0f,  0.0f, 1.0f},  {1.0f, 0.0f}},
        {{0.5f,  0.5f,  0.5f},   {0.0f,  0.0f, 1.0f},  {1.0f, 1.0f}},
        {{0.5f,  0.5f,  0.5f},   {0.0f,  0.0f, 1.0f},  {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f},  {0.0f,  0.0f, 1.0f},  {0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f},  {0.0f,  0.0f, 1.0f},  {0.0f, 0.0f}},

        {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f}},

        {{0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 0.0f}},
        {{0.5f,  0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 1.0f}},
        {{0.5f, -0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {0.0f, 0.0f}},
        {{0.5f,  0.5f,  0.5f},  {1.0f,  0.0f,  0.0f},  {1.0f, 0.0f}},

        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f,  0.0f},  {0.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f, 1.0f}},
        {{0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f, 0.0f}},
        {{0.5f, -0.5f,  0.5f},  {0.0f, -1.0f,  0.0f},  {1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, -1.0f,  0.0f},  {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, -1.0f,  0.0f},  {0.0f, 1.0f}},

        {{-0.5f,  0.5f, -0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f}},
        {{0.5f,  0.5f, -0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 1.0f}},
        {{0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f}},
        {{0.5f,  0.5f,  0.5f},  {0.0f,  1.0f,  0.0f},  {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f}, {0.0f,  1.0f,  0.0f},  {0.0f, 1.0f}}
    };

    cube.setVertices(vertices);
    cube.setMaterial(&cubeMaterial);

    cubeLight.setVertices(vertices);
    cubeLight.setMaterial(&lightMaterial);

    floor.setVertices(vertices);
    floor.setMaterial(&floorMaterial);

    addLight(&light0);
    addLight(&plight0);
    //addLight(&splight0);

    //gl::ClearColor(soap::Color::gray.r,soap::Color::gray.g,soap::Color::gray.b, 1.0f);
}


void MyScene::render()
{


    objectShader.use();
    setView(cam.getView());

    bindLights(objectShader);

    objectShader.uniform("viewPos", cam.position());

    setModel(glm::mat4());
    setModel( glm::translate(model(), glm::vec3(.0f, -2.0f, 0.0f)));
    setModel(glm::scale(model(), glm::vec3(.3f, 0.3f, 0.3f)));
    sendMatrix(objectShader);
    nanosuit.draw(objectShader);


    setModel(glm::mat4());
    setModel( glm::translate(model(), glm::vec3(-3.0f, 0.0f, 0.0f)));
    sendMatrix(objectShader);
    cube.draw(objectShader);


    setModel(glm::mat4());
    setModel( glm::translate(model(), glm::vec3(0.0f, -2.f, 0.0f)));
    setModel(glm::scale(model(), glm::vec3(10.f, 0.2f, 10.f)));
    sendMatrix(objectShader);
    floor.draw(objectShader);

    setModel(glm::mat4());
    setModel( glm::translate(model(), glm::vec3(0.0f, 0.f, -5.0f)));
    setModel(glm::scale(model(), glm::vec3(10.f, 10.f, 1.f)));
    sendMatrix(objectShader);
    floor.draw(objectShader);









    // --- lighting SOURCE --- //

    lightShader.use();
    GLfloat radius = 2.f;

    plight0.position().x = sin(glfwGetTime()) * radius;
    plight0.position().y = sin(glfwGetTime()) * radius;
    plight0.position().z = cos(glfwGetTime()) * radius;
    setModel(glm::mat4());

    setModel( glm::translate(model(), plight0.position()));
    setModel(glm::scale(model(), glm::vec3(0.2f)));

    sendMatrix(lightShader);
    cubeLight.draw(lightShader);
}


