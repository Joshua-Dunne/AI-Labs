#ifndef WANDER_H
#define WANDER_H
#include "NPC.h"
class WanderAI :
    public NPC
{
public:
    WanderAI(sf::Vector2f t_pos);

    // Inherited via NPC
    virtual void update(sf::Time& dt) override;

    float m_maxSpeed = 0.5f;
    float m_maxAcceleration = 20.0f;

private:
    SteeringOutput getSteering();
    SteeringOutput getArrival(sf::Vector2f t_pos);

    float m_wanderOffset = 4.0f;
    float m_wanderRate = 5.0f;
    float m_wanderRadius = 20.0f;
    float m_wanderOrientation = 0.0f;

    float m_arrivalRadius = 10.0f;
    float m_slowRadius = 200.0f;
    float m_timeToTarget = 0.0f;
};

#endif