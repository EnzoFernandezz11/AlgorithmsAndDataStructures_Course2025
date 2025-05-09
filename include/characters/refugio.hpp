#ifndef REFUGIO_HPP
#define REFUGIO_HPP

#include <string>
#include <utility>

#include "engine/engineData.hpp"

#include "dataStructures/list.hpp"
#include "dataStructures/wrapperVector.hpp"

#include "characters/entidadGenerica.hpp"
#include "characters/npc.hpp"
#include "characters/refugiado.hpp"

uint8_t constexpr REFUGIO_BASE_CAPACITY {10}; ///< Máximo de defensa

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
    double m_defense; ///< Nivel de defensa del refugio
    double m_attack;  ///< Capacidad de ataque del refugio
    uint64_t m_maxCapacity {
        REFUGIO_BASE_CAPACITY};        ///< Maxima capacidad del refugio, determinado por el nivel del jugador
    std::vector<Refugee> m_refugees; ///< Lista de moradores dentro del refugio
    wrapperVector<std::pair<std::string, float>> m_resources; ///< Lista de recursos con su cantidad
    DoublyLinkedList<NPC::VisitanteVariant>* m_visitants;     ///< Lista de visitantes registrados

    std::string m_leader; ///< Nombre del líder del refugio

    void printRecursive(DoublyListNode<NPC::VisitanteVariant>* mNode);

public:
    /**
     * @brief Constructor del refugio
     *
     * @param name Nombre del refugio
     * @param leader Nombre del líder del refugio
     */
    Refugio(const std::string& name, const std::string& leader);

    /**
     * @brief Muestra la información del refugio
     */
    void showInfo() const override;

    /**
     * @brief Ejecuta una acción específica del refugio
     */
    void doAction() const;

    /**
     * @brief Agrega un morador al refugio
     * @param refugee Nombre del morador
     */
    void addRefugee(const std::string& refugee);

    /**
     * @brief Agrega un recurso al refugio
     * @param resource Nombre del recurso
     * @param amount Cantidad del recurso
     */
    void addResource(const std::string& resource, float amount);

    /**
     * @brief Consume un recurso del refugio
     * @param resource Nombre del recurso a consumir
     * @param amount Cantidad a consumir
     * @return true si el consumo fue exitoso, false si no hay suficiente recurso
     */
    bool consumeResource(const std::string& resource, float amount);

    /**
     * @brief Registra un visitante en el refugio
     * @param visitante Visitante a registrar
     */
    void registerVisitant(const NPC::VisitanteVariant& visitante);

    /**
     * @brief Muestra todos los visitantes registrados
     */
    void showVisits();

    /**
     * @brief Busca si una facción ha visitado el refugio
     */
    bool hasFactionVisited(EngineData::Faction faccion) const;

    /**
     *
     * @param faccion Faccion a verificar si es segura.
     * @return Booleano si es segura o no.
     */
    bool isSafeFaction(EngineData::Faction faccion) const;
};

#endif // REFUGIO_HPP
