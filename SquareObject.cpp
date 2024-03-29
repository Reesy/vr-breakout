#pragma unmanaged
#include "SquareObject.h"


SquareObject::SquareObject()
{
}


SquareObject::~SquareObject()
{
}

void SquareObject::draw(glm::mat4 &view, glm::mat4 &projection){
	if (this->initialised){

		localShader.Use();

		glm::mat4 model;


		model = glm::scale(model, this->getSize());
		model = glm::translate(model, this->getPosition());
		


		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));
		glUniform3fv(colorLocation, 1, glm::value_ptr(color));

		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);

		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);


	}

}

void SquareObject::init(GLfloat inVertss[], Shader drawShader){
	this->initialised = true;
	this->localShader = drawShader;
	GLfloat inVerts[] = {
		// Positions
		0.5f, 0.5f, 0.0f,  // Top Right
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, 0.5f, 0.0f,  // Top Left

		// Second triangle
		0.5f, -0.5f, 0.0f,  // Bottom Right
		-0.5f, -0.5f, 0.0f,  // Bottom Left
		-0.5f, 0.5f, 0.0f   // Top Left
	};
	modelLocation = glGetUniformLocation(localShader.Program, "model");
	viewLocation = glGetUniformLocation(localShader.Program, "view");
	projectionLocation = glGetUniformLocation(localShader.Program, "projection");
	colorLocation = glGetUniformLocation(localShader.Program, "inColor");


	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(inVerts), inVerts, GL_STATIC_DRAW);


	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0); // Unbind VAO

}
