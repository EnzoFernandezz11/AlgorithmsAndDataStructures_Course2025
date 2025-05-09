#ifndef REFUGIADO_HPP
#define REFUGIADO_HPP

#include "engine/engineData.hpp"
#include "entidadGenerica.hpp"
#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <variant>

uint8_t constexpr REFUGIADO_MAX_HEALTH {100}; ///< Máximo de salud
uint8_t constexpr REFUGIADO_MIN_HEALTH {80};  ///< Mínimo de salud

/**
 * @class Refugiado
 * @brief Representa a un refugiado en el mundo post-apocalíptico.
 *
 * Los refugiados pueden unirse a un refugio. Necesitan recursos para mantenerse
 * y, de no tenerlos, buscarán otro refugio donde vivir.
 */
class Refugee : public EntidadGenerica
{
private:
    int m_maxHealth;            ///< Salud del
    int m_health {m_maxHealth}; ///< Salud actual del refugiado
    std::unordered_map<EngineData::Resources, uint8_t> m_bag;
    bool m_isFromVault; ///< Si proviene de un refugio Vault (más débil)

    struct RefugiadoConsumibles
    {
        uint8_t m_consumeFood {0};     ///< Cantidad de comida consumida
        uint8_t m_consumeWater {0};    ///< Cantidad de agua consumida
        uint8_t m_consumeMedicine {0}; ///< Cantidad de medicina consumida
        uint8_t m_consumeAmmo {0};     ///< Cantidad de municiones consumidas
        uint8_t m_consumeTools {0};    ///< Cantidad de armas consumidas
    };

    struct VaultConsumibles
    {
        uint8_t m_consumeFood {0};        ///< Cantidad de comida consumida
        uint8_t m_consumeWater {0};       ///< Cantidad de agua consumida
        uint8_t m_consumeMedicine {0};    ///< Cantidad de medicina consumida
        uint8_t m_consumeAmmo {0};        ///< Cantidad de municiones consumidas
        uint8_t m_consumeTools {0};       ///< Cantidad de armas consumidas
        uint8_t m_consumeAlchohol {0};    ///< Cantidad de alcohol consumido
        uint8_t m_consumeElectronics {0}; ///< Cantidad de electrónica consumida
        uint8_t m_consumeMaterials {0};   ///< Cantidad de materiales consumidos
    };

    std::variant<RefugiadoConsumibles, VaultConsumibles> m_consumeRefugee;

public:
    /**
     * @brief Constructor del refugiado
     * @param name Nombre del refugiado
     * @param isFromVault Indica si proviene de un Vault o de la superficie
     */
    explicit Refugee(const std::string& name, bool isFromVault, std::unordered_map<EngineData::Resources, uint8_t> bag)
        : EntidadGenerica(name)
        , m_maxHealth(isFromVault ? REFUGIADO_MIN_HEALTH : REFUGIADO_MAX_HEALTH)
        , m_bag(std::move(bag))
        , m_isFromVault(isFromVault)
        , m_consumeRefugee(
              isFromVault
                  ? std::variant<RefugiadoConsumibles, VaultConsumibles> {std::in_place_type<VaultConsumibles>}
                  : std::variant<RefugiadoConsumibles, VaultConsumibles> {std::in_place_type<RefugiadoConsumibles>})

    {
    }

    /**
     * @brief Muestra la información del refugiado
     */
    void showInfo() const override
    {
        std::cout << "👤 Refugiado: " << m_name << "\n"
                  << " - Salud: " << m_health << "/" << m_maxHealth << "\n"
                  << " - Origen: " << (m_isFromVault ? "VAULT" : "Superficie") << "\n"
                  << " - Bolsa de recursos:\n";

        for (const auto& [resource, quantity] : m_bag)
        {
            std::cout << "\t\t* " << EngineData::valueToString(resource) << ": " << static_cast<int>(quantity) << "\n";
        }
    }

    void setManteinanceSupplies(std::variant<RefugiadoConsumibles, VaultConsumibles> supplies)
    {
        if (m_isFromVault && std::holds_alternative<VaultConsumibles>(supplies))
        {
            m_consumeRefugee = std::get<VaultConsumibles>(supplies);
        }
        else
        {
            m_consumeRefugee = std::get<RefugiadoConsumibles>(supplies);
        }
    }

    /**
     * @brief Consume suministros cada ciclo
     * @param cantidad Cantidad a consumir
     */
    void consumeSupplies(std::variant<RefugiadoConsumibles, VaultConsumibles> supplies)
    {
        bool keepInRefugee = true;

        if (m_isFromVault && std::holds_alternative<VaultConsumibles>(supplies))
        {
            auto& vaultSupplies = std::get<VaultConsumibles>(supplies);
            auto& refugeeNeeds = std::get<VaultConsumibles>(m_consumeRefugee);

            // Verifica y consume cada recurso, si alguno no alcanza, no se puede quedar
            if (vaultSupplies.m_consumeFood < refugeeNeeds.m_consumeFood ||
                vaultSupplies.m_consumeWater < refugeeNeeds.m_consumeWater ||
                vaultSupplies.m_consumeMedicine < refugeeNeeds.m_consumeMedicine ||
                vaultSupplies.m_consumeAmmo < refugeeNeeds.m_consumeAmmo ||
                vaultSupplies.m_consumeTools < refugeeNeeds.m_consumeTools ||
                vaultSupplies.m_consumeAlchohol < refugeeNeeds.m_consumeAlchohol ||
                vaultSupplies.m_consumeElectronics < refugeeNeeds.m_consumeElectronics ||
                vaultSupplies.m_consumeMaterials < refugeeNeeds.m_consumeMaterials)
            {
                keepInRefugee = false;
            }
            else
            {
                vaultSupplies.m_consumeFood -= refugeeNeeds.m_consumeFood;
                vaultSupplies.m_consumeWater -= refugeeNeeds.m_consumeWater;
                vaultSupplies.m_consumeMedicine -= refugeeNeeds.m_consumeMedicine;
                vaultSupplies.m_consumeAmmo -= refugeeNeeds.m_consumeAmmo;
                vaultSupplies.m_consumeTools -= refugeeNeeds.m_consumeTools;
                vaultSupplies.m_consumeAlchohol -= refugeeNeeds.m_consumeAlchohol;
                vaultSupplies.m_consumeElectronics -= refugeeNeeds.m_consumeElectronics;
                vaultSupplies.m_consumeMaterials -= refugeeNeeds.m_consumeMaterials;
            }
        }
        else if (!m_isFromVault && std::holds_alternative<RefugiadoConsumibles>(supplies))
        {
            auto& suppliesBasic = std::get<RefugiadoConsumibles>(supplies);
            auto& needs = std::get<RefugiadoConsumibles>(m_consumeRefugee);

            if (suppliesBasic.m_consumeFood < needs.m_consumeFood ||
                suppliesBasic.m_consumeWater < needs.m_consumeWater ||
                suppliesBasic.m_consumeMedicine < needs.m_consumeMedicine ||
                suppliesBasic.m_consumeAmmo < needs.m_consumeAmmo ||
                suppliesBasic.m_consumeTools < needs.m_consumeTools)
            {
                keepInRefugee = false;
            }
            else
            {
                suppliesBasic.m_consumeFood -= needs.m_consumeFood;
                suppliesBasic.m_consumeWater -= needs.m_consumeWater;
                suppliesBasic.m_consumeMedicine -= needs.m_consumeMedicine;
                suppliesBasic.m_consumeAmmo -= needs.m_consumeAmmo;
                suppliesBasic.m_consumeTools -= needs.m_consumeTools;
            }
        }
        else
        {
            keepInRefugee = false; // tipo de recurso no coincide con lo que espera el refugiado
        }

        if (keepInRefugee)
        {
            std::cout << "💬" << m_name << " >>> Gracias por mantenerme alimentado." << '\n';
        }
        else
        {
            std::cout << "💬" << m_name << " >>> No puedo quedarme sin recursos... buscaré otro lugar." << '\n';
        }
    }

    /**
     * @brief Intenta ingresar al refugio
     * @param espacioDisponible Si hay lugar y recursos disponibles
     */
    void requestShelter(bool espacioDisponible)
    {
        if (espacioDisponible)
        {
            std::cout << "💬" << m_name << " >>> Gracias por recibirme en su refugio." << std::endl;
        }
        else
        {
            std::cout << "💬" << m_name << " >>> Entiendo, seguiré buscando un lugar donde quedarme..." << std::endl;
        }
    }

    /**
     * @brief Devuelve si es de un Vault
     */
    bool isFromVault() const
    {
        return m_isFromVault;
    }
};

#endif // REFUGIADO_HPP
