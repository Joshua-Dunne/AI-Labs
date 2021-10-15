#ifndef PERSUE_H
#define PERSUE_H
#include "NPC.h"

class PersueAI :
    public NPC
{
public:
    PersueAI(sf::Vector2f t_pos);
    // Inherited via NPC
    virtual void update(sf::Time& dt) override;
    sf::Vector2f m_target;
    sf::Vector2f m_targetVelocity;
    float m_maxSpeed = 0.5f;
    float m_maxAcceleration = 20.0f;

private:

    SteeringOutput getSteering();
    SteeringOutput getArrival(sf::Vector2f t_pos);

    float m_arrivalRadius = 10.0f;
    float m_slowRadius = 200.0f;
    float m_timeToTarget = 0.0f;
};

#endif