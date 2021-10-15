#ifndef ARRIVE_H
#define ARRIVE_H
#include "NPC.h"

class ArriveAI :
    public NPC
{
public:
    ArriveAI(sf::Vector2f t_pos);
    // Inherited via NPC
    virtual void update(sf::Time& dt) override;

    sf::Vector2f m_target;
    float m_maxSpeed = 0.5f;
    float m_maxAcceleration = 20.0f;

private:

    SteeringOutput getSteering();

    float m_arrivalRadius = 10.0f;
    float m_slowRadius = 300.0f;
    float m_timeToTarget = 0.0f;

};

#endif