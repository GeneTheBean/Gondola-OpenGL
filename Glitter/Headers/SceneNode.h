#pragma once
// Local Headers
#include "glitter.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"          // to print vectors and matrices
#include <iostream>
#include <vector>

class SceneNode {
	public:
		SceneNode(){} //Default Constructor

		//Initalize all the variables needed for the setup, then sets up the mesh
		SceneNode(GLfloat vertices[], const int vSize, GLuint elements[], const int eSize, int drawCount, GLuint shaderProgram) {
			this->vertices = vertices;
			this->vSize = vSize;
			this->elements = elements;
			this->eSize = eSize;
			this->drawCount = drawCount;
			this->shaderProgram = shaderProgram;
			parent = NULL;

			setUpMesh();
		}
	
		//Creates vertex, buffer, and element arrays and binds them
		void SceneNode::setUpMesh() {
			// Create Vertex Array Object
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);
	
			// Create a Vertex Buffer Object and copy the vertex data to it
			glGenBuffers(1, &vbo);
	
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vSize, vertices, GL_STATIC_DRAW);
	
			// Create an element array
			glGenBuffers(1, &ebo);
	
			bindVertices();
		}
		
		//Sets up how the gpu will interpret the data passed by the constructor
		void SceneNode::bindVertices() {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, eSize, elements, GL_STATIC_DRAW);
	
			glBindVertexArray(vao);
			// Specify the layout of the vertex data
			// position
			GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
			glEnableVertexAttribArray(posAttrib);
			glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), 0);  // attribute location, # values, value type, normalize?, stride, offset
																							  // color
			GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
			glEnableVertexAttribArray(colAttrib);
			glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
		}
		
		//Renders the current node and draws its children nodes
		virtual void SceneNode::draw() {
			if (this != NULL)
				render();	//render the current node

			if (!children.empty()) {
				for (int i = 0; i < children.size(); i++) {	//render its children
					children.at(i)->draw();
				}
			}
		}

		//Renders the scene node using GL_TRIANGLES by Default
		virtual void SceneNode::render() {
			glBindVertexArray(vao);
			glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(transform));
			glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}
		
		void SceneNode::translate(glm::vec3 addVector) {	//Any translation will be also applied to its children nodes
			if (this != NULL)
				transform = glm::translate(transform, addVector);
			
			if (!children.empty()) {
				for (int i = 0; i < children.size(); i++) {	//translate its children
					children.at(i)->translate(addVector);
				}
			}
		}
	
		void SceneNode::rotate(GLfloat angle, glm::vec3 rotVector) {	//Any rotation will be also applied to its children nodes
			if (this != NULL)
				transform = glm::rotate(transform, glm::radians(angle), rotVector);
			
			if (!children.empty()) {
				for (int i = 0; i < children.size(); i++) {	//rotate its children
					children.at(i)->rotate(angle, rotVector);
				}
			}
		}
	
		void SceneNode::scale(glm::mat4 scaleMatrix, glm::vec3 scaleVector) {	//Any scaling will be also applied to its children nodes
			if (this != NULL)
				transform = glm::scale(scaleMatrix, scaleVector);
			
			if (!children.empty()) {
				for (int i = 0; i < children.size(); i++) {	//scale its children
					children.at(i)->scale(scaleMatrix, scaleVector);
				}
			}
		}
		
		//Sets the parent to this and adds the node to the children vector
		void SceneNode::addChild(SceneNode* s) {
			children.push_back(s);
			s->parent = this;
		}

		//Returns child SceneNode
		SceneNode* getChild(unsigned int i) {
			return children.at(i);
		}

	protected:
		GLfloat* vertices; //Stores vertices of the mesh
		GLuint* elements;	//Stores element data of the mesh
		glm::mat4 transform; //Stores transform of mesh
		SceneNode *parent;	//Reference to the parent node
		std::vector<SceneNode*> children; //Container of sceneNode children
		GLuint vao, vbo, ebo, shaderProgram; //Pipeline variables
		int drawCount; //number of elements to draw
		int vSize; //sizeof(vertices)
		int eSize; //sizeof(elements)
	
};