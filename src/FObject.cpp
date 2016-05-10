#include "FObject.hpp"

int FObject::IDcounter = 0;

FObject::FObject()
{
	m_gravity = false;
	m_visible = false;
	m_solid = false;
	m_drags = false;
	m_id = FObject::createID();
	freeze();
}

FObject::FObject(bool gravity, bool visible, bool solid, bool drags)
{
	m_gravity = gravity;
	m_visible = visible;
	m_solid = solid;
	m_drags = drags;
	m_id = FObject::createID();
	freeze();
}

FObject::FObject(FVector position, FVector size, bool gravity, bool visible, bool solid, bool drags)
{
	m_position = position;
	m_size = size;
	m_gravity = gravity;
	m_visible = visible;
	m_solid = solid;
	m_drags = drags;
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

FVector FObject::getCenter()
{
	return m_position + m_size / 2.f;
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
	return m_velocity.getLength() < MINIMUM_STILL_VELOCITY;
}

bool FObject::hasDrag()
{
	return m_drags;
}

bool FObject::intersects(FObject& other)
{
	auto left1 = getPosition().x,
		 left2 = other.getPosition().x,
		 right1 = getPosition().x + getSize().x,
		 right2 = other.getPosition().x + other.getSize().x,
		 top1 = getPosition().y,
		 top2 = other.getPosition().y,
		 bottom1 = getPosition().y + getSize().y,
		 bottom2 = other.getPosition().y + other.getSize().y;
		 
	return
		(left1 > left2 && left1 < right2 && top1 > top2 && top1 < bottom2) ||
		(left1 > left2 && left1 < right2 && bottom1 > top2 && bottom1 < bottom2) ||
		(right1 > left2 && right1 < right2 && top1 > top2 && top1 < bottom2)  ||
		(right1 > left2 && right1 < right2 && bottom1 > top2 && bottom1 < bottom2) ||
		
		(left2 > left1 && left2 < right1 && top2 > top1 && top2 < bottom1) ||
		(left2 > left1 && left2 < right1 && bottom2 > top1 && bottom2 < bottom1) ||
		(right2 > left1 && right2 < right1 && top2 > top1 && top2 < bottom1)  ||
		(right2 > left1 && right2 < right1 && bottom2 > top1 && bottom2 < bottom1);
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

void FObject::setGravitational(const bool value)
{
	m_gravity = value;
}

void FObject::setVisible(const bool value)
{
	m_visible = value;
}

void FObject::setDrag(const bool value)
{
	m_drags = value;
}

void FObject::freeze()
{
	land();
	halt();
}

void FObject::land()
{
	m_velocity.y = 0.f;
}

void FObject::halt()
{
	m_velocity.x = 0.f;
}

void FObject::tick(const float delta)
{
	if (m_drags)
	{
		m_velocity = m_velocity * DRAG;
	}
	
	if (m_velocity.getLength() < MINIMUM_VELOCITY)
		m_velocity = FVector();
		
	if (isGravitational())
	{
		FVector down(0.f, GRAVITY * delta);
		accelerate(down);
	}
	
	m_position += m_velocity;
}

int FObject::createID()
{
	return FObject::IDcounter++;
}
