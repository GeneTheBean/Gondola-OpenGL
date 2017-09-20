#ifndef SHADER_H
#define SHADER_H

//Local headers
#include "glitter.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp> // after <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/ext.hpp"          // to print vectors and matrices

//Standard headers
#include <vector>

#include "SceneNode.h";
#include "TriangleStrip.h";
#include "TriangleFan.h";

// define macros for convenience
#define BROWN 1.0, 0.4, 0.2   
#define YELLOW 1.0, 0.9, 0.2 
#define PINK 1.0, 0, 0.3
#define BLACK 0, 0, 0


class Gondola : public SceneNode {
public:
	Gondola(GLuint shaderProgram) {
		this -> shaderProgram = shaderProgram;
		setUpGondola();
	}

	void Gondola::setUpGondola() {
		GLfloat headShape[] = {
			0,  0, BROWN,
			-0.5,  0, BROWN,
			-0.5, 0.5, BROWN,
			-0.45, 1.0, BROWN,
			-0.4, 1.3, BROWN,
			-0.2, 1.7, BROWN,
			0, 1.75, BROWN,
			0.2, 1.7, BROWN,
			0.4, 1.3, BROWN,
			0.45, 1.0, BROWN,
			0.5, 0.5, BROWN,
			0.5,  0, BROWN
		};

		GLuint headElements[] = {
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
		};

		GLfloat snoutShape[] = {
			-0.3, .8, YELLOW,
			-0.2, 0.9, YELLOW,
			-0.2, 0.7, YELLOW,
			0, 0.9, YELLOW,
			0.2, 0.9, YELLOW,
			0.2, 0.7, YELLOW,
			0.3, 0.8, YELLOW,
		};

		GLuint snoutElements[] = {
			0, 1, 2,
			1, 2, 3,
			3, 4, 5,
			4, 5, 6
		};

		GLfloat rightEye[] = {
			-0.08, 0.9, BLACK,
			0, 1.0, BLACK,
			0, 0.8, BLACK,
			0.08, 0.9, BLACK,
		};

		GLfloat leftEye[] = {
			-0.08, 0.9, BLACK,
			0, 1.0, BLACK,
			0, 0.8, BLACK,
			0.08, 0.9, BLACK,
		};

	
		GLuint eyeElements[] = {
			0, 1, 2, 3
		};

		GLfloat mouthShape[] = {
			-0.2, 0.7, PINK,
			0, 0.9, PINK,
			0, 0.65, PINK,
			0.2, 0.7, PINK,
		};

		GLuint mouthElements[] = {
			0, 1, 2, 3
		};

		GLfloat noseShape[] = {
			-0.1, 0.9, BLACK,
			0, 1.0, BLACK,
			0, 0.8, BLACK,
			0.1, 0.9, BLACK,
		};

		GLuint noseElements[] = {
			0, 1, 2, 3
		};

		GLfloat leftWaist[] = {
			-0.5,  0, BROWN,
			-0.5, -0.2, BROWN,
			-0.2, -0.2, BROWN,
			-0.15, -0.1, BROWN,
			0, 0, BROWN
		};

		GLfloat rightWaist[] = {
			0.5,  0, BROWN,
			0.5, -0.2, BROWN,
			0.2, -0.2, BROWN,
			0.15, -0.1, BROWN,
			0, 0, BROWN
		};

		GLuint waistElements[] = {
			0, 1, 2, 3, 4
		};
		
		GLfloat leftLeg[] = {
			-0.5f,  -0.2, BROWN,
			-0.2,  -0.2, BROWN,
			-0.2, -7.0f, BROWN,
			-0.5f, -7.0f, BROWN  
		};

		GLfloat rightLeg[] = {
			-0.5f,  -0.2, BROWN,
			-0.2,  -0.2, BROWN,
			-0.2, -7.0f, BROWN,
			-0.5f, -7.0f, BROWN
		};

		GLuint legElements[] = {
			0, 1, 2,
			2, 3, 0
		};

		//Intialize head
		head = new TriangleFan(headShape, sizeof(headShape), headElements, sizeof(headElements), sizeof(headElements)/sizeof(headElements[0]), shaderProgram);
		this->addChild(head);
		
		//Intialize face
		face = new SceneNode();
		head->addChild(face);
		snout = new SceneNode(snoutShape, sizeof(snoutShape), snoutElements, sizeof(snoutElements), sizeof(snoutElements) / sizeof(snoutElements[0]), shaderProgram);
		mouth = new TriangleStrip(mouthShape, sizeof(mouthShape), mouthElements, sizeof(mouthElements), sizeof(mouthElements) / sizeof(mouthElements[0]), shaderProgram);
		nose = new TriangleStrip(noseShape, sizeof(noseShape), noseElements, sizeof(noseElements), sizeof(noseElements) / sizeof(noseElements[0]), shaderProgram);
		snout->addChild(mouth);
		snout->addChild(nose);
		face->addChild(snout);
		eyes = new SceneNode();
		r_eye = new TriangleStrip(rightEye, sizeof(rightEye), eyeElements, sizeof(eyeElements), sizeof(eyeElements) / sizeof(eyeElements[0]), shaderProgram);
		l_eye = new TriangleStrip(rightEye, sizeof(rightEye), eyeElements, sizeof(eyeElements), sizeof(eyeElements) / sizeof(eyeElements[0]), shaderProgram);
		eyes->addChild(r_eye);
		eyes->addChild(l_eye);
		face->addChild(eyes);

		//Initialize waist
		waist = new SceneNode();
		head->addChild(waist);
		l_waist = new TriangleFan(leftWaist, sizeof(leftWaist), waistElements, sizeof(waistElements), sizeof(waistElements) / sizeof(waistElements[0]), shaderProgram);
		r_waist = new TriangleFan(rightWaist, sizeof(rightWaist), waistElements, sizeof(waistElements), sizeof(waistElements) / sizeof(waistElements[0]), shaderProgram);
		waist->addChild(l_waist);
		waist->addChild(r_waist);
		
		l_leg = new SceneNode(leftLeg, sizeof(leftLeg), legElements, sizeof(legElements), sizeof(legElements) / sizeof(legElements[0]), shaderProgram);
		r_leg = new SceneNode(rightLeg, sizeof(rightLeg), legElements, sizeof(legElements), sizeof(legElements) / sizeof(legElements[0]), shaderProgram);
		l_waist->addChild(l_leg);
		r_waist->addChild(r_leg);
		
		head->scale(glm::mat4(1.0), glm::vec3(0.2, 0.2 , 1.0));
		head->translate(glm::vec3(0, -5.0, 0));
		r_eye->translate(glm::vec3(0.18, 0, 0));
		l_eye->translate(glm::vec3(-0.18, 0, 0));
		eyes->translate(glm::vec3(0, 0.23, 0));
		r_leg->translate(glm::vec3(0.7, 0, 0));
	}


	void Gondola::display() {
		face->rotate(0.0005, glm::vec3(0, 0, 1.0));
		eyes->rotate(005, glm::vec3(0, 1.0, 0));
		translate(glm::vec3(0, 0.001, 0));
		draw();
	}

	private: 
		SceneNode* head;
		
		SceneNode* face;
		SceneNode* eyes;
		SceneNode* snout;
		SceneNode* mouth;
		SceneNode* nose;
		SceneNode* l_eye;
		SceneNode* r_eye;
		
		SceneNode* waist;
		SceneNode* l_waist;
		SceneNode* r_waist;
		SceneNode* l_leg;
		SceneNode* r_leg;
		SceneNode* l_foot;
		SceneNode* r_foot;
};
#endif

