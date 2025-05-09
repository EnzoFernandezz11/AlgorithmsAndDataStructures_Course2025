#ifndef RAIDER_HPP
#define RAIDER_HPP

#include <iostream>

#include "entidadGenerica.hpp"
#include "randomEventGenerator.hpp"

/**
 * @class Raider
 * @brief Representa una banda de asaltantes en el Yermo.
 *
 * Los Raiders suelen operar en grupos armados y bien organizados. Atacan para saquear,
 * pero en ocasiones pueden rendirse y pedir asilo si las cosas no salen como esperaban.
 */
class Raider : public EntidadGenerica
{
private:
    int m_integrantes;                                 ///< Cantidad de miembros en la banda
    double m_fireFactor;                               ///< Nivel de ataque general
    bool m_rendidos {false};                           ///< Indica si se han rendido
    bool m_seUnieron {false};                          ///< Indica si fueron aceptados en el refugio
    double m_rendicionChance;                          ///< Probabilidad de rendición
    RandomEventGenerator* m_randomgenerator {nullptr}; ///< Generador de eventos aleatorios

public:
    /**
     * @brief Constructor
     * @param nombre Nombre del grupo raider
     */
    explicit Raider(const std::string& nombre,
                       int integrantes,
                       RandomEventGenerator* randomGenerator,
                       double poderFuego,
                       double rendicionChance)
        : EntidadGenerica(nombre)
        , m_integrantes(integrantes)
        , m_fireFactor(poderFuego)
        , m_rendicionChance(rendicionChance)
        , m_randomgenerator(randomGenerator) // 30% de posibilidad de rendirse
    {
    }

    /**
     * @brief Muestra información del grupo raider
     */
    void showInfo() const override
    {
        std::cout << "🔫 RAIDERS: " << m_name << "\n"
                  << " - Miembros: " << m_integrantes << "\n"
                  << " - Factor de fuego: " << m_fireFactor << "\n"
                  << " - ¿Rendidos?: " << (m_rendidos ? "Sí" : "No") << "\n"
                  << " - ¿Se unieron al refugio?: " << (m_seUnieron ? "Sí" : "No") << "\n";
    }

    /**
     * @brief Simula el intento de rendición
     */
    void intentarRendicion()
    {
        if (m_randomgenerator->chance(m_rendicionChance))
        {
            m_rendidos = true;
            std::cout << "💬 " << m_name << " >>> ¡Nos rendimos! ¡Déjennos vivir!" << '\n';
        }
        else
        {
            std::cout << "💬 " << m_name << " >>> ¡Nunca nos rendiremos!" << '\n';
        }
    }

    /**
     * @brief Acepta a los raiders en el refugio si se rindieron
     */
    bool aceptarEnRefugio()
    {
        if (m_rendidos)
        {
            m_seUnieron = true;
            std::cout << "✅ Los raiders se han unido al refugio. Serán vigilados de cerca..." << '\n';
            return true;
        }

        std::cout << "❌ No se puede aceptar a un grupo hostil sin rendirse." << '\n';
        return false;
    }

    /**
     * @brief Devuelve el poder total del grupo
     */
    int poderTotal() const
    {
        return static_cast<int>(m_integrantes * m_fireFactor);
    }

    bool estanRendidos() const
    {
        return m_rendidos;
    }
    bool seUnieron() const
    {
        return m_seUnieron;
    }
};

#endif // RAIDER_HPP
