#ifndef ARTEFACTOUNICO_HPP
#define ARTEFACTOUNICO_HPP

#include <algorithm>
#include <iostream>
#include <string>

#include "engine/engineData.hpp"
#include "entidadGenerica.hpp"

/**
 * @class ArtefactoUnico
 * @brief Representa un artefacto único dentro del universo de Refugio 33.
 *
 * Los artefactos únicos son ítems extremadamente valiosos, difíciles de encontrar y muy codiciados por facciones
 * como los Steel Brothers o las Caravanas. Pueden tener diversos efectos sobre el refugio si son activados o reparados.
 */
class ArtefactoUnico : public EntidadGenerica
{
private:
    EngineData::UniqueArtifactType
        m_type;          ///< Tipo de artefacto (por ejemplo: "Tecnología", "Arma", "Medicina", "Módulo de defensa")
    double m_durability; ///< Nivel de durabilidad restante del artefacto (de 0.0 a 100.0)

public:
    /**
     * @brief Constructor del artefacto único
     * @param name Nombre del artefacto
     * @param type Tipo del artefacto
     * @param durability Durabilidad inicial
     */
    explicit ArtefactoUnico(const std::string& name, const EngineData::UniqueArtifactType type, double durability)
        : EntidadGenerica(name)
        , m_type(type)
        , m_durability(durability)
    {
    }

    /**
     * @brief Muestra la información del artefacto único
     */
    void showInfo() const override
    {
        std::cout << "🧪 Artefacto: " << m_name << "\n"
                  << " - Tipo      : " << EngineData::valueToString(m_type) << "\n"
                  << " - Durabilidad: " << m_durability << "%" << '\n';
    }

    /**
     * @brief Simula el uso del artefacto, reduciendo su durabilidad
     * @param amount Cantidad de desgaste
     */
    void use(double amount)
    {
        m_durability -= amount;
        m_durability = std::max(m_durability, 0.0);
    }

    /**
     * @brief Verifica si el artefacto está roto
     * @return true si la durabilidad es cero, false en caso contrario
     */
    bool isBroken() const
    {
        return m_durability <= 0.0;
    }

    std::string nombre() const
    {
        return this->m_name;
    }
};

#endif // ARTEFACTOUNICO_HPP
