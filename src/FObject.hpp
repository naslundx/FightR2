#ifndef __FOBJECT_HPP__
#define __FOBJECT_HPP__

#include "FVector.hpp"
#include "FDirection.hpp"

class FObject
{
public:
	FObject();
	FObject(bool, bool, bool);
	FObject(FVector, FVector, bool, bool, bool);
	~FObject();
	
	FVector& getPosition();
	FVector& getSize();
	FVector& getVelocity();
	bool isGravitational();
	bool isVisible();
	bool isSolid();
	bool isStill();
	int getID();
	
	void setPosition(const FVector);
	void setSize(const FVector);
	void setVelocity(const FVector);
	void accelerate(const FVector&);
	void setGravitational(bool);
	void setVisible(bool);
	void freeze();
	virtual void tick();

protected:
	FVector m_position, m_size, m_velocity;
	int m_id;
	bool m_gravity, m_visible, m_solid;
	FDirection m_direction;
	
	static int IDcounter;
	static int createID();
};

#endif
