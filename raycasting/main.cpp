#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>

struct eqResult FindABC(long double x1,long double x2,long double y1,long double y2);
struct dotResult FindDot(long double A,long double B,long double C,long double D,long double E,long double F);
struct eqResult{
    long double A;
    long double B;
    long double C;
};
struct dotResult{
    long double X;
    long double Y;
};

int main() {

    sf::RenderWindow window(sf::VideoMode(1920,1080),"Raycasting");
    window.setFramerateLimit(30);
    std:: vector<sf::VertexArray> lines_top;
    std:: vector<sf::VertexArray> lines_bot;
    std:: vector<sf::VertexArray> lines_right;
    std:: vector<sf::VertexArray> lines_left;
    sf::Event ev;
    while(window.isOpen()){
        lines_top.clear();
        lines_bot.clear();
        lines_left.clear();
        lines_right.clear();
        int counter = 500;
        for(int i = 0;i <= 1920;i+=100) {
            sf::VertexArray line(sf::LineStrip, 2);
            line[0].color = sf::Color::Blue;
            line[1].color = sf::Color::Blue;
            line[0].position = sf::Vector2f(double(sf::Mouse::getPosition(window).x), double(sf::Mouse::getPosition(window).y));
            line[1].position = sf::Vector2f(i, 0);
            lines_top.push_back(line);
        }
        for(int i = 0;i <= 1920;i+=100){
            sf::VertexArray line(sf::LineStrip,2);
            line[0].color = sf::Color::Blue;
            line[1].color = sf::Color::Blue;
            line[0].position = sf::Vector2f(double(sf::Mouse::getPosition(window).x), double(sf::Mouse::getPosition(window).y));
            line[1].position = sf::Vector2f(i, 1080);
            lines_bot.push_back(line);
        }
        for(int i = 0;i <= 1080;i+=100){
            sf::VertexArray line(sf::LineStrip,2);
            line[0].color = sf::Color::Blue;
            line[1].color = sf::Color::Blue;
            line[0].position = sf::Vector2f(double(sf::Mouse::getPosition(window).x), double(sf::Mouse::getPosition(window).y));
            line[1].position = sf::Vector2f(0, i);
            lines_right.push_back(line);
        }
        for(int i = 0;i <= 1080;i+=100){
            sf::VertexArray line(sf::LineStrip,2);
            line[0].color = sf::Color::Blue;
            line[1].color = sf::Color::Blue;
            line[0].position = sf::Vector2f(double(sf::Mouse::getPosition(window).x), double(sf::Mouse::getPosition(window).y));
            line[1].position = sf::Vector2f(1920, i);
            lines_left.push_back(line);
        }

        sf::VertexArray wall(sf::LineStrip,2);
        wall[0].color = sf::Color::Green;
        wall[1].color = sf::Color::Green;
        wall[0].position = sf::Vector2f(500,500);
        wall[1].position = sf:: Vector2f (1000,1000);
        // LINES TOP///////////////////////////////////////////////////////////////////////////////
        for(int i = 0;i < lines_top.size();i++) {
            struct eqResult line_res = FindABC(lines_top[i][0].position.x, lines_top[i][1].position.x, lines_top[i][0].position.y,
                                               lines_top[i][1].position.y);
            struct eqResult obj_res = FindABC(wall[0].position.x, wall[1].position.x, wall[0].position.y,
                                              wall[1].position.y);
            struct dotResult point = FindDot(line_res.A, line_res.B, line_res.C, obj_res.A, obj_res.B, obj_res.C);
            if (point.X >= wall[0].position.x && point.X <= wall[1].position.x && point.Y >= wall[0].position.y &&
                point.Y <= wall[1].position.y && lines_top[i][0].position.y >= point.Y) {
                if (round(line_res.A * point.X + line_res.B * point.Y + line_res.C) ==0 &&
                    round(obj_res.A * point.X + obj_res.B * point.Y + obj_res.C) == 0) {
                    std::cout << line_res.A * point.X + line_res.B * point.Y + line_res.C << "       "
                              << obj_res.A * point.X + obj_res.B * point.Y + obj_res.C << std::endl;
                    lines_top[i][1].position.x = point.X;
                    lines_top[i][1].position.y = point.Y;
                }
                else{
                    std :: cout << "Error::" << line_res.A * point.X + line_res.B * point.Y + line_res.C << "       "
                                << obj_res.A * point.X + obj_res.B * point.Y + obj_res.C << std::endl;
                }
            }
        }
        // LINES BOTTOM////////////////////////////////////////////////////////////////////////////
        for(int i = 0;i < lines_bot.size();i++) {
            struct eqResult line_res = FindABC(lines_bot[i][0].position.x, lines_bot[i][1].position.x, lines_bot[i][0].position.y,
                                               lines_bot[i][1].position.y);
            struct eqResult obj_res = FindABC(wall[0].position.x, wall[1].position.x, wall[0].position.y,
                                              wall[1].position.y);
            struct dotResult point = FindDot(line_res.A, line_res.B, line_res.C, obj_res.A, obj_res.B, obj_res.C);
            if (point.X >= wall[0].position.x && point.X <= wall[1].position.x && point.Y >= wall[0].position.y &&
                point.Y <= wall[1].position.y && lines_bot[i][0].position.y <= point.Y) {
                if (round(line_res.A * point.X + line_res.B * point.Y + line_res.C) ==0 &&
                    round(obj_res.A * point.X + obj_res.B * point.Y + obj_res.C) == 0) {
                    std::cout << line_res.A * point.X + line_res.B * point.Y + line_res.C << "       "
                              << obj_res.A * point.X + obj_res.B * point.Y + obj_res.C << std::endl;
                    lines_bot[i][1].position.x = point.X;
                    lines_bot[i][1].position.y = point.Y;
                }
                else{
                    std :: cout << "Error::" << line_res.A * point.X + line_res.B * point.Y + line_res.C << "       "
                                << obj_res.A * point.X + obj_res.B * point.Y + obj_res.C << std::endl;
                }
            }
        }
        // LINES RIGHT//////////////////////////////////////////////////////////////////////////////
        for(int i = 0;i < lines_right.size();i++) {
            struct eqResult line_res = FindABC(lines_right[i][0].position.x, lines_right[i][1].position.x, lines_right[i][0].position.y,
                                               lines_right[i][1].position.y);
            struct eqResult obj_res = FindABC(wall[0].position.x, wall[1].position.x, wall[0].position.y,
                                              wall[1].position.y);
            struct dotResult point = FindDot(line_res.A, line_res.B, line_res.C, obj_res.A, obj_res.B, obj_res.C);
            if (point.X >= wall[0].position.x && point.X <= wall[1].position.x && point.Y >= wall[0].position.y &&
                point.Y <= wall[1].position.y && lines_right[i][0].position.x >= point.X) {
                if (round(line_res.A * point.X + line_res.B * point.Y + line_res.C) ==0 &&
                    round(obj_res.A * point.X + obj_res.B * point.Y + obj_res.C) == 0) {
                    std::cout << line_res.A * point.X + line_res.B * point.Y + line_res.C << "       "
                              << obj_res.A * point.X + obj_res.B * point.Y + obj_res.C << std::endl;
                    lines_right[i][1].position.x = point.X;
                    lines_right[i][1].position.y = point.Y;
                }
                else{
                    std :: cout << "Error::" << line_res.A * point.X + line_res.B * point.Y + line_res.C << "       "
                                << obj_res.A * point.X + obj_res.B * point.Y + obj_res.C << std::endl;
                }
            }
        }
        // LINES LEFT//////////////////////////////////////////////////////////////////////////////
        for(int i = 0;i < lines_left.size();i++) {
            struct eqResult line_res = FindABC(lines_left[i][0].position.x, lines_left[i][1].position.x, lines_left[i][0].position.y,
                                               lines_left[i][1].position.y);
            struct eqResult obj_res = FindABC(wall[0].position.x, wall[1].position.x, wall[0].position.y,
                                              wall[1].position.y);
            struct dotResult point = FindDot(line_res.A, line_res.B, line_res.C, obj_res.A, obj_res.B, obj_res.C);
            if (point.X >= wall[0].position.x && point.X <= wall[1].position.x && point.Y >= wall[0].position.y &&
                point.Y <= wall[1].position.y && lines_left[i][0].position.x <= point.X) {
                if (round(line_res.A * point.X + line_res.B * point.Y + line_res.C) ==0 &&
                    round(obj_res.A * point.X + obj_res.B * point.Y + obj_res.C) == 0) {
                    std::cout << line_res.A * point.X + line_res.B * point.Y + line_res.C << "       "
                              << obj_res.A * point.X + obj_res.B * point.Y + obj_res.C << std::endl;
                    lines_left[i][1].position.x = point.X;
                    lines_left[i][1].position.y = point.Y;
                }
                else{
                    std :: cout << "Error::" << line_res.A * point.X + line_res.B * point.Y + line_res.C << "       "
                                << obj_res.A * point.X + obj_res.B * point.Y + obj_res.C << std::endl;
                }
            }
        }
        while(window.pollEvent(ev)){
            if(ev.type == sf::Event::Closed ) {
                std :: cout << "Window closed" << std :: endl;
                window.close();
            }
            if(ev.type == sf::Event::KeyPressed){
                if(ev.key.code == sf::Keyboard::Escape){
                    std::cout << "Window closed" << std :: endl;
                    window.close();
                }
            }
        }
        window.draw(wall);
        for(int i = 0; i < lines_top.size();i++){
            window.draw(lines_top.at(i));
        }
        for(int i =0; i < lines_bot.size();i++){
            window.draw(lines_bot.at(i));
        }
        for(int i =0; i < lines_right.size();i++){
            window.draw(lines_right.at(i));
        }
        for(int i =0; i < lines_left.size();i++){
            window.draw(lines_left.at(i));
        }
        window.display();
        window.clear();
    }
    return 0;
}

struct eqResult FindABC(long double x1,long double x2,long double y1,long double y2){
    long double A = -(y2-y1);
    long double B = x2-x1;
    long double C = x1*(y2-y1) - y1*(x2-x1);
    std :: cout << A  << ' '<< B << ' '<< C << std :: endl;
    struct eqResult res;
    res.A = A;
    res.B = B;
    res.C = C;
    return res;
}

struct dotResult FindDot(long double A,long double B,long double E,long double C,long double D,long double F){
    long double det=A*D-B*C;
    struct dotResult dot;
    long double x = (-E*D + B*F)/det;
    long double y=(-A*F+E*C)/det;
    dot.X = x;
    dot.Y = y;
    return dot;

}
