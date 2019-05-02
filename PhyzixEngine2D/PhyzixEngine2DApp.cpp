#include "PhyzixEngine2DApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>
#include <glm/ext.hpp>
using std::cout;
using std::endl;

PhyzixEngine2DApp::PhyzixEngine2DApp() {

}

PhyzixEngine2DApp::~PhyzixEngine2DApp() {

}

bool PhyzixEngine2DApp::startup() {
	
	//increase the 2D line count to maximize the number of objects we can draw
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	m_scene = new _PhysicsScene();
	m_scene->setTimeStep(0.01f);
	m_scene->setGravity(glm::vec2(0.0f, -15.0f));

	m_circle = new _Circle(glm::vec2(20.0f, 20.0f), glm::vec2(0.0f, 0.0f), 12, 1.0f, 0.0f, 1.0f, 3.0f, glm::vec4(1, 0, 0, 1));
	m_circle2 = new _Circle(glm::vec2(20.0f, -20.0f), glm::vec2(0.0f, 0.0f), 12, 1.0f, 0.0f, 1.0f, 3.0f, glm::vec4(1, 0, 0, 1));

	m_circle3 = new _Circle(glm::vec2(-5.0f, -20.0f), glm::vec2(0.0f, 0.0f), 12, 1.0f, 0.0f, 1.0f, 3.0f, glm::vec4(1, 0, 0, 1));

	m_square3 = new _AABB(glm::vec2(20.0f, -30.0f), glm::vec2(5.0f, 5.0f), glm::vec2(0.0f, 0.0f), 0.0f, 0.0f, 1.0f, glm::vec4(0, 1, 1, 1));
	m_square = new _AABB(glm::vec2(-20.0f, 20.0f), glm::vec2(5.0f, 5.0f), glm::vec2(0.0f, 0.0f), 0.0f, 0.0f, 1.0f, glm::vec4(0, 1, 1, 1));
	m_square2 = new _AABB(glm::vec2(-20.0f, -20.0f), glm::vec2(5.0f, 5.0f), glm::vec2(0.0f, 0.0f), 0.0f, 0.0f, 1.0f, glm::vec4(0, 1, 1, 1));

	m_plane = new _Plane(glm::normalize(glm::vec2(0, -1)), -40.0f, glm::vec4(0, 0, 1, 1));
	m_plane2 = new _Plane(glm::normalize(glm::vec2(1, -1)), -60.0f, glm::vec4(0, 1, 0, 1));

	m_plane3 = new _Plane(glm::normalize(glm::vec2(0, 1)), -40.0f, glm::vec4(0, 0, 1, 1));
    m_plane4 = new _Plane(glm::normalize(glm::vec2(-1, 1)), -60.0f, glm::vec4(0, 1, 0, 1));

	m_circle->setElasticity(0.9f);
	m_circle->setKinematic(false);

	m_circle2->setElasticity(0.9f);
	m_circle2->setKinematic(true);

	m_square->setElasticity(0.9f);
	m_square->setKinematic(false);

	m_square2->setElasticity(0.9f);
	m_square2->setKinematic(true);
			
	m_circle3->setElasticity(0.9f);
	m_circle3->setKinematic(false);

	m_square3->setElasticity(0.9f);
	m_square3->setKinematic(false);

	m_scene->addActor(m_square);
	m_scene->addActor(m_square2);
	m_scene->addActor(m_square3);
	m_scene->addActor(m_circle3);
	m_scene->addActor(m_circle);
	m_scene->addActor(m_circle2);
	m_scene->addActor(m_plane);
	m_scene->addActor(m_plane2);
	m_scene->addActor(m_plane3);
	m_scene->addActor(m_plane4);

	m_square3->applyForce(glm::vec2(0.0f, 20.0f));
	//m_circle->applyForce(glm::vec2(-50.0f, -50.0f));

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	return true;
}

void PhyzixEngine2DApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
	aie::Gizmos::destroy();
}

void PhyzixEngine2DApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	aie::Gizmos::clear();

	m_scene->update(deltaTime);
	m_scene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhyzixEngine2DApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16 / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}