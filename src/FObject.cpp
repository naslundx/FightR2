#include "FObject.hpp"

int FObject::IDcounter = 0;

FObject::FObject()
{
	m_gravity = false;
	m_visible = false;
	m_solid = false;
	m_id = FObject::createID();
	freeze();
}

FObject::FObject(bool gravity, bool visible, bool solid)
{
	m_gravity = gravity;
	m_visible = visible;
	m_solid = solid;
	m_id = FObject::createID();
	freeze();
}

FObject::FObject(FVector position, FVector size, bool gravity, bool visible, bool solid)
{
	m_position = position;
	m_size = size;
	m_gravity = gravity;
	m_visible = visible;
	m_solid = solid;
	m_id = FObject::createID();
	freeze();
}

FObject::~FObject()
{
}

FVector& FObject::getPosition()
{
	return m_position;
}

FVector& FObject::getSize()
{
	return m_size;
}

FVector& FObject::getVelocity()
{
	return m_velocity;
}

bool FObject::isGravitational()
{
	return m_gravity;
}

bool FObject::isVisible()
{
	return m_visible;
}

bool FObject::isSolid()
{
	return m_solid;
}

bool FObject::isStill()
{
	return m_velocity.getLength() < 0.0001;
}

int FObject::getID()
{
	return m_id;
}

void FObject::setPosition(const FVector position)
{
	m_position = position;
}

void FObject::setSize(const FVector size)
{
	m_size = size;
}

void FObject::setVelocity(const FVector velocity)
{
	m_velocity = velocity;
}

void FObject::accelerate(const FVector& acceleration)
{
	m_velocity += acceleration;
}

void FObject::setGravitational(bool value)
{
	m_gravity = value;
}

void FObject::setVisible(bool value)
{
	m_visible = value;
}

void FObject::freeze()
{
	m_velocity = FVector();
}

void FObject::tick(float delta)
{
	if (isGravitational())
	{
		FVector down(0.f, -0.5f * delta);
		accelerate(down);
	}
	
	m_position += m_velocity;
}

int FObject::createID()
{
	return FObject::IDcounter++;
}
