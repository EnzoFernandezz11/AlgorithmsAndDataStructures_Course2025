#include "gameSerializer.hpp"
#include "engine.hpp"
#include "uiDef.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

void GameSerializer::save(const Engine& engine, const std::string& path)
{
    std::ofstream out(path);
    if (!out)
    {
        std::cout << RED << "[ERROR] Una rata ha mordido el archivo de guardado." << RESET << std::endl;
        std::cout << RED << "[ERROR] Por favor, contacte a su ingeniero de sistemas (Si es que sigue vivo)." << RESET
                  << std::endl;
        return;
    }

    const auto& player = engine.playerInfo();
    const auto& shelter = engine.playerShelter();

    out << "[Jugador]\n";
    out << "Nombre=" << player.name << "\n";
    out << "Nivel=" << player.level << "\n\n";

    // Add events later
}

bool GameSerializer::load(Engine& engine, const std::string& path)
{
    std::ifstream in(path);
    if (!in)
    {
        std::cout << RED << "[ERROR] El usuario hizo cualquier cosa y rompió el archivo de guardado." << RESET
                  << std::endl;
        std::cout << RED << "[ERROR] Por favor, contacte a su ingeniero de sistemas (Si es que sigue vivo)." << RESET
                  << std::endl;
        return false;
    }

    std::string line, section;
    EngineData::PlayerInfo player;
    std::string nombreRefugio;
    float defensa = 0, ataque = 0;
    std::vector<std::string> moradores;
    std::vector<std::pair<std::string, float>> recursos;
    std::vector<std::pair<std::string, std::string>> visitas;

    while (std::getline(in, line))
    {
        if (line.empty())
            continue;
        if (line[0] == '[')
        {
            section = line;
            continue;
        }

        if (section == "[Jugador]")
        {
            if (line.rfind("Nombre=", 0) == 0)
                player.name = line.substr(7);
            else if (line.rfind("Nivel=", 0) == 0)
                player.level = line.substr(6);
        }
        else if (section == "[Refugio]")
        {
            if (line.rfind("Nombre=", 0) == 0)
                nombreRefugio = line.substr(7);
            else if (line.rfind("Defensa=", 0) == 0)
                defensa = std::stof(line.substr(8));
            else if (line.rfind("Ataque=", 0) == 0)
                ataque = std::stof(line.substr(7));
        }
        else if (section == "[Moradores]")
        {
            moradores.push_back(line);
        }
        else if (section == "[Recursos]")
        {
            std::istringstream iss(line);
            std::string nombre;
            float cantidad;
            if (std::getline(iss, nombre, ',') && iss >> cantidad)
            {
                recursos.emplace_back(nombre, cantidad);
            }
        }
    }

    Refugio refugio(nombreRefugio, std::string {player.name});
    for (const auto& m : moradores) refugio.addRefugee(m);
    for (const auto& [r, c] : recursos) refugio.addResource(r, c);

    engine.playerInfo(player);
    engine.playerShelter(refugio);

    std::cout << BLUE << "[SUCCESS] Sistema VAULT restaurado con éxito." << RESET << std::endl;
    return true;
}
