
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <vector>

struct Player {
    std::string name;
    sf::Vector2f pos;
    float scale;
    int health;
    int distance;
};

class FreeFireESP {
    sf::RenderWindow window;
    sf::Font font;

    bool boxes = true;
    bool skeleton = true;
    bool health = true;
    bool names = true;

    sf::Color red{255, 25, 50};

    std::vector<Player> players{
        {"PLAYER_01", {300, 260}, 1.0f, 100, 15},
        {"PLAYER_02", {580, 300}, 0.8f, 70, 28},
        {"PLAYER_03", {850, 260}, 1.1f, 45, 35}
    };

    void line(sf::Vector2f a, sf::Vector2f b) {
        auto d = b - a;
        float length = std::sqrt(d.x*d.x + d.y*d.y);

        sf::RectangleShape l({length, 2.f});
        l.setPosition(a);
        l.setRotation(std::atan2(d.y,d.x)*180.f/3.14159265f);
        l.setFillColor(red);
        window.draw(l);
    }

    void text(std::string value, float x, float y,
              unsigned size, sf::Color color) {
        if (font.getInfo().family.empty()) return;

        sf::Text t(value, font, size);
        t.setPosition(x,y);
        t.setFillColor(color);
        window.draw(t);
    }

    void drawSkeleton(const Player& p) {
        float x = p.pos.x;
        float y = p.pos.y;
        float s = p.scale;

        sf::Vector2f head(x,y);
        sf::Vector2f neck(x,y+30*s);
        sf::Vector2f chest(x,y+65*s);
        sf::Vector2f waist(x,y+115*s);

        sf::Vector2f ls(x-25*s,y+43*s);
        sf::Vector2f rs(x+25*s,y+43*s);

        sf::Vector2f le(x-42*s,y+85*s);
        sf::Vector2f re(x+42*s,y+85*s);

        sf::Vector2f lh(x-48*s,y+120*s);
        sf::Vector2f rh(x+48*s,y+120*s);

        sf::Vector2f lk(x-18*s,y+175*s);
        sf::Vector2f rk(x+18*s,y+175*s);

        sf::Vector2f lf(x-25*s,y+225*s);
        sf::Vector2f rf(x+25*s,y+225*s);

        sf::CircleShape circle(10*s);
        circle.setOrigin(10*s,10*s);
        circle.setPosition(head);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(red);
        circle.setOutlineThickness(2);
        window.draw(circle);

        line(neck,chest);
        line(chest,waist);

        line(neck,ls);
        line(neck,rs);
        line(ls,le);
        line(le,lh);
        line(rs,re);
        line(re,rh);

        line(waist,lk);
        line(lk,lf);
        line(waist,rk);
        line(rk,rf);
    }

    void drawPlayer(const Player& p) {
        float s = p.scale;
        float x = p.pos.x;
        float y = p.pos.y;

        if(boxes) {
            sf::RectangleShape b({115*s,245*s});
            b.setPosition(x-57*s,y-15*s);
            b.setFillColor(sf::Color::Transparent);
            b.setOutlineColor(red);
            b.setOutlineThickness(2);
            window.draw(b);
        }

        if(skeleton) drawSkeleton(p);

        if(health) {
            sf::RectangleShape bg({5,190*s});
            bg.setPosition(x-67*s,y+5*s);
            bg.setFillColor(sf::Color(60,60,60));
            window.draw(bg);

            sf::RectangleShape hp({
                5,190*s*p.health/100.f
            });

            hp.setPosition(
                x-67*s,
                y+5*s+190*s*(1-p.health/100.f)
            );

            hp.setFillColor(sf::Color::Green);
            window.draw(hp);
        }

        if(names) {
            text(p.name,x-45*s,y-35*s,13,sf::Color::White);
            text(std::to_string(p.distance)+" M",
                 x-15*s,y+245*s,12,red);
        }
    }

public:
    FreeFireESP()
        : window(sf::VideoMode(1100,700),
                 "CART3R - FREE FIRE ESP DEMO") {

        window.setFramerateLimit(60);
        font.loadFromFile("assets/font.ttf");
    }

    void run() {
        while(window.isOpen()) {
            sf::Event event;

            while(window.pollEvent(event)) {
                if(event.type==sf::Event::Closed)
                    window.close();

                if(event.type==sf::Event::KeyPressed) {
                    switch(event.key.code) {
                        case sf::Keyboard::Escape:
                            window.close();
                            break;
                        case sf::Keyboard::F1:
                            boxes=!boxes;
                            break;
                        case sf::Keyboard::F2:
                            skeleton=!skeleton;
                            break;
                        case sf::Keyboard::F3:
                            health=!health;
                            break;
                        case sf::Keyboard::F4:
                            names=!names;
                            break;
                        default:
                            break;
                    }
                }
            }

            window.clear(sf::Color(10,10,14));

            for(const auto& p:players)
                drawPlayer(p);

            text("CART3R.JAILBREAK",20,15,23,red);
            text("FREE FIRE OFFLINE SIMULATOR",20,48,13,
                 sf::Color::White);

            text("F1 - BOXES",20,100,13,sf::Color::White);
            text("F2 - SKELETON",20,125,13,sf::Color::White);
            text("F3 - HEALTH",20,150,13,sf::Color::White);
            text("F4 - NAMES",20,175,13,sf::Color::White);
            text("ESC - EXIT",20,200,13,sf::Color::White);

            window.display();
        }
    }
};

int main() {
    FreeFireESP app;
    app.run();
    return 0;
}
