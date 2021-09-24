/*
	Alumno: Néstor I. Martínez Ostoa
	No. Cuenta: 315618648
	Script: Práctica 2 - 7 cubos en pantalla con vista en perspectiva
	Fecha: 23 de sept del 2021

*/

#include<iostream>
using namespace std;

// GLM, GLFW, GLEW headers
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

// Shaders
#include "Shader.h"

const GLint WIDTH = 800, HEIGHT = 600;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Practica 2 - Néstor I. Martínez Ostoa", nullptr, nullptr);
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

	glViewport(0, 0, screenWidth, screenHeight);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	Shader ourShader("Shader/core.vs", "Shader/core.frag");
	
	// Perspective Projection
	float vertices[] = {
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,// Front - Red
		0.5f, -0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		0.5f,  0.5f, 0.5f,  1.0f, 0.0f,0.0f,
		-0.5f,  0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		-0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,
		
	    -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,// Back - Green
		 0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		 0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	    -0.5f,  0.5f,-0.5f, 0.0f, 1.0f,0.0f,
	    -0.5f, -0.5f,-0.5f, 0.0f, 1.0f,0.0f,
		
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,1.0f, //Right - Blue
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f, 0.0f,1.0f,
		 0.5f,  -0.5f, 0.5f, 0.0f, 0.0f,1.0f,
      
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f, // Left - Yellow
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f, -0.5f,  1.0f, 1.0f,0.0f,
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,0.0f,
		
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f, // Bottom - Light Blue
		0.5f, -0.5f, -0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,1.0f,
		-0.5f, -0.5f,  0.5f, 0.0f, 1.0f,1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f,1.0f,
		
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f, // Top - Light Pink
		0.5f,  0.5f, -0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		0.5f,  0.5f,  0.5f,  1.0f, 0.2f,0.5f,
		-0.5f,  0.5f,  0.5f, 1.0f, 0.2f,0.5f,
		-0.5f,  0.5f, -0.5f, 1.0f, 0.2f,0.5f,
	};


	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	
	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	

	// Matriz de proyección
	glm::mat4 projection=glm::mat4(1);


	// (FOV, Radio de aspecto, znear, zfar)
	projection = glm::perspective(45.0f, (GLfloat)screenWidth / (GLfloat)screenHeight, 0.1f, 100.0f);


	// Dibujo en pantalla
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ourShader.Use();
		glm::mat4 view=glm::mat4(1);
	
		view = glm::translate(view, glm::vec3(0.0f,0.0f,-8.0f));
		//model = glm::rotate( model, glm::radians(25.0f), glm::vec3( 1.0f, 0.0f, 0.0f ) ); // use to compare orthographic and perspective projection
		//model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		//view = glm::translate( view, glm::vec3( screenWidth / 2, screenHeight / 2, 0 ) ); // use with orthographic projection
		
		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");
		
		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		glBindVertexArray(VAO);

		// ------------------------------------------------------
		// Dibujo de los cubos:
		// -------------------
		// 
		// 1. Definición de la matriz model (representará a un cubo) - glm::mat4
		// 2. Definición de la traslación y rotación del modelo - glm::translate y glm::rotate
		// 3. Mandar información al shader - glUniformMatriz4vf()
		// 4. Dibujar matriz model - glDrawArrays()
		// ------------------------------------------------------
		
		// Cubo central
		mat4 model = mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Cubo a la derecha del central
		model = mat4(1);
		model = translate(model, vec3(2, 0, 0));
		model = rotate(model, radians(-11.0f - 90.0f), vec3(0, 1, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Cubo a la izquierda del central
		model = mat4(1);
		model = translate(model, vec3(-2, 0, 0));
		model = rotate(model, radians(11.0f + 90.0f), vec3(0, 1, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Cubo en diagonal derecha por arriba del central
		model = mat4(1);
		model = translate(model, vec3(1, 3, 0));
		model = rotate(model, radians(-4.0f), vec3(0, 1, 0));
		model = rotate(model, radians(-90.0f + 17.0f), vec3(1, 0, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Cubo en diagonal izquierda por arriba del central
		model = mat4(1);
		model = translate(model, vec3(-1, 3, 0));
		model = rotate(model, radians(4.0f), vec3(0, 1, 0));
		model = rotate(model, radians(90.0f + 17.0f), vec3(1, 0, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Cubo en diagonal derecha debajo del central
		model = mat4(1);
		model = translate(model, vec3(1, -3, 0));
		model = rotate(model, radians(-180.0f - 4.0f), vec3(0, 1, 0));
		model = rotate(model, radians(18.0f), vec3(1, 0, 0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Cubo en diagonal izquierda debajo del central
		model = mat4(1);
		model = translate(model, vec3(-1, -3, 0));
		model = rotate(model, radians(-22.0f), vec3(1, 0, 0)); 
		model = rotate(model, radians(9.0f), vec3(0, 1, 0)); 
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, value_ptr(model));
		glDrawArrays(GL_TRIANGLES, 0, 36);


		// Finalización
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glfwTerminate();
	return EXIT_SUCCESS;
}


