#pragma once
#ifndef _PUZZLES_HPP_
#define _PUZZLES_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <sstream>
#include <iostream>

struct PUZZLES
{
    sf::Sprite Obrazok;
    int Cislo;
};

class Puzzles
{
private:
    sf::RenderWindow PuzzleWindow;
    sf::Clock Cas;
    sf::Image Obrazky[15];
    sf::Image Biela;
    sf::Sprite biela;
    sf::Image iButton;
    sf::Sprite Button;

    PUZZLES HraciaPlocha[4][4];
    int AktualnaPoziciaX;
    int AktualnaPoziciaY;
    int Smer;
    bool Kresli;
    int cas;

    void VykresliPrehodenie();
    void Prehod();
    std::string IntToString(int x);
    void RestartujCas();
    void VypisCas();

public:
    Puzzles();
    ~Puzzles();
    void VytvorOkno();
    bool ZavriOkno();
    void NacitajObrazky();
    void VypniRozmazanie();
    void VycistiPlochu();
    void VygenerujPlochu();
    void VykresliPlochu();
    bool Pohyb();
    bool OverenieRiesenia();
    void Pockaj();
    void StopCas();
};

#endif
