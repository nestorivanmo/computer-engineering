/*
	Alumno: Néstor I. Martínez Ostoa
	Nombre: 315618648_REPORTE3_GPO8.cpp
	Descripción: Modelado geométrico - modelo de un caracter de Pokemon Quest
	Fecha: 24 de septiembre del 2021
*/

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);

const GLint WIDTH = 800, HEIGHT = 600;
float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;




int main() {
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 3 - 315618648", nullptr, nullptr);
	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
	if (nullptr == window) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);

	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	// Set up vertex data (and buffer(s)) and attribute pointers
	

	// use with Perspective Projection
	float vertices[] = {
		// Light blue: index 0
		-0.5f, -0.5f, 0.5f,     0.75f, 0.9f, 0.94f,
		0.5f, -0.5f, 0.5f,      0.75f, 0.9f, 0.94f,
		0.5f,  0.5f, 0.5f,      0.75f, 0.9f, 0.94f,
		0.5f,  0.5f, 0.5f,      0.75f, 0.9f, 0.94f,
		-0.5f,  0.5f, 0.5f,     0.75f, 0.9f, 0.94f,
		-0.5f, -0.5f, 0.5f,     0.75f, 0.9f, 0.94f,
		-0.5f, -0.5f,-0.5f,   0.75f, 0.9f, 0.94f,
		0.5f, -0.5f,-0.5f,     0.75f, 0.9f, 0.94f,
		0.5f,  0.5f,-0.5f,     0.75f, 0.9f, 0.94f,
		0.5f,  0.5f,-0.5f,     0.75f, 0.9f, 0.94f,
		-0.5f,  0.5f,-0.5f,   0.75f, 0.9f, 0.94f,
		-0.5f, -0.5f,-0.5f,     0.75f, 0.9f, 0.94f,
		0.5f, -0.5f,  0.5f,    0.75f, 0.9f, 0.94f,
		0.5f, -0.5f, -0.5f,    0.75f, 0.9f, 0.94f,
		0.5f,  0.5f, -0.5f,    0.75f, 0.9f, 0.94f,
		0.5f,  0.5f, -0.5f,    0.75f, 0.9f, 0.94f,
		0.5f,  0.5f,  0.5f,    0.75f, 0.9f, 0.94f,
		0.5f,  -0.5f, 0.5f,    0.75f, 0.9f, 0.94f,
		-0.5f,  0.5f,  0.5f,    0.75f, 0.9f, 0.94f,
		-0.5f,  0.5f, -0.5f,    0.75f, 0.9f, 0.94f,
		-0.5f, -0.5f, -0.5f,    0.75f, 0.9f, 0.94f,
		-0.5f, -0.5f, -0.5f,    0.75f, 0.9f, 0.94f,
		-0.5f, -0.5f,  0.5f,    0.75f, 0.9f, 0.94f,
		-0.5f,  0.5f,  0.5f,    0.75f, 0.9f, 0.94f,
		-0.5f, -0.5f, -0.5f,    0.75f, 0.9f, 0.94f,
		0.5f, -0.5f, -0.5f,     0.75f, 0.9f, 0.94f,
		0.5f, -0.5f,  0.5f,     0.75f, 0.9f, 0.94f,
		0.5f, -0.5f,  0.5f,     0.75f, 0.9f, 0.94f,
		-0.5f, -0.5f,  0.5f,    0.75f, 0.9f, 0.94f,
		-0.5f, -0.5f, -0.5f,    0.75f, 0.9f, 0.94f,
		-0.5f,  0.5f, -0.5f,    0.75f, 0.9f, 0.94f,
		0.5f,  0.5f, -0.5f,     0.75f, 0.9f, 0.94f,
		0.5f,  0.5f,  0.5f,     0.75f, 0.9f, 0.94f,
		0.5f,  0.5f,  0.5f,     0.75f, 0.9f, 0.94f,
		-0.5f,  0.5f,  0.5f,    0.75f, 0.9f, 0.94f,
		-0.5f,  0.5f, -0.5f,    0.75f, 0.9f, 0.94f,
		// Low gray : start index 36
		-0.5f, -0.5f, 0.5f,     0.7f,0.7f,0.7f,
		0.5f, -0.5f, 0.5f,      0.7f,0.7f,0.7f,
		0.5f,  0.5f, 0.5f,      0.7f,0.7f,0.7f,
		0.5f,  0.5f, 0.5f,      0.7f,0.7f,0.7f,
		-0.5f,  0.5f, 0.5f,     0.7f,0.7f,0.7f,
		-0.5f, -0.5f, 0.5f,     0.7f,0.7f,0.7f,
		-0.5f, -0.5f,-0.5f,   0.7f,0.7f,0.7f,
		0.5f, -0.5f,-0.5f,     0.7f,0.7f,0.7f,
		0.5f,  0.5f,-0.5f,     0.7f,0.7f,0.7f,
		0.5f,  0.5f,-0.5f,     0.7f,0.7f,0.7f,
		-0.5f,  0.5f,-0.5f,   0.7f,0.7f,0.7f,
		-0.5f, -0.5f,-0.5f,     0.7f,0.7f,0.7f,
		0.5f, -0.5f,  0.5f,    0.7f,0.7f,0.7f,
		0.5f, -0.5f, -0.5f,    0.7f,0.7f,0.7f,
		0.5f,  0.5f, -0.5f,    0.7f,0.7f,0.7f,
		0.5f,  0.5f, -0.5f,    0.7f,0.7f,0.7f,
		0.5f,  0.5f,  0.5f,    0.7f,0.7f,0.7f,
		0.5f,  -0.5f, 0.5f,    0.7f,0.7f,0.7f,
		-0.5f,  0.5f,  0.5f,    0.7f,0.7f,0.7f,
		-0.5f,  0.5f, -0.5f,    0.7f,0.7f,0.7f,
		-0.5f, -0.5f, -0.5f,    0.7f,0.7f,0.7f,
		-0.5f, -0.5f, -0.5f,    0.7f,0.7f,0.7f,
		-0.5f, -0.5f,  0.5f,    0.7f,0.7f,0.7f,
		-0.5f,  0.5f,  0.5f,    0.7f,0.7f,0.7f,
		-0.5f, -0.5f, -0.5f,    0.7f,0.7f,0.7f,
		0.5f, -0.5f, -0.5f,     0.7f,0.7f,0.7f,
		0.5f, -0.5f,  0.5f,     0.7f,0.7f,0.7f,
		0.5f, -0.5f,  0.5f,     0.7f,0.7f,0.7f,
		-0.5f, -0.5f,  0.5f,    0.7f,0.7f,0.7f,
		-0.5f, -0.5f, -0.5f,    0.7f,0.7f,0.7f,
		-0.5f,  0.5f, -0.5f,    0.7f,0.7f,0.7f,
		0.5f,  0.5f, -0.5f,     0.7f,0.7f,0.7f,
		0.5f,  0.5f,  0.5f,     0.7f,0.7f,0.7f,
		0.5f,  0.5f,  0.5f,     0.7f,0.7f,0.7f,
		-0.5f,  0.5f,  0.5f,    0.7f,0.7f,0.7f,
		-0.5f,  0.5f, -0.5f,    0.7f,0.7f,0.7f,
		// High gray: start index 72
		-0.5f, -0.5f, 0.5f,     0.4f,0.4f,0.4f,
		0.5f, -0.5f, 0.5f,      0.4f,0.4f,0.4f,
		0.5f,  0.5f, 0.5f,      0.4f,0.4f,0.4f,
		0.5f,  0.5f, 0.5f,      0.4f,0.4f,0.4f,
		-0.5f,  0.5f, 0.5f,     0.4f,0.4f,0.4f,
		-0.5f, -0.5f, 0.5f,     0.4f,0.4f,0.4f,
		-0.5f, -0.5f,-0.5f,   0.4f,0.4f,0.4f,
		0.5f, -0.5f,-0.5f,     0.4f,0.4f,0.4f,
		0.5f,  0.5f,-0.5f,     0.4f,0.4f,0.4f,
		0.5f,  0.5f,-0.5f,     0.4f,0.4f,0.4f,
		-0.5f,  0.5f,-0.5f,   0.4f,0.4f,0.4f,
		-0.5f, -0.5f,-0.5f,     0.4f,0.4f,0.4f,
		0.5f, -0.5f,  0.5f,    0.4f,0.4f,0.4f,
		0.5f, -0.5f, -0.5f,    0.4f,0.4f,0.4f,
		0.5f,  0.5f, -0.5f,    0.4f,0.4f,0.4f,
		0.5f,  0.5f, -0.5f,    0.4f,0.4f,0.4f,
		0.5f,  0.5f,  0.5f,    0.4f,0.4f,0.4f,
		0.5f,  -0.5f, 0.5f,    0.4f,0.4f,0.4f,
		-0.5f,  0.5f,  0.5f,    0.4f,0.4f,0.4f,
		-0.5f,  0.5f, -0.5f,    0.4f,0.4f,0.4f,
		-0.5f, -0.5f, -0.5f,    0.4f,0.4f,0.4f,
		-0.5f, -0.5f, -0.5f,    0.4f,0.4f,0.4f,
		-0.5f, -0.5f,  0.5f,    0.4f,0.4f,0.4f,
		-0.5f,  0.5f,  0.5f,    0.4f,0.4f,0.4f,
		-0.5f, -0.5f, -0.5f,    0.4f,0.4f,0.4f,
		0.5f, -0.5f, -0.5f,     0.4f,0.4f,0.4f,
		0.5f, -0.5f,  0.5f,     0.4f,0.4f,0.4f,
		0.5f, -0.5f,  0.5f,     0.4f,0.4f,0.4f,
		-0.5f, -0.5f,  0.5f,    0.4f,0.4f,0.4f,
		-0.5f, -0.5f, -0.5f,    0.4f,0.4f,0.4f,
		-0.5f,  0.5f, -0.5f,    0.4f,0.4f,0.4f,
		0.5f,  0.5f, -0.5f,     0.4f,0.4f,0.4f,
		0.5f,  0.5f,  0.5f,     0.4f,0.4f,0.4f,
		0.5f,  0.5f,  0.5f,     0.4f,0.4f,0.4f,
		-0.5f,  0.5f,  0.5f,    0.4f,0.4f,0.4f,
		-0.5f,  0.5f, -0.5f,    0.4f,0.4f,0.4f,
		// Mid gray : start index 108
		-0.5f, -0.5f, 0.5f,    0.88f,0.88f,0.88f,
		0.5f, -0.5f, 0.5f,     0.88f,0.88f,0.88f,
		0.5f,  0.5f, 0.5f,     0.88f,0.88f,0.88f,
		0.5f,  0.5f, 0.5f,     0.88f,0.88f,0.88f,
		-0.5f,  0.5f, 0.5f,    0.88f,0.88f,0.88f,
		-0.5f, -0.5f, 0.5f,    0.88f,0.88f,0.88f,
		-0.5f, -0.5f,-0.5f,  0.88f,0.88f,0.88f,
		0.5f, -0.5f,-0.5f,    0.88f,0.88f,0.88f,
		0.5f,  0.5f,-0.5f,    0.88f,0.88f,0.88f,
		0.5f,  0.5f,-0.5f,    0.88f,0.88f,0.88f,
		-0.5f,  0.5f,-0.5f,  0.88f,0.88f,0.88f,
		-0.5f, -0.5f,-0.5f,    0.88f,0.88f,0.88f,
		0.5f, -0.5f,  0.5f,   0.88f,0.88f,0.88f,
		0.5f, -0.5f, -0.5f,   0.88f,0.88f,0.88f,
		0.5f,  0.5f, -0.5f,   0.88f,0.88f,0.88f,
		0.5f,  0.5f, -0.5f,   0.88f,0.88f,0.88f,
		0.5f,  0.5f,  0.5f,   0.88f,0.88f,0.88f,
		0.5f,  -0.5f, 0.5f,   0.88f,0.88f,0.88f,
		-0.5f,  0.5f,  0.5f,   0.88f,0.88f,0.88f,
		-0.5f,  0.5f, -0.5f,   0.88f,0.88f,0.88f,
		-0.5f, -0.5f, -0.5f,   0.88f,0.88f,0.88f,
		-0.5f, -0.5f, -0.5f,   0.88f,0.88f,0.88f,
		-0.5f, -0.5f,  0.5f,   0.88f,0.88f,0.88f,
		-0.5f,  0.5f,  0.5f,   0.88f,0.88f,0.88f,
		-0.5f, -0.5f, -0.5f,   0.88f,0.88f,0.88f,
		0.5f, -0.5f, -0.5f,    0.88f,0.88f,0.88f,
		0.5f, -0.5f,  0.5f,    0.88f,0.88f,0.88f,
		0.5f, -0.5f,  0.5f,    0.88f,0.88f,0.88f,
		-0.5f, -0.5f,  0.5f,   0.88f,0.88f,0.88f,
		-0.5f, -0.5f, -0.5f,   0.88f,0.88f,0.88f,
		-0.5f,  0.5f, -0.5f,   0.88f,0.88f,0.88f,
		0.5f,  0.5f, -0.5f,    0.88f,0.88f,0.88f,
		0.5f,  0.5f,  0.5f,    0.88f,0.88f,0.88f,
		0.5f,  0.5f,  0.5f,    0.88f,0.88f,0.88f,
		-0.5f,  0.5f,  0.5f,   0.88f,0.88f,0.88f,
		-0.5f,  0.5f, -0.5f,   0.88f,0.88f,0.88f,
		// White : start index 144
		-0.5f, -0.5f, 0.5f,     1.0f,1.0f,1.0f,
		0.5f, -0.5f, 0.5f,      1.0f,1.0f,1.0f,
		0.5f,  0.5f, 0.5f,      1.0f,1.0f,1.0f,
		0.5f,  0.5f, 0.5f,      1.0f,1.0f,1.0f,
		-0.5f,  0.5f, 0.5f,     1.0f,1.0f,1.0f,
		-0.5f, -0.5f, 0.5f,     1.0f,1.0f,1.0f,
		-0.5f, -0.5f,-0.5f,   1.0f,1.0f,1.0f,
		0.5f, -0.5f,-0.5f,     1.0f,1.0f,1.0f,
		0.5f,  0.5f,-0.5f,     1.0f,1.0f,1.0f,
		0.5f,  0.5f,-0.5f,     1.0f,1.0f,1.0f,
		-0.5f,  0.5f,-0.5f,   1.0f,1.0f,1.0f,
		-0.5f, -0.5f,-0.5f,     1.0f,1.0f,1.0f,
		0.5f, -0.5f,  0.5f,    1.0f,1.0f,1.0f,
		0.5f, -0.5f, -0.5f,    1.0f,1.0f,1.0f,
		0.5f,  0.5f, -0.5f,    1.0f,1.0f,1.0f,
		0.5f,  0.5f, -0.5f,    1.0f,1.0f,1.0f,
		0.5f,  0.5f,  0.5f,    1.0f,1.0f,1.0f,
		0.5f,  -0.5f, 0.5f,    1.0f,1.0f,1.0f,
		-0.5f,  0.5f,  0.5f,    1.0f,1.0f,1.0f,
		-0.5f,  0.5f, -0.5f,    1.0f,1.0f,1.0f,
		-0.5f, -0.5f, -0.5f,    1.0f,1.0f,1.0f,
		-0.5f, -0.5f, -0.5f,    1.0f,1.0f,1.0f,
		-0.5f, -0.5f,  0.5f,    1.0f,1.0f,1.0f,
		-0.5f,  0.5f,  0.5f,    1.0f,1.0f,1.0f,
		-0.5f, -0.5f, -0.5f,    1.0f,1.0f,1.0f,
		0.5f, -0.5f, -0.5f,     1.0f,1.0f,1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,1.0f,1.0f,
		0.5f, -0.5f,  0.5f,     1.0f,1.0f,1.0f,
		-0.5f, -0.5f,  0.5f,    1.0f,1.0f,1.0f,
		-0.5f, -0.5f, -0.5f,    1.0f,1.0f,1.0f,
		-0.5f,  0.5f, -0.5f,    1.0f,1.0f,1.0f,
		0.5f,  0.5f, -0.5f,     1.0f,1.0f,1.0f,
		0.5f,  0.5f,  0.5f,     1.0f,1.0f,1.0f,
		0.5f,  0.5f,  0.5f,     1.0f,1.0f,1.0f,
		-0.5f,  0.5f,  0.5f,    1.0f,1.0f,1.0f,
		-0.5f,  0.5f, -0.5f,    1.0f,1.0f,1.0f,
		// Red magnet: start index 180
		-0.5f, -0.5f, 0.5f,     0.96f,0.36f,0.33f,
		0.5f, -0.5f, 0.5f,      0.96f,0.36f,0.33f,
		0.5f,  0.5f, 0.5f,      0.96f,0.36f,0.33f,
		0.5f,  0.5f, 0.5f,      0.96f,0.36f,0.33f,
		-0.5f,  0.5f, 0.5f,     0.96f,0.36f,0.33f,
		-0.5f, -0.5f, 0.5f,     0.96f,0.36f,0.33f,
		-0.5f, -0.5f,-0.5f,   0.96f,0.36f,0.33f,
		0.5f, -0.5f,-0.5f,     0.96f,0.36f,0.33f,
		0.5f,  0.5f,-0.5f,     0.96f,0.36f,0.33f,
		0.5f,  0.5f,-0.5f,     0.96f,0.36f,0.33f,
		-0.5f,  0.5f,-0.5f,   0.96f,0.36f,0.33f,
		-0.5f, -0.5f,-0.5f,     0.96f,0.36f,0.33f,
		0.5f, -0.5f,  0.5f,    0.96f,0.36f,0.33f,
		0.5f, -0.5f, -0.5f,    0.96f,0.36f,0.33f,
		0.5f,  0.5f, -0.5f,    0.96f,0.36f,0.33f,
		0.5f,  0.5f, -0.5f,    0.96f,0.36f,0.33f,
		0.5f,  0.5f,  0.5f,    0.96f,0.36f,0.33f,
		0.5f,  -0.5f, 0.5f,    0.96f,0.36f,0.33f,
		-0.5f,  0.5f,  0.5f,    0.96f,0.36f,0.33f,
		-0.5f,  0.5f, -0.5f,    0.96f,0.36f,0.33f,
		-0.5f, -0.5f, -0.5f,    0.96f,0.36f,0.33f,
		-0.5f, -0.5f, -0.5f,    0.96f,0.36f,0.33f,
		-0.5f, -0.5f,  0.5f,    0.96f,0.36f,0.33f,
		-0.5f,  0.5f,  0.5f,    0.96f,0.36f,0.33f,
		-0.5f, -0.5f, -0.5f,    0.96f,0.36f,0.33f,
		0.5f, -0.5f, -0.5f,     0.96f,0.36f,0.33f,
		0.5f, -0.5f,  0.5f,     0.96f,0.36f,0.33f,
		0.5f, -0.5f,  0.5f,     0.96f,0.36f,0.33f,
		-0.5f, -0.5f,  0.5f,    0.96f,0.36f,0.33f,
		-0.5f, -0.5f, -0.5f,    0.96f,0.36f,0.33f,
		-0.5f,  0.5f, -0.5f,    0.96f,0.36f,0.33f,
		0.5f,  0.5f, -0.5f,     0.96f,0.36f,0.33f,
		0.5f,  0.5f,  0.5f,     0.96f,0.36f,0.33f,
		0.5f,  0.5f,  0.5f,     0.96f,0.36f,0.33f,
		-0.5f,  0.5f,  0.5f,    0.96f,0.36f,0.33f,
		-0.5f,  0.5f, -0.5f,    0.96f,0.36f,0.33f,
		// Blue magnet: start index 216
		-0.5f, -0.5f, 0.5f,     0.33f,0.85f,0.96f,
		0.5f, -0.5f, 0.5f,      0.33f,0.85f,0.96f,
		0.5f,  0.5f, 0.5f,      0.33f,0.85f,0.96f,
		0.5f,  0.5f, 0.5f,      0.33f,0.85f,0.96f,
		-0.5f,  0.5f, 0.5f,     0.33f,0.85f,0.96f,
		-0.5f, -0.5f, 0.5f,     0.33f,0.85f,0.96f,
		-0.5f, -0.5f,-0.5f,   0.33f,0.85f,0.96f,
		0.5f, -0.5f,-0.5f,     0.33f,0.85f,0.96f,
		0.5f,  0.5f,-0.5f,     0.33f,0.85f,0.96f,
		0.5f,  0.5f,-0.5f,     0.33f,0.85f,0.96f,
		-0.5f,  0.5f,-0.5f,   0.33f,0.85f,0.96f,
		-0.5f, -0.5f,-0.5f,     0.33f,0.85f,0.96f,
		0.5f, -0.5f,  0.5f,    0.33f,0.85f,0.96f,
		0.5f, -0.5f, -0.5f,    0.33f,0.85f,0.96f,
		0.5f,  0.5f, -0.5f,    0.33f,0.85f,0.96f,
		0.5f,  0.5f, -0.5f,    0.33f,0.85f,0.96f,
		0.5f,  0.5f,  0.5f,    0.33f,0.85f,0.96f,
		0.5f,  -0.5f, 0.5f,    0.33f,0.85f,0.96f,
		-0.5f,  0.5f,  0.5f,    0.33f,0.85f,0.96f,
		-0.5f,  0.5f, -0.5f,    0.33f,0.85f,0.96f,
		-0.5f, -0.5f, -0.5f,    0.33f,0.85f,0.96f,
		-0.5f, -0.5f, -0.5f,    0.33f,0.85f,0.96f,
		-0.5f, -0.5f,  0.5f,    0.33f,0.85f,0.96f,
		-0.5f,  0.5f,  0.5f,    0.33f,0.85f,0.96f,
		-0.5f, -0.5f, -0.5f,    0.33f,0.85f,0.96f,
		0.5f, -0.5f, -0.5f,     0.33f,0.85f,0.96f,
		0.5f, -0.5f,  0.5f,     0.33f,0.85f,0.96f,
		0.5f, -0.5f,  0.5f,     0.33f,0.85f,0.96f,
		-0.5f, -0.5f,  0.5f,    0.33f,0.85f,0.96f,
		-0.5f, -0.5f, -0.5f,    0.33f,0.85f,0.96f,
		-0.5f,  0.5f, -0.5f,    0.33f,0.85f,0.96f,
		0.5f,  0.5f, -0.5f,     0.33f,0.85f,0.96f,
		0.5f,  0.5f,  0.5f,     0.33f,0.85f,0.96f,
		0.5f,  0.5f,  0.5f,     0.33f,0.85f,0.96f,
		-0.5f,  0.5f,  0.5f,    0.33f,0.85f,0.96f,
		-0.5f,  0.5f, -0.5f,    0.33f,0.85f,0.96f,
		// Black: start index 252
		-0.5f, -0.5f, 0.5f,     0.0f,0.0f,0.0f,
		0.5f, -0.5f, 0.5f,      0.0f,0.0f,0.0f,
		0.5f,  0.5f, 0.5f,      0.0f,0.0f,0.0f,
		0.5f,  0.5f, 0.5f,      0.0f,0.0f,0.0f,
		-0.5f,  0.5f, 0.5f,     0.0f,0.0f,0.0f,
		-0.5f, -0.5f, 0.5f,     0.0f,0.0f,0.0f,
		-0.5f, -0.5f,-0.5f,   0.0f,0.0f,0.0f,
		0.5f, -0.5f,-0.5f,     0.0f,0.0f,0.0f,
		0.5f,  0.5f,-0.5f,     0.0f,0.0f,0.0f,
		0.5f,  0.5f,-0.5f,     0.0f,0.0f,0.0f,
		-0.5f,  0.5f,-0.5f,   0.0f,0.0f,0.0f,
		-0.5f, -0.5f,-0.5f,     0.0f,0.0f,0.0f,
		0.5f, -0.5f,  0.5f,    0.0f,0.0f,0.0f,
		0.5f, -0.5f, -0.5f,    0.0f,0.0f,0.0f,
		0.5f,  0.5f, -0.5f,    0.0f,0.0f,0.0f,
		0.5f,  0.5f, -0.5f,    0.0f,0.0f,0.0f,
		0.5f,  0.5f,  0.5f,    0.0f,0.0f,0.0f,
		0.5f,  -0.5f, 0.5f,    0.0f,0.0f,0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,0.0f,0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,0.0f,0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,0.0f,0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,0.0f,0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,0.0f,0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,0.0f,0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,0.0f,0.0f,
		0.5f, -0.5f, -0.5f,     0.0f,0.0f,0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,0.0f,0.0f,
		0.5f, -0.5f,  0.5f,     0.0f,0.0f,0.0f,
		-0.5f, -0.5f,  0.5f,    0.0f,0.0f,0.0f,
		-0.5f, -0.5f, -0.5f,    0.0f,0.0f,0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,0.0f,0.0f,
		0.5f,  0.5f, -0.5f,     0.0f,0.0f,0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,0.0f,0.0f,
		0.5f,  0.5f,  0.5f,     0.0f,0.0f,0.0f,
		-0.5f,  0.5f,  0.5f,    0.0f,0.0f,0.0f,
		-0.5f,  0.5f, -0.5f,    0.0f,0.0f,0.0f,
	};

	// Índices de color:
	// - Light blue: 0
	// - Red Magnet: 180
	// - Blue Magnet: 216
	// - Low gray: 36
	// - Mid gray: 108
	// - High gray: 72 
	// - Black: 252
	// - White: 144

	GLint lightBlueIndex = 0;
	GLint redMagnetIndex = 180;
	GLint blueMagnetIndex = 216;
	GLint lowGrayIndex = 36;
	GLint midGrayIndex = 108;
	GLint highGrayIndex = 72;
	GLint blackIndex = 252;
	GLint whiteIndex = 144;

	GLclampf redBackgroundColor = 0.13f;
	GLclampf greenBackgroundColor = 0.13f;
	GLclampf blueBackgroundColor = 0.13f;


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	
	glm::mat4 projection=glm::mat4(1);

	projection = glm::perspective(glm::radians(45.0f), (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);//FOV, Radio de aspecto,znear,zfar

	while (!glfwWindowShouldClose(window)) {
		
		Inputs(window);

		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(redBackgroundColor, greenBackgroundColor, blueBackgroundColor, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY-0.2f, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);
	
		// ---------------------------------
		// Dibujo de MAGNETON
		// ---------------------------------

		// ---------------------------------
		// 
		// Cuerpo
		model = glm::mat4(1.0f);
		model = glm::scale(model, glm::vec3(2, 2, 2));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, lightBlueIndex, 36);

		// Ojo 
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.65f));
		model = glm::scale(model, glm::vec3(1.0f, 0.9f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, whiteIndex, 36);

		// Pupila
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.2f, 0.7f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, blackIndex, 36);

		// Cruz izquierda
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.6f, -0.6f, 1.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, lowGrayIndex, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.6f, -0.6f, 0.9f));
		model = glm::scale(model, glm::vec3(0.3f, 0.09f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, highGrayIndex, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.6f, -0.6f, 0.9f));
		model = glm::scale(model, glm::vec3(0.09f, 0.3f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, highGrayIndex, 36);


		// Cruz derecha
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.6f, -0.6f, 1.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, lowGrayIndex, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.6f, -0.6f, 0.9f));
		model = glm::scale(model, glm::vec3(0.3f, 0.09f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, highGrayIndex, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.6f, -0.6f, 0.9f));
		model = glm::scale(model, glm::vec3(0.09f, 0.3f, 0.8f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, highGrayIndex, 36);
		// ---------------------------------


		// ---------------------------------
		// Cruz superior
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.125f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.25f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, lowGrayIndex, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.375f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.25f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, highGrayIndex, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.25f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, lowGrayIndex, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.75f, 0.0f));
		model = glm::scale(model, glm::vec3(1.2f, 0.25f, 1.2f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, lowGrayIndex, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.9f, 0.25f, 0.25f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, highGrayIndex, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.8f, 0.0f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.9f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, highGrayIndex, 36);
		// ---------------------------------

		// ---------------------------------
		// Left Arm
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.125f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 1.3f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, midGrayIndex, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.3f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.2f, 0.35f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, midGrayIndex, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.075f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, redMagnetIndex, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-1.3f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.2f, 0.35f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, midGrayIndex, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.075f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, blueMagnetIndex, 36);

		// Right Arm
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.125f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.5f, 1.3f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, midGrayIndex, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.3f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.2f, 0.35f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, midGrayIndex, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.075f, 0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, redMagnetIndex, 36);

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(1.3f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(1.2f, 0.35f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, midGrayIndex, 36);
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.075f, -0.5f, 0.0f));
		model = glm::scale(model, glm::vec3(0.35f, 0.35f, 0.35f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, blueMagnetIndex, 36);
		// ---------------------------------

		// Finish
		glBindVertexArray(0);	
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 double offset = 0.02;
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += offset;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= offset;
	 if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		 movY += 0.005;
	 if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		 movY -= 0.005;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= offset;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += offset;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += offset;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= offset;
 }


