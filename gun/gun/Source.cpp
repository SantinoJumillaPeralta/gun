#include <player.cpp>
#include <enemigo.cpp>
#include <civil.cpp>
#include <SFML/Graphics.hpp>
#include <iostream>

enum class Estado {
    MENU,
    JUGANDO,
    GAME_OVER
};

class Juego {
    sf::RenderWindow window;
    sf::SoundBuffer disparoBuffer;
    sf::Sound disparoSound;
    sf::Music fondoMusica;
    sf::Font font;
    sf::Text menuJugar;
    sf::Text menuAbandonar;
    sf::Texture fondoTexture;
    sf::Sprite fondoSprite;
    Estado estado;

public:
    Juego() : estado(Estado::MENU), window(sf::VideoMode(800, 600), "Shooter Game") {
        if (!disparoBuffer.loadFromFile("Nueva carpeta (9)\Sonido\disparo.ogg")) {
            std::cout << "Error al cargar el archivo de sonido de disparo" << std::endl;
        }
        disparoSound.setBuffer(disparoBuffer);

        if (!fondoMusica.openFromFile("Nueva carpeta (9)\Sonido\fondo.ogg")) {
            std::cout << "Error al cargar el archivo de música de fondo" << std::endl;
        }
        fondoMusica.setLoop(true);

        if (!font.loadFromFile("Nueva carpeta (9)\Textura\payday.zip\Payday.ttf")) {
            std::cout << "Error al cargar la fuente Payday" << std::endl;
        }

        menuJugar.setFont(font);
        menuJugar.setString("Jugar");
        menuJugar.setCharacterSize(30);
        menuJugar.setPosition(300, 300);

        menuAbandonar.setFont(font);
        menuAbandonar.setString("Abandonar");
        menuAbandonar.setCharacterSize(30);
        menuAbandonar.setPosition(300, 350);

        if (!fondoTexture.loadFromFile("Nueva carpeta (9)\Texturafondo.jpg")) {
            std::cout << "Error al cargar la imagen de fondo" << std::endl;
        }
        fondoSprite.setTexture(fondoTexture);
    }

    void ejecutar() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (estado == Estado::MENU) {
                        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                        if (menuJugar.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                            estado = Estado::JUGANDO;
                            fondoMusica.play();
                        }
                        else if (menuAbandonar.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y))) {
                            std::cout << "Has abandonado el juego." << std::endl;
                            window.close();
                            return;
                        }
                    }
                    else if (estado == Estado::JUGANDO) {
                        disparoSound.play();
                    }
                }
            }

            window.clear();

            if (estado == Estado::MENU) {
                window.draw(menuJugar);
                window.draw(menuAbandonar);
            }
            else if (estado == Estado::JUGANDO) {
                window.draw(fondoSprite);
                // Resto de la lógica de juego
            }
            else if (estado == Estado::GAME_OVER) {
                // Lógica para el estado de game over
            }

            window.display();
        }
    }
};

int main() {
    Juego juego;
    juego.ejecutar();
    return 0;
}