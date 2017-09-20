#pragma once
// Local Headers
#include "glitter.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"          // to print vectors and matrices

#include "SceneNode.h"
#include <vector>

class TriangleFan : public SceneNode {
	public:
		TriangleFan(GLfloat vertices[], const int vSize, GLuint elements[], const int eSize, int drawCount, GLuint shaderProgram)
		: SceneNode(vertices, vSize, elements, eSize, drawCount, shaderProgram) {}

		//Renders the scene node using GL_TRIANGLE_STRIP
		virtual void TriangleFan::render() {
			glBindVertexArray(vao);
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(transform));
			glDrawElements(GL_TRIANGLE_FAN, drawCount, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
};