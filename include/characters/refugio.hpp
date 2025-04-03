#ifndef REFUGIO_HPP
#define REFUGIO_HPP

#include "engine.hpp"
#include "engineData.hpp"
#include "entidadGenerica.hpp"
#include "list.hpp"
#include "wrapperVector.hpp"
#include <iostream>
#include <string>
#include <utility>

/**
 * @class Refugio
 * @brief Representa un refugio dentro del Yermo
 *
 * Un refugio proporciona seguridad y almacenamiento de recursos para los moradores.
 * Tiene capacidades de defensa y ataque, además de una lista de refugiados y recursos disponibles.
 */
class Refugio : public EntidadGenerica
{

    /**
     * @struct Visitante
     * @brief Representa un visitante del refugio
     *
     * Contiene el nombre y la facción del visitante.
     */
    struct Visitante
    {
        std::string nombre;
        EngineData::Faction faccion;
    };

private:
    double m_defense;                                         ///< Nivel de defensa del refugio
    double m_attack;                                          ///< Capacidad de ataque del refugio
    wrapperVector<std::string> m_refugees;                    ///< Lista de moradores dentro del refugio
    wrapperVector<std::pair<std::string, float>> m_resources; ///< Lista de recursos con su cantidad
    DoublyLinkedList<Visitante>* m_visitants;                 ///< Lista de visitantes registrados

    std::string m_leader; ///< Nombre del líder del refugio

    void printRecursive(DoublyListNode<Visitante>* mNode)
    {
        if(mNode == nullptr)
        {
            return;
        }
        std::cout << "Nombre: " << mNode->data.nombre << ". Facción: " << faccionToString(mNode->data.faccion) << std::endl;
        printRecursive(mNode->next);
    }

    /**
     * @brief Devuelve la faccion en formato de string para su impresion.
     */
    std::string faccionToString(EngineData::Faction faccion) const
    {
        switch (faccion)
        {
        case EngineData::Faction::WATER_MERCHANTS:
            return "Mercaderes de agua";
        case EngineData::Faction::MERCHANTS:
            return "Mercaderes";
        case EngineData::Faction::REFUGEES:
            return "Refugiados";
        case EngineData::Faction::LOOTERS:
            return "Saqueadores";
        case EngineData::Faction::STEEL_BROTHERS:
            return "Hermanos de acero";
        case EngineData::Faction::ENCLAVE:
            return "Enclave";
        case EngineData::Faction::MUTANTS:
            return "Mutantes";
        case EngineData::Faction::RAIDERS:
            return "Asaltantes";
        case EngineData::Faction::GHOULS:
            return "Ghouls";
        case EngineData::Faction::CARAVAN:
            return "Caravanas";
        case EngineData::Faction::UNKNOWN:
            return "Desconocido";
        default:
            return "Faccion no reconocida";
        }
    }

public:
    /**
     * @brief Constructor del refugio
     *
     * @param name Nombre del refugio
     * @param leader Nombre del líder del refugio
     */
    Refugio(const std::string& name, const std::string& leader) :EntidadGenerica(name), m_leader(leader) {}

    /**
     * @brief Muestra la información del refugio
     */
    void showInfo() const override
    {
        std::cout << "Defensa: " << m_defense ; 
        std::cout << "Ataque: " << m_attack ; 
        std::cout << "Lider: " << m_leader ; 
        //(No vi oportuno agregar los moradores, recursos y visitantes)
    }

    /**
     * @brief Ejecuta una acción específica del refugio
     */
    void doAction() const
    {
        std::cout << "Binevenido al refugio " << m_name ;
    }

    /**
     * @brief Agrega un morador al refugio
     * @param refugee Nombre del morador
     */
    void addRefugee(const std::string& refugee)
    {
        m_refugees.push_back(refugee);
    }

    /**
     * @brief Agrega un recurso al refugio
     * @param resource Nombre del recurso
     * @param amount Cantidad del recurso
     */
    void addResource(const std::string& resource, float amount)
    {
        m_resources.push_back(std::make_pair(resource, amount));
    }

    /**
     * @brief Consume un recurso del refugio
     * @param resource Nombre del recurso a consumir
     * @param amount Cantidad a consumir
     * @return true si el consumo fue exitoso, false si no hay suficiente recurso
     */
    bool consumeResource(const std::string& resource, float amount)
    {
        for (int i = 0; i < m_resources.size(); i++)
        {
            if (m_resources[i].first == resource) 
            {
                if (m_resources[i].second >= amount) 
                {
                    m_resources[i].second -= amount;
                    return true; 
                } else 
                {
                    return false; 
                }
            }
        }
        return false; 
    }

    /**
     * @brief Registra un visitante en el refugio (nombre y facción)
     * @param nombre Nombre del visitante
     * @param faccion Facción del visitante
     */
    void registerVisitant(const std::string& nombre, EngineData::Faction faccion)
    {
        Visitante newVisit{nombre,faccion};
        m_visitants->push_front(newVisit);
    }

    /**
     * @brief Muestra todos los visitantes registrados
     */
    void showVisits()
    {
        printRecursive(m_visitants->get_head());
    }

    /**
     * @brief Busca si una facción ha visitado el refugio
     */
    bool hasFactionVisited(EngineData::Faction faccion) const
    {
        DoublyListNode<Visitante>* head = m_visitants->get_head();
        while (head != nullptr)
        {
            if(head->data.faccion == faccion)
            {
                return true;
            }
            head = head->next;
        }
        return false;
    }

    /**
     *
     * @param faccion Faccion a verificar si es segura.
     * @return Booleano si es segura o no.
     */
    bool isSafeFaction(EngineData::Faction faccion) const
    {
        if (faccion == EngineData::Faction::LOOTERS ||
            faccion == EngineData::Faction::MUTANTS ||
            faccion == EngineData::Faction::RAIDERS ||
            faccion == EngineData::Faction::GHOULS)
        {
            return false; 
        }
        return true; 
    };
};
#endif // REFUGIO_HPP
