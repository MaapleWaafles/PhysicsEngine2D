#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include "_AABB.h"
#include "_Circle.h"
#include "_Plane.h"
#include "_RigidBody.h"
#include "_PhysicsScene.h"

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
	_Circle*            m_circle;
	_Circle*            m_circle2;
	_Circle*            m_circle3;
	_AABB*              m_square3;
	_AABB*              m_square;
	_AABB*              m_square2;
	_PhysicsScene*      m_scene;
	_Plane*             m_plane;
	_Plane*             m_plane2;
	_Plane*             m_plane3;
	_Plane*             m_plane4;
};