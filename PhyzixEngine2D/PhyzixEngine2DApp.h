#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "AABB.h"
#include "Circle.h"
#include "Plane.h"
#include "RigidBody.h"
#include "PhysicsScene.h"

class PhyzixEngine2DApp : public aie::Application {
public:

	PhyzixEngine2DApp();
	virtual ~PhyzixEngine2DApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	Circle*            m_circle;
	Circle*            m_circle2;
	Circle*            m_circle3;
	AABB*              m_square3;
	AABB*              m_square;
	AABB*              m_square2;
	PhysicsScene*      m_scene;
	Plane*             m_plane;
	Plane*             m_plane2;
	Plane*             m_plane3;
	Plane*             m_plane4;
};