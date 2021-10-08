#ifndef BASIC_AI_H
#define BASIC_AI_H
#include "NPC.h"
class BasicAI :
    public NPC
{
public:
    BasicAI(sf::Vector2f t_pos);
    // Inherited via NPC
    virtual void update(sf::Time& dt) override;
};

#endif