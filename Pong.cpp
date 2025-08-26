#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
    VideoMode vm(1920, 1080);

    RenderWindow window(vm, "Pong", Style::Fullscreen);

    int score = 0;
    int lives = 2;

    Bat bat(1920 / 2, 1080 - 20);

    Ball ball(1920 / 2, 0);

    Text hud;

    Font font;
    font.loadFromFile("font/KOMIKAP_.ttf");

    hud.setFont(font);

    hud.setCharacterSize(75);

    hud.setFillColor(Color::White);
    hud.setPosition(20, 20);

    Clock clock;

    while (window.isOpen())
    {

        // to show score
        if (lives <= 0)
        {
            // Clear the window and show the final score
            window.clear();
            hud.setString("Game Over! Final Score: " + std::to_string(score) + "\nResart (press R)   Exit (press E)");
            window.draw(hud);
            window.display();

            // Wait for a short duration before exiting
            // sf::sleep(sf::seconds(3));
            // window.close();

            if (Keyboard::isKeyPressed(Keyboard::R))
            {
                score = 0;
                lives = 2;
                bat = Bat(1920 / 2, 1080 - 20);
                ball = Ball(1920 / 2, 0);

                // Continue game loop
                continue;
            }

            if (Keyboard::isKeyPressed(Keyboard::E))
            {
                window.close();
                break;
            }
            sf::sleep(sf::milliseconds(100));
            continue;
        }

        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left))
            bat.moveLeft();
        else
            bat.stopLeft();

        if (Keyboard::isKeyPressed(Keyboard::Right))
            bat.moveRight();
        else
            bat.stopRight();

        Time dt = clock.restart();

        bat.update(dt);
        ball.update(dt);

        std::stringstream ss;
        ss << "Score: " << score << " Lives: " << lives;

        hud.setString(ss.str());
        // collision of ball and bottom
        if (ball.getPosition().top > window.getSize().y)
        {
            ball.reboundBottom();
            lives--;
            if (lives < 1)
            {
                score = 0;
                // lives=3;//used for showing score if not needed uncomment it
            }
        }
        if (ball.getPosition().top < 0)
        {
            ball.reboundBatOrTop();
            score++;
        }

        if (ball.getPosition().left < 0 || ball.getPosition().left + 25 > window.getSize().x)
            ball.reboundSides();

        // ball and bat intersection
        if (ball.getPosition().intersects(bat.getPosition()))
            ball.reboundBatOrTop();

        window.clear();

        window.draw(hud);

        window.draw(bat.getShape());
        window.draw(ball.getShape());
        window.display();
    }
    return 0;
}