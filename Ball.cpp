#include "Ball.h"

Ball::Ball(float startX, float startY)
{
    m_Position.x = startX;
    m_Position.y = startY;

    m_Shape.setSize(sf::Vector2f(25, 25));
    m_Shape.setPosition(m_Position);
}
FloatRect Ball::getPosition()
{
    return m_Shape.getGlobalBounds();
}
RectangleShape Ball::getShape()
{
    return m_Shape;
}
float Ball::getXVelocity()
{
    return m_DirectionX;
}
void Ball::reboundSides()
{
    m_DirectionX = -m_DirectionX;
}
void Ball::reboundBatOrTop()
{
    m_DirectionY = -m_DirectionY;
}
// void Ball::reboundBottom(){
//     m_DirectionY=0;
//     m_DirectionX=500;
//     m_DirectionY=-m_DirectionY;
// }
void Ball::reboundBottom()
{
    // Reset position near the top center
    m_Position.x = 1920 / 2; // Center X
    m_Position.y = 100;      // Near the top

    // Reset downward motion for the next drop
    m_DirectionY = .2f;
    m_DirectionX = .2f;

    m_Shape.setPosition(m_Position);
}

void Ball::update(Time dt)
{

    m_Position.y += m_DirectionY * m_Speed * dt.asSeconds();
    m_Position.x += m_DirectionX * m_Speed * dt.asSeconds();

    m_Shape.setPosition(m_Position);
}
