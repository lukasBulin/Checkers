
#include "RenderBoardGL.h"
#include "CheckerBoard.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


using namespace std;

// Helper function to compile shaders
bool CRenderBoardGL::CompileShader(GLuint& shader, GLenum type, const char* source) {
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

bool CRenderBoardGL::InitializeShaders() {
    const char* vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec2 aPos;
        layout(location = 1) in vec2 aTexCoord;

        out vec2 TexCoord;

        void main() {
            gl_Position = vec4(aPos, 0.0, 1.0);
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

void CRenderBoardGL::SetupBoardGeometry() {
    float vertices[] = {
        // positions   // tex coords
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f,
        -1.0f,  1.0f,  0.0f, 1.0f
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
        -0.1f, -0.1f,     0.0f, 0.0f,
         0.1f, -0.1f,     1.0f, 0.0f,
         0.1f,  0.1f,     1.0f, 1.0f,
        -0.1f,  0.1f,     0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &redCheckerVAO);
    glGenBuffers(1, &redCheckerVBO);
    glGenBuffers(1, &redCheckerEBO);

    glBindVertexArray(redCheckerVAO);

    glBindBuffer(GL_ARRAY_BUFFER, redCheckerVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, redCheckerEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

bool CRenderBoardGL::InitializeRender() {
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

    return true;
}

bool CRenderBoardGL::CreateWindow() {
    if (!glfwInit()) return false;

    window = glfwCreateWindow(640, 480, "Sprite Example", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return false;
    }

    if (!InitializeRender()) return false;

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    return true;
}

GLuint CRenderBoardGL::LoadTexture(const char* filepath) {
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

void CRenderBoardGL::RenderCheckerBoard(const CCheckerBoard* board) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgram);

    glBindVertexArray(boardVAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, boardTexture);
    glUniform1i(glGetUniformLocation(shaderProgram, "uTexture"), 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

    RenderRedChecker(0.0f, 0.0f); // Example position

    glfwSwapBuffers(window);
    glfwPollEvents();
}

void CRenderBoardGL::RenderRedChecker(float x, float y) {

    glUseProgram(shaderProgram);

    glBindVertexArray(redCheckerVAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, redCheckerTexture);
    glUniform1i(glGetUniformLocation(shaderProgram, "uTexture"), 0);

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "uTransform"), 1, GL_FALSE, glm::value_ptr(transform));

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);

}


bool CRenderBoardGL::IsWindowClosed() const {
    return glfwWindowShouldClose(window);
}

void CRenderBoardGL::DeinitializeWindow() {
    glDeleteVertexArrays(1, &boardVAO);
    glDeleteBuffers(1, &boardVBO);
    glDeleteBuffers(1, &boardEBO);
    glDeleteProgram(shaderProgram);
    glDeleteTextures(1, &boardTexture);
    glfwDestroyWindow(window);
    glfwTerminate();
}