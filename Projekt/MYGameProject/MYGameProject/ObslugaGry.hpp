#include <SFML/Graphics.hpp>
#include <fstream>
#include <thread>
#include "NazwyGraczy.hpp"
#include "Boostery.hpp"

NazwijGraczy nazwijgraczy;
TabelaWynikow tabela;

class ObslugaGry {
public:
    sf::RenderWindow Graj;
    Gracz1 player1;
    Gracz2 player2;
    Pilka ball{ 400,300 };

    float maxX = 800;
    float maxY = 600;
    SpeedUp Item_Up{maxX, maxY};
    SpeedDown Item_Down{maxX, maxY};

    sf::Texture BackgroundTla[3];
    bool wlaczSpeedUp, wlaczSpeedDown = true;
    int liczbaBramek = 5;
    int WybraneTlo = 0;

    void zapiszWynikiAsync(TabelaWynikow& tabela) {//uzycie thread by zapis wynikow dzialal niezaleznie
        std::thread saveThread([&tabela]() {
            tabela.zapiszTabeleWynikow("tabela_wynikow.txt");
            });
        saveThread.detach(); 
    }

    void graj() {
        tabela.wczytajTabeleWynikow("tabela_wynikow.txt");

        Graj.create(sf::VideoMode(800, 600), "Ping Pong Game");
        BackgroundTla[0].loadFromFile("Photos/game_photo.jpg");
        BackgroundTla[1].loadFromFile("Photos/game_photo2.jpg");
        BackgroundTla[2].loadFromFile("Photos/game_photo3.jpg");

        nazwijgraczy.wczytajNazwyGraczy();
        nazwijgraczy.wprowadzNazwyGraczy();
        nazwijgraczy.zapiszNazwyGraczy();

        sf::Sprite TloGry(BackgroundTla[WybraneTlo]);

        while (Graj.isOpen()) {
            sf::Event granie;
            while (Graj.pollEvent(granie)) {
                if (granie.type == sf::Event::Closed) {
                    Graj.close();
                }

                if (granie.type == sf::Event::KeyPressed) {
                    if (granie.key.code == sf::Keyboard::Escape) {
                        Graj.close();
                        RestartGry();
                    }
                    player1.Sterowanie(granie.key.code, true);
                    player2.Sterowanie(granie.key.code, true);
                }

                else if (granie.type == sf::Event::KeyReleased) {
                    player1.Sterowanie(granie.key.code, false);
                    player2.Sterowanie(granie.key.code, false);
                }
            }

            player1.Ruch(Graj.getSize().x, Graj.getSize().y);
            player2.Ruch(Graj.getSize().x, Graj.getSize().y);
            Graj.clear();
            Graj.draw(TloGry);

            ball.kolizja(player1, player2);
            Item_Up.SpeedKolizja(ball);
            Item_Down.SpeedKolizja(ball);

            player1.Wyswietl(Graj, nazwijgraczy.nazwaGracza1);
            player2.Wyswietl(Graj, nazwijgraczy.nazwaGracza2);
            ball.Wyswietl(Graj);

            Item_Up.Wyswietl(Graj);
            Item_Down.Wyswietl(Graj);
            Graj.display();

            if (player1.score1 >= liczbaBramek || player2.score2 >= liczbaBramek) {
                std::string zwyciezca = (player1.score1 >= liczbaBramek) ? nazwijgraczy.nazwaGracza1 : nazwijgraczy.nazwaGracza2;
                auto it = std::ranges::find_if(tabela.wyniki, [&zwyciezca](const auto& para) {
                    return para.first == zwyciezca;
                    });

                if (it != tabela.wyniki.end()) {
                    it->second++;
                }
                else {
                    tabela.wyniki.push_back({ zwyciezca, 1 });
                }

                zapiszWynikiAsync(tabela);

                sf::RenderWindow tabelaWindow(sf::VideoMode(400, 300), "Tabela Wyników");
                sf::Font czcionka;
                czcionka.loadFromFile(fontPath.string());
                tabela.wyswietlTabeleWynikow(tabelaWindow, czcionka);

                sf::Event event;
                while (tabelaWindow.isOpen()) {
                    while (tabelaWindow.pollEvent(event)) {
                        if (event.type == sf::Event::KeyPressed) {
                            if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Escape) {
                                tabelaWindow.close();
                                RestartGry();
                            }
                        }
                    }
                }
            }
        }
    }

    void opcje() {
        sf::RenderWindow Opcje(sf::VideoMode(800, 600), "Opcje");

        // tlo do opcji
        sf::RectangleShape TloOpcji;
        TloOpcji.setSize(sf::Vector2f(800, 600));
        sf::Texture OpcjeTexture;
        OpcjeTexture.loadFromFile("Photos/options.jpg");
        TloOpcji.setTexture(&OpcjeTexture);

        sf::Font czcionkaOpcji;
        czcionkaOpcji.loadFromFile(fontPath.string()); //zaladowanie odpowiedniej czcionki

        sf::Text backgroundOption;
        backgroundOption.setFont(czcionkaOpcji);
        backgroundOption.setCharacterSize(75);
        backgroundOption.setFillColor(sf::Color::White);
        backgroundOption.setString("Wybierz Arene:");
        backgroundOption.setPosition(124, 100);

        sf::Text infoText;
        infoText.setFont(czcionkaOpcji);
        infoText.setCharacterSize(50);
        infoText.setFillColor(sf::Color::White);
        infoText.setString("");
        infoText.setPosition(400, 400);

        // Przyciski do wyboru t³a
        sf::RectangleShape backgroundButton0(sf::Vector2f(200, 100));
        backgroundButton0.setPosition(sf::Vector2f(50, 200));
        sf::Texture texture0;
        texture0.loadFromFile("Photos/game_photo.jpg");
        backgroundButton0.setTexture(&texture0);

        sf::RectangleShape backgroundButton1(sf::Vector2f(200, 100));
        backgroundButton1.setPosition(sf::Vector2f(300, 200));
        sf::Texture texture1;
        texture1.loadFromFile("Photos/game_photo2.jpg");
        backgroundButton1.setTexture(&texture1);

        sf::RectangleShape backgroundButton2(sf::Vector2f(200, 100));
        backgroundButton2.setPosition(sf::Vector2f(550, 200));
        sf::Texture texture2;
        texture2.loadFromFile("Photos/game_photo3.jpg");
        backgroundButton2.setTexture(&texture2);

        // Przyciski do zmiany liczby bramek
        sf::Text bramkiOption;
        bramkiOption.setFont(czcionkaOpcji);
        bramkiOption.setCharacterSize(50);
        bramkiOption.setFillColor(sf::Color::White);
        bramkiOption.setString("Limit Goli: " + std::to_string(liczbaBramek));
        bramkiOption.setPosition(265, 400);

        sf::Text plusButton;
        plusButton.setFont(czcionkaOpcji);
        plusButton.setCharacterSize(50);
        plusButton.setFillColor(sf::Color::White);
        plusButton.setString("+");
        plusButton.setPosition(650, 400);

        sf::Text minusButton;
        minusButton.setFont(czcionkaOpcji);
        minusButton.setCharacterSize(50);
        minusButton.setFillColor(sf::Color::White);
        minusButton.setString("-");
        minusButton.setPosition(600, 400);

        sf::RectangleShape Button_Boost_Off(sf::Vector2f(100, 50));
        Button_Boost_Off.setPosition(sf::Vector2f(620, 485));
        sf::Texture Texture_Boost_Off;
        Texture_Boost_Off.loadFromFile("Photos/speedboost_button.png");
        Button_Boost_Off.setTexture(&Texture_Boost_Off);
        sf::Font font;
        font.loadFromFile(fontPath.string());
   
        sf::Text buttonTextSpeedBoosts;
        buttonTextSpeedBoosts.setFont(font);
        buttonTextSpeedBoosts.setCharacterSize(45);
        buttonTextSpeedBoosts.setFillColor(sf::Color::White);
        buttonTextSpeedBoosts.setString(wlaczSpeedUp && wlaczSpeedDown ? "Ikony szybkosci: ON" : "Ikony szybkosci: OFF");
        //inaczej da sie to zapisac: if (wlaczSpeedUp && wlaczSpeedDown) {
        //buttonTextSpeedBoosts.setString("Ikony szybkosci: ON")
        //} else {buttonTextSpeedBoosts.setString("Ikony szybkosci: OFF");
        buttonTextSpeedBoosts.setPosition(130, 478);

        sf::Sprite TloGry(BackgroundTla[WybraneTlo]);//Ustawia sprite tla na domysla wartosc
        while (Opcje.isOpen()) {
            sf::Event WyborOpcje;
            while (Opcje.pollEvent(WyborOpcje)) {
                if (WyborOpcje.type == sf::Event::Closed) {
                    Opcje.close();
                }
                if (WyborOpcje.type == sf::Event::KeyPressed) {
                    if (WyborOpcje.key.code == sf::Keyboard::Escape) {
                        Opcje.close();
                    }
                }

                //kod do wybierania tla w grze
                if (WyborOpcje.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f PozycjaMyszki = sf::Vector2f(sf::Mouse::getPosition(Opcje));
                    if (backgroundButton0.getGlobalBounds().contains(PozycjaMyszki)) {
                        WybraneTlo = 0;
                        TloGry.setTexture(BackgroundTla[WybraneTlo]);
                        infoText.setString("Zmieniono arene: Lod");
                        infoText.setPosition(100, 310);
                    }
                    else if (backgroundButton1.getGlobalBounds().contains(PozycjaMyszki)) {
                        WybraneTlo = 1;
                        TloGry.setTexture(BackgroundTla[WybraneTlo]);
                        infoText.setString("Zmieniono arene: Trawa");
                        infoText.setPosition(100, 310);
                    }
                    else if (backgroundButton2.getGlobalBounds().contains(PozycjaMyszki)) {
                        WybraneTlo = 2;
                        TloGry.setTexture(BackgroundTla[WybraneTlo]);
                        infoText.setString("Zmieniono arene: Woda");
                        infoText.setPosition(100, 310);
                    }
                    else if (plusButton.getGlobalBounds().contains(PozycjaMyszki)) {
                        if (liczbaBramek < 20) {//ograniczenie ze limit to do 20 bramek
                            liczbaBramek++;
                        };
                        bramkiOption.setString("Limit Goli: " + std::to_string(liczbaBramek));
                    }
                    else if (minusButton.getGlobalBounds().contains(PozycjaMyszki)) {
                        if (liczbaBramek > 1) {//warunek by nie dalo sie ustawic ponizej 1
                            liczbaBramek--;
                        };
                        bramkiOption.setString("Limit Goli: " + std::to_string(liczbaBramek));
                    }
                    else if (Button_Boost_Off.getGlobalBounds().contains(PozycjaMyszki)) {
                        wlaczSpeedUp = !wlaczSpeedUp;
                        wlaczSpeedDown = !wlaczSpeedDown; // Zmiana stanu przycisków
                        buttonTextSpeedBoosts.setString(wlaczSpeedUp && wlaczSpeedDown ? "Ikony szybkosci: ON" : "Ikony szybkosci: OFF");
                    }
                }
            }
            Opcje.clear();
            Opcje.draw(TloOpcji);
            Opcje.draw(backgroundOption);
            Opcje.draw(infoText);
            Opcje.draw(backgroundButton0);
            Opcje.draw(backgroundButton1);
            Opcje.draw(backgroundButton2);
            Opcje.draw(bramkiOption); // rysowanie tekstu z liczb¹ bramek
            Opcje.draw(plusButton); // rysowanie przycisku '+'
            Opcje.draw(minusButton); // rysowanie przycisku '-'
            Opcje.draw(Button_Boost_Off);//rysowanie przycisku do wylaczania boostow
            Opcje.draw(buttonTextSpeedBoosts);//rysowanie tekstu do wylaczania boostow

            Opcje.display();
        }
        Graj.close();
        // Tworzenie nowego okna gry
        RestartGry();
    }

    void Pomoc() {
        sf::RenderWindow Pomoc(sf::VideoMode(800, 600), "Pomoc");

        // tlo do opcji pomoc
        sf::RectangleShape TloPomoc;
        TloPomoc.setSize(sf::Vector2f(800, 600));
        sf::Texture PomocTexture;
        PomocTexture.loadFromFile("Photos/Zasady.jpg");
        TloPomoc.setTexture(&PomocTexture);

        // Tekst z zasadami gry
        sf::Font CzcionkaPomocy;
        CzcionkaPomocy.loadFromFile(fontPath.string());

        sf::Text PomocText;
        PomocText.setFont(CzcionkaPomocy);
        PomocText.setCharacterSize(18);
        PomocText.setFillColor(sf::Color::White);
        PomocText.setString(
            "ZASADY GRY W CYMBERGAJA:\n\n\n"
            "1. Gracze poruszaja krazkami, probujac odbijac pilke.\n\n"
            "2. Celem gry jest zdobycie ustalonej liczby bramek zanim zrobi to rywal.\n\n"
            "    Liczbe bramek mozesz ustalic w menu opcji.\n\n"
            "3. Pilka odbija sie od krawedzi krazkow oraz od scian boiska.\n\n"
            "4. Gracz moze poruszac krazkami tylko na swojej polowie.\n\n"
            "5. Na planszy w kazdej nowej grze sa obiekty, ktore maja wplyw na szybkosc krazka.\n\n"
            "   Ikona zajaca oznacza ze krazek przyspieszy, a zolwia - ze krazek zwolni.\n\n"
            "6. Gracze moga korzystac z przestrzeni bramkowej w celu odbicia pilki.\n\n\n"
            "Nacisnij ESC, aby wrocic do menu glownego."
        );
        PomocText.setPosition(50, 50);

        while (Pomoc.isOpen()) {
            sf::Event WyborPomoc;
            while (Pomoc.pollEvent(WyborPomoc)) {
                if (WyborPomoc.type == sf::Event::Closed) {
                    Pomoc.close();
                }
                if (WyborPomoc.type == sf::Event::KeyPressed) {
                    if (WyborPomoc.key.code == sf::Keyboard::Escape) {
                        Pomoc.close();
                    }
                }
            }
            Pomoc.clear();
            Pomoc.draw(TloPomoc);
            Pomoc.draw(PomocText);
            Pomoc.display();
        }
        Graj.close();
        RestartGry();
    }

    void RestartGry() {
        // Zamknij obecne okno gry
        Graj.close();

        // Ponownie zainicjuj obiekty gry
        player1 = Gracz1();
        player2 = Gracz2();
        ball = Pilka(400, 300);

        // Ponownie zainicjuj obiekty SpeedUp i SpeedDown w losowych miejscach
        Item_Up = SpeedUp(random(0, maxX), random(0, maxY));
        Item_Down = SpeedDown(random(0, maxX), random(0, maxY));

        // SprawdŸ i dezaktywuj SpeedUp i SpeedDown, jeœli zosta³y wy³¹czone
        if (!wlaczSpeedUp) {
            Item_Up.CzyAktywny = false;
        }
        if (!wlaczSpeedDown) {
            Item_Down.CzyAktywny = false;
        }

        // Ustaw tekstury obiektów gry
        ball.ball.setTexture(ball.ballTexture);
        player1.Krazek.setTexture(player1.KrazekTexture);
        player2.Krazek.setTexture(player2.KrazekTexture);
        Item_Up.obiekt.setTexture(&Item_Up.obiektTexture);
        Item_Down.obiekt.setTexture(&Item_Down.obiektTexture);

        // Wyœwietl obiekty gry na ekranie
        Item_Up.Wyswietl(Graj);
        Item_Down.Wyswietl(Graj);
    }
};