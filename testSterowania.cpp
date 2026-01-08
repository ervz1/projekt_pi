#include <optional>
#include <utility>
#include <SFML/Graphics.hpp>
#include "GameLoop.hpp"
#include "sterowanie.hpp"




int main()
{
    sf::Clock clock;  

    while (true)
    {
        float dt = clock.restart().asSeconds();  
        sterowanieRzutem(dt);
        if (auto ruch = sterowaniePiciem(dt))
        if (auto ruch = sterowaniePodnoszenia(dt))
        if (auto ruch = sterowanieRuchem(dt))
        sf::sleep(sf::milliseconds(20));
        // std::cout << "dt = " << dt << '\n';
    }

}
