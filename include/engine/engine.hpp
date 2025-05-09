#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "engine/eventManager.hpp"
#include "engine/gameConsole.hpp"
#include "engine/visitorFactory.hpp"

#include "gameSerializer.hpp"
#include "refugio.hpp"

auto constexpr SAVE_FILE {"assets/save.txt"};      //< Nombre del archivo de guardado
auto constexpr CONFIG_FILE {"assets/system.conf"}; //< Nombre del archivo de configuración
auto constexpr CONSOLE_VERSION {"0.1.0"};          //< Versión de la consola

class Refugio;

/**
 * @brief: Clase que inicializa el motor del juego
 */
class Engine
{
public:
    /**
     * @brief: Inicializa el motor del juego
     */
    void start();

    /**
     * @brief: Carga la configuración del juego
     * @param: config Referencia a la configuración del juego
     */

    void engineConfig(const EngineData::GameConfig& config);

    /**
     * @brief: Obtiene la configuración del juego actual
     * @return: Referencia a la configuración del juego
     */
    const EngineData::GameConfig& engineConfig() const;

    /**
     * @brief: Carga el refugio del jugador
     * @param: refugio Referencia al refugio del jugador
     */
    void playerShelter(const Refugio& refugio);

    /**
     * @brief: Carga la información del jugador
     * @return: Referencia a la información del jugador
     */
    const Refugio& playerShelter() const;

    /**
     * @brief: Carga la información del jugador
     * @param: player Referencia a la información del jugador
     */
    void playerInfo(const EngineData::PlayerInfo& player);

    /**
     * @brief: Carga la información del jugador
     * @return: Referencia a la información del jugador
     */
    const EngineData::PlayerInfo& playerInfo() const;

    double wrapperRandomDouble(double min, double max)
    {
        return m_randomGenerator.getDouble(min, max);
    }

    template<typename TData>
    const TData& wrapperRandomChoice(const std::vector<TData>& vec)
    {
        return m_randomGenerator.randomChoice(vec);
    }

    bool checkEvent();

    void processEvent();

private:
    /**
     * @brief: Inicializa los recursos del tablero
     */
    void initResources();

    /**
     * @brief: Inicializa los elementos del tablero
     */
    static void initEntities();

    /**
     * @brief: Inicializa la consola interativa
     */
    void initConsole();

    /**
     * @brief: Carga la información de guardado
     */
    void loadGame();

    /**
     * @brief: Carga la configuración del juego
     */
    void loadConfig();

    EngineData::PlayerInfo m_player;        //< Información del jugador
    RandomEventGenerator m_randomGenerator; //< Generador de eventos aleatorios
    EngineData::GameConfig m_gameConfig;    //< Configuración del juego
    std::unique_ptr<Refugio> m_shelter;     //< Refugio del jugador
    std::unique_ptr<GameConsole> m_console;
    std::unique_ptr<EventManager> m_eventManager;
    std::unique_ptr<VisitorFactory> m_factory;
    std::unique_ptr<GameSerializer> m_serializer;
};

#endif // ENGINE_HPP
