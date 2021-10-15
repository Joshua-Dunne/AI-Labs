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

private:
    SteeringOutput getSteering();

    float m_wanderOffset = 4.0f; //  --how far in front we aim
    float m_wanderRadius = 10.0f; // --radius of target circle
    float m_wanderRate = 2.0f; // --how fast we can turn
    float m_maxAcc = 5.0f; // --maximum acceleration
    float m_wanderOrientation; // --orientation of target
    float m_orientation;

    SteeringOutput m_steering;

    sf::Vector2f m_target;
};

#endif