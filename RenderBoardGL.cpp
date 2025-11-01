#include "RenderBoardGL.h"
#include "CheckerBoard.h"
#include "GameState.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace std;

// Helper function to compile shaders
bool CRenderBoardGL::CompileShader(GLuint& shader, GLenum type, const char* source) 
{
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        cerr << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
            << " Shader compilation failed:\n" << infoLog << endl;
        return false;
    }
    return true;
}

bool CRenderBoardGL::InitializeShaders() 
{
    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec2 aPos;
        layout(location = 1) in vec2 aTexCoord;

        uniform mat4 uTransform;
        uniform mat4 uProjection;

        out vec2 TexCoord;

        void main() {
            gl_Position = uProjection * uTransform * vec4(aPos, 0.0, 1.0);
            TexCoord = aTexCoord;
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        in vec2 TexCoord;
        uniform sampler2D uTexture;

        void main() {
            FragColor = texture(uTexture, TexCoord);
        }
    )";

    GLuint vertexShader, fragmentShader;
    if (!CompileShader(vertexShader, GL_VERTEX_SHADER, vertexShaderSource)) return false;
    if (!CompileShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderSource)) return false;

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        cerr << "Shader Program linking failed:\n" << infoLog << endl;
        return false;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return true;
}

void CRenderBoardGL::SetupBoardGeometry() 
{
    float vertices[] = {
        // positions   // tex coords
         0.0f,  0.0f,  0.0f, 0.0f,
      800.0f,   0.0f,  1.0f, 0.0f,
      800.0f, 800.0f,  1.0f, 1.0f,
        0.0f, 800.0f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &boardVAO);
    glGenBuffers(1, &boardVBO);
    glGenBuffers(1, &boardEBO);

    glBindVertexArray(boardVAO);

    glBindBuffer(GL_ARRAY_BUFFER, boardVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, boardEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void CRenderBoardGL::SetupRedCheckerGeometry()
{
    float vertices[] = {
        // positions     // tex coords
         0.0f,  0.0f,  0.0f, 0.0f,
      80.0f,   0.0f,  1.0f, 0.0f,
      80.0f, 80.0f,  1.0f, 1.0f,
        0.0f, 80.0f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &CheckerVAO);
    glGenBuffers(1, &CheckerVBO);
    glGenBuffers(1, &CheckerEBO);

    glBindVertexArray(CheckerVAO);

    glBindBuffer(GL_ARRAY_BUFFER, CheckerVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, CheckerEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

bool CRenderBoardGL::InitializeRender() 
{
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cerr << "Failed to initialize GLAD" << endl;
        return false;
    }

    cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;

    if (!InitializeShaders()) return false;

    SetupBoardGeometry();
    SetupRedCheckerGeometry();

    //board Texture
    boardTexture = LoadTexture("Images/CheckerBoard.jpg");
    if (boardTexture == 0) 
        return false;

    //redChecker Texture
    redCheckerTexture = LoadTexture("Images/CheckerPieceRed.png");
    if (redCheckerTexture == 0)
        return false;

    //redChecker Texture
    blackCheckerTexture = LoadTexture("Images/CheckerPieceBlack.png");
    if (blackCheckerTexture == 0)
        return false;

    return true;
}

bool CRenderBoardGL::CreateWindow(CGameState* inGameState)
{
    if (!glfwInit())
    {
        return false;
    }

    window = glfwCreateWindow(windowWidth, windowHeight, "Sprite Example", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return false;
    }

    glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
    glfwSetMouseButtonCallback(window, MouseButtonCallback);
    glfwSetWindowUserPointer(window, this); // So we can access the instance in the static callback

    if (!InitializeRender())
    {
        return false;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    gameState = inGameState;

    return true;
}

void CRenderBoardGL::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int windowWidth, windowHeight;
        glfwGetWindowSize(window, &windowWidth, &windowHeight);

        // Flip Y to match OpenGL's bottom-left origin
        ypos = windowHeight - ypos;

        // Swap X and Y if needed
        double correctedX = ypos;
        double correctedY = xpos;

        int squareSize = windowWidth / 8;

        int boardX = static_cast<int>(correctedX / squareSize);
        int boardY = static_cast<int>(correctedY / squareSize);

        CRenderBoardGL* instance = static_cast<CRenderBoardGL*>(glfwGetWindowUserPointer(window));
        if (instance != nullptr && instance->gameState != nullptr)
        {
            instance->gameState->HandleMouseClick(boardX, boardY);
        }
    }
}

GLuint CRenderBoardGL::LoadTexture(const char* filepath) 
{
    int width, height, channels;
    unsigned char* data = stbi_load(filepath, &width, &height, &channels, 0);
    if (!data) {
        cerr << "Failed to load texture: " << filepath << endl;
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(data);
    return textureID;
}

void CRenderBoardGL::RenderCheckerBoard(const CCheckerBoard* board) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);

    GLint loc = glGetUniformLocation(shaderProgram, "uTransform");
    if (loc == -1) {
        std::cerr << "uTransform not found in shader!" << std::endl;
    }

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uProjection"), 1, GL_FALSE, glm::value_ptr(projection));


    glBindVertexArray(boardVAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, boardTexture);
    glUniform1i(glGetUniformLocation(shaderProgram, "uTexture"), 0);


    glm::mat4 boardTransform = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uTransform"), 1, GL_FALSE, glm::value_ptr(boardTransform));


    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    RenderAllCheckers(board);

    //RenderChecker(100.0f, 100.0f); // Example position
    //RenderChecker(300.f, 300.f);

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void CRenderBoardGL::RenderAllCheckers(const CCheckerBoard* board)
{
    //clear console
    system("cls");

    assert(board != nullptr);

    for (int row = board->GetBoardSize() - 1; row >= 0; row--)
    {
        for (int col = 0; col < board->GetBoardSize(); col++)
        {
            const ECheckerType value = board->GetValueAt(row, col);

            switch (value)
            {
            case ECheckerType::red:
                RenderChecker(col * 100 + 10, row * 100 + 10, redCheckerTexture);
                break;
            case ECheckerType::black:
                RenderChecker(col * 100 + 10, row * 100 + 10, blackCheckerTexture);
                break;

            }
        }
    }
}

void CRenderBoardGL::RenderChecker(float x, float y, GLuint texture)
{
    glBindVertexArray(CheckerVAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f, -1.0f, 1.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uProjection"), 1, GL_FALSE, glm::value_ptr(projection));

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uTransform"), 1, GL_FALSE, glm::value_ptr(transform));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

bool CRenderBoardGL::IsWindowClosed() const 
{
    return glfwWindowShouldClose(window);
}

void CRenderBoardGL::DeinitializeWindow() 
{
    glDeleteVertexArrays(1, &boardVAO);
    glDeleteBuffers(1, &boardVBO);
    glDeleteBuffers(1, &boardEBO);
    glDeleteProgram(shaderProgram);
    glDeleteTextures(1, &boardTexture);
    glfwDestroyWindow(window);
    glfwTerminate();
}