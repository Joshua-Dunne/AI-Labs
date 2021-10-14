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
    float m_orientation = m_rotation;
    float m_targetDistance = 3.0f;
    float m_maxRotation = 3.0f;
};

#endif