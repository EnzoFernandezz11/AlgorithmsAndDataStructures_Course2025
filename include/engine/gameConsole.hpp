
#ifndef GAME_CONSOLE_HPP
#define GAME_CONSOLE_HPP

class Engine; // Forward declaration of Engine
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#ifdef _WIN32
#include <windows.h>
auto constexpr CLEAR_SCREEN {"cls"};
#else
#include <cstdlib>
auto constexpr CLEAR_SCREEN {"clear"};
#endif

/**
 * @class GameConsole
 * @brief Maneja los comandos de la consola (status, check, explore, etc.) y su interacción con el Engine.
 *
 * Esta clase proporciona una interfaz para interactuar con el motor del juego (Engine) a través de una consola.
 * Permite procesar comandos de texto, mantener un historial de comandos y generar salidas relacionadas con
 * las operaciones realizadas en el motor del juego.
 */
class GameConsole
{
public:
    void interativeLoop();

    void setEngine(Engine* engine);

private:
    // Stores the history of commands
    std::vector<char> m_commandHistory;

    // Stores the output of the console
    std::vector<std::string> m_outputBuffer;

    // Helper method to execute a command
    void executeCommand(const char& command);

    /**
     * @brief: Muestra el banner de bienvenida
     */
    void showBanner();

    /**
     * @brief: Muestra el menu principal
     */
    void showMenu();

    /**
     * @brief: Limpia la pantalla antes de mostrar el menú
     */
    void clearScreen();

    Engine* m_engine = nullptr;

    bool m_keepRunning {true}; //< Variable para controlar el bucle de ejecución
    /**
     * @brief: Operaciones que puede realizar el jugador
     */
    enum class Operation : uint8_t
    {
        SHOW_STATUS, //< Muestra el estado actual del refugio
        SHOW_EVENTS, //< Muestra los eventos aleatorios
        CHECK_EVENT, //< Muestra el evento actual
        EXPLORE,     //< Explora el mapa
        FIGHT,       //< Lucha contra un enemigo
        EXIT,        //< Salir del juego
        SAVE,        //< Guardar el juego
        UNKNOWN      //< Operación desconocida
    };

    std::unordered_map<char, Operation> m_validOperations = {{'i', Operation::SHOW_STATUS},
                                                             {'e', Operation::SHOW_EVENTS},
                                                             {'c', Operation::CHECK_EVENT},
                                                             {'x', Operation::EXPLORE},
                                                             {'f', Operation::FIGHT},
                                                             {'s', Operation::SAVE},
                                                             {'q', Operation::EXIT}};
};

#endif // GAME_CONSOLE_HPP
