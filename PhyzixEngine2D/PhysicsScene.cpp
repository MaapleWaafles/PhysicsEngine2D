#include "PhysicsScene.h"
#include "RigidBody.h"
#include <iostream>
#include <list>
#include "Circle.h"
#include "AABB.h"
#include "Plane.h"
#include <limits>
using std::list;
using std::cout;
using std::endl;

//Setup for the Function Pointer
typedef bool(*fn)(PhysicsObject*, PhysicsObject*);

//Function Pointer that will pass into its specific collision function based on shape ID's
static fn CollisionFunctionArray[] = {
	PhysicsScene::planetoplane, PhysicsScene::planetocircle, PhysicsScene::planetosquare,
	PhysicsScene::circletoplane, PhysicsScene::circletocircle, PhysicsScene::circletosquare,
	PhysicsScene::squaretoplane, PhysicsScene::squaretocircle, PhysicsScene::squaretosquare,
};

//Settung variables to Zero
PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0)) { }

PhysicsScene::~PhysicsScene()
{
	//For all actors contained
	for (auto actor : m_actors) {
		//Delets all the actors
		delete actor;
	}
}

void PhysicsScene::addActor(PhysicsObject * actor)
{
	//Adds the actor to the back of the Vector
	m_actors.push_back(actor);
}

bool PhysicsScene::removeActor(PhysicsObject * actor)
{
	//For each index within the vector's size
	for (unsigned i = 0; i < m_actors.size(); ++i) {
		//If the index is the actor we want
		if (m_actors[i] == actor) {
			//Erase that actor
			m_actors.erase(m_actors.begin() + i);
			//Return True when done
			return true;
		}
	}
	//If Null or no actor found return false
	return false;
}

void PhysicsScene::update(float deltaTime)
{
	//Each Frame will get the deltaTime
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	//While the accumulated time is greater than or equal to the timestep 
	while (accumulatedTime >= m_timeStep) {
		//for all the physics objects within the container
		for (auto pActor : m_actors) {
			//Use Fixed Update which renders different frameratezs
			pActor->fixedUpdate(m_gravity, m_timeStep);
		}
		//accumulated time decreases the timestep
		accumulatedTime -= m_timeStep;

		// check for collisions (ideally you'd want to have some sort of scene management in place)
		checkForCollision();
	}
}

void PhysicsScene::checkForCollision()
{
	//Counts how many actors are in the container
	int actorCount = m_actors.size();

	//need to check for collisions against all object except this one
	for (int outer = 0; outer < actorCount - 1; outer++) {
		for (int inner = outer + 1; inner < actorCount; inner++) {
			//Applys Objects into the Actor
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			//Grabs the ID for the Actors
			int shapeID1 = object1->getShapeID();
			int shapeID2 = object2->getShapeID();

			//Grabs the Shape ID's for the Objects 
			int functionIDx = (shapeID1 * SHAPE_COUNT) + shapeID2;
			//Using the ID's, it passes into its specific function pointer
			fn collisionfunctPtr = CollisionFunctionArray[functionIDx];
			if (collisionfunctPtr != nullptr) {
				//Checks if a collsion occured
				collisionfunctPtr(object1, object2);
			}
		}
	}
}

bool PhysicsScene::planetoplane(PhysicsObject *, PhysicsObject *)
{
	//_Planes are static Object and cannot move therefore false
	return false;
}

bool PhysicsScene::planetocircle(PhysicsObject* obj1, PhysicsObject* obj2)
{
	//_Planes are static Object and cannot move therefore false
	return circletoplane(obj2, obj1);
}

bool PhysicsScene::planetosquare(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return squaretoplane(obj2, obj1);
}

bool PhysicsScene::circletoplane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Circle* Sphere = dynamic_cast<Circle*>(obj1);
	Plane* Line = dynamic_cast<Plane*>(obj2);

	//if Sphere and Line are not equal to Nullptr
	if (Sphere != nullptr && Line != nullptr) {
		//collison direction
		glm::vec2 collisionNormal = Line->getNormal();
		float sphereTo_Plane = glm::dot(Sphere->getPosition(), Line->getNormal()) - Line->getDistance();

		//If Behind the _Plane 
		if (sphereTo_Plane < 0) {
			collisionNormal *= -1;
			sphereTo_Plane *= -1;
		}

		float intersection = Sphere->getRadius() - sphereTo_Plane;
		if (intersection > 0) {
			Sphere->setPosition(Sphere->getPosition() + intersection * collisionNormal);
			Line->resolveCollision(Sphere);
			return true;
		}
	}

	return false;
}

bool PhysicsScene::circletocircle(PhysicsObject* obj1, PhysicsObject* obj2)
{
	//Cast the Object to sphere and sphere
	Circle *Sphere1 = dynamic_cast<Circle*>(obj1);
	Circle *Sphere2 = dynamic_cast<Circle*>(obj2);

	//If Successful test for Collision
	if (Sphere1 != nullptr && Sphere2 != nullptr) {

		glm::vec2 distance = Sphere1->getPosition() - Sphere2->getPosition();
		float radius = Sphere1->getRadius() + Sphere2->getRadius();
		glm::vec2 collisionNormal = glm::normalize(distance);

		if (glm::length(distance) < radius) {
			float intersection = glm::length(distance) - radius;

			//Static Rigid Body
			if (!Sphere1->isKinematic() && !Sphere2->isKinematic()) {
				Sphere1->setPosition(Sphere1->getPosition() + -intersection * collisionNormal);
				Sphere2->setPosition(Sphere2->getPosition() - intersection * collisionNormal);
			}
			if (!Sphere1->isKinematic()) {
				Sphere1->setPosition(Sphere1->getPosition() + -intersection);
			}
			else {
				Sphere2->setPosition(Sphere2->getPosition() - intersection);
			}
			Sphere1->resolveCollision(Sphere2);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::circletosquare(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return squaretocircle(obj2, obj1);
}

bool PhysicsScene::squaretocircle(PhysicsObject* obj1, PhysicsObject* obj2)
{
	static vector<float> intersect;

	AABB *Box1 = dynamic_cast<AABB*>(obj1);
	Circle *Sphere1 = dynamic_cast<Circle*>(obj2);

	if (Box1 != nullptr && Sphere1 != nullptr) {

		glm::vec2 contact = glm::clamp(Sphere1->getPosition(), Box1->getMin(), Box1->getMax());
		glm::vec2 point = contact - Sphere1->getPosition();

		if (glm::dot(point, point) <= Sphere1->getRadius() * Sphere1->getRadius()) {

			glm::vec2 vClamp = glm::normalize(point) * Sphere1->getRadius();  
			float intersection = glm::distance(contact, vClamp + Sphere1->getPosition());

			//Static Rigid Body
			if (!Box1->isKinematic() && !Sphere1->isKinematic()) {
				Box1->setPosition(Box1->getPosition() + intersection * point);
				Sphere1->setPosition(Sphere1->getPosition() - intersection * point);
			}
			if (!Box1->isKinematic()) {
				Box1->setPosition(Box1->getPosition() + intersection * point);
			}
			else {
				Sphere1->setPosition(Sphere1->getPosition() - intersection * point);
			}

			Box1->resolveCollision(Sphere1);
			return true;
		}
	}

	return false;
}

bool PhysicsScene::squaretoplane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	AABB *Box = dynamic_cast<AABB*>(obj1);
	Plane *Line = dynamic_cast<Plane*>(obj2);

	//Success
	if (Box != nullptr && Line != nullptr) {
		glm::vec2 collisionNormal = Line->getNormal();
	
		glm::vec2 corners[4];
		corners[0] = Box->getMin();
		corners[1] = { Box->getMin().x, Box->getMax().y };
		corners[2] = Box->getMax();
		corners[3] = { Box->getMax().x, Box->getMin().y };

		float intersection = glm::dot(corners[0], collisionNormal) - Line->getDistance();

		for (int i = 1; i < 4; i++) {
			float temp = glm::dot(corners[i], collisionNormal) - Line->getDistance();
			if (temp < intersection) {
				intersection = temp;
			}
		}

		if (intersection <= 0) {
			Box->setPosition(Box->getPosition() - intersection * collisionNormal);
			Line->resolveCollision(Box);
			return true;
		}
	}
	return false;
}

bool PhysicsScene::squaretosquare(PhysicsObject* obj1, PhysicsObject* obj2)
{
	AABB *Box = dynamic_cast<AABB*>(obj1);
	AABB *Box2 = dynamic_cast<AABB*>(obj2);

	if (Box != nullptr && Box2 != nullptr) {
		if (!(Box->getMax().x < Box2->getMin().x ||
			Box->getMax().y < Box2->getMin().y ||
			Box->getMin().y > Box2->getMax().y ||
			Box->getMin().x > Box2->getMax().x))
		{
			glm::vec2 clamp = glm::clamp(Box->getPosition(), Box2->getMin(), Box2->getMax());
			glm::vec2 normal = glm::normalize(clamp - Box->getPosition());

			float minBox1 = std::numeric_limits<float>::max();
			float maxBox1 = std::numeric_limits<float>::lowest();
			float minBox2 = std::numeric_limits<float>::max();
			float maxBox2 = std::numeric_limits<float>::lowest();
			std::vector<glm::vec2> Box1corner = Box->corners();
			std::vector<glm::vec2> Box2corner = Box2->corners();
			for (auto corner : Box1corner) {
				float overlap;
				overlap = glm::dot(normal, corner);
				if (overlap < minBox1) {
					minBox1 = overlap;
				}
				if (overlap > maxBox1) {
					maxBox1 = overlap;
				}
			}
			for (auto corner : Box2corner) {
				float overlap;
				overlap = glm::dot(normal, corner);
				if (overlap < minBox2) {
					minBox2 = overlap;
				}
				if (overlap > maxBox2) {
					maxBox2 = overlap;
				}
			}
			float intersection = 0.0f;

			if (maxBox1 - minBox2 > maxBox2 - minBox1) {
				intersection = maxBox2 - minBox1;

			}
			else {
				intersection = maxBox1 - minBox2;
			}

			//Static Rigid Body
			if (!Box->isKinematic() && !Box2->isKinematic()) {
				Box->setPosition(Box->getPosition() + intersection * -normal);
				Box2->setPosition(Box2->getPosition() - intersection * normal);
			}
		    if (!Box->isKinematic()) {
				Box->setPosition(Box->getPosition() + intersection);
			}
			else {
				Box2->setPosition(Box2->getPosition() - intersection);
			}
			Box->resolveCollision(Box2);
			return true;
		}

	}

	return false;
}


void PhysicsScene::updateGizmos()
{
	//For all actors
	for (auto pActor : m_actors) {
		//Create a gizmo
		pActor->makeGizmo();
	}
}

void PhysicsScene::debugScene()
{
	int count = 0;
	for (auto pActor : m_actors) {
		cout << count << endl;
		pActor->debug();
		count++;
	}
}

void PhysicsScene::setGravity(const glm::vec2& gravity)
{
	this->m_gravity = gravity;
}

glm::vec2 PhysicsScene::getGravity() const
{
	return m_gravity;
}

void PhysicsScene::setTimeStep(const float& timeStep)
{
	this->m_timeStep = timeStep;
}

float PhysicsScene::getTimeStep() const
{
	return m_timeStep;
}
