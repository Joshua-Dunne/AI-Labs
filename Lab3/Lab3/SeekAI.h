#ifndef SEEK_H
#define SEEK_H
#include "NPC.h"
class SeekAI :
    public NPC
{
public:
    SeekAI(sf::Vector2f t_pos);

    // Inherited via NPC
    virtual void update(sf::Time& dt) override;
    
    sf::Vector2f m_target;

private:
    SteeringOutput getSteering();

    float maxAcceleration = 2.0f;

};

#endif