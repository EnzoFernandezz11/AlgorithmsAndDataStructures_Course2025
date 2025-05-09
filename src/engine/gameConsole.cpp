#include "engine/gameConsole.hpp"
#include "engine/engine.hpp" // Include the full definition of Engine
#include "uiDef.hpp"

void GameConsole::showBanner()
{
    std::cout << GREEN
              << "         :---.  .---..---.   :--:..---..---..:------:.  . :-------.:-----:    .-+=.              "
              << RESET << '\n';
    std::cout << GREEN
              << "          :@@@-  =@@%.*@@@+   *@@#.:%@@-.@@@-.%@@@@@@%. .  =@@@@@@@:*@@@@@+  =@@@@@*             "
              << RESET << '\n';
    std::cout << GREEN
              << "           +@@%..@@@=:%@@@@.  *@@#.:%@@-.@@@-.::#@@%::.    .:=@@@::.*@@%::..*@@@+::: .           "
              << RESET << '\n';
    std::cout << GREEN
              << "           :@@@==@@%.=@@@@@=  *@@#.:%@@-.@@@-   #@@#........ -@@@.  *@@%::.-@@@-               . "
              << RESET << '\n';
    std::cout << GREEN
              << "           .*@@%%@@=.%@@+@@%. *@@#.:%@@-.@@@-   #@@#.-@@@@@* -@@@.  *@@@@@:=@@@.                 "
              << RESET << '\n';
    std::cout << GREEN
              << "            .@@@@@%.-@@%.@@@- *@@#.:%@@-.@@@- . #@@#.:+++++- -@@@.  *@@%==.-@@@:                 "
              << RESET << '\n';
    std::cout << GREEN
              << "             =@@@@-.#@@@@@@@* *@@%.:@@@-.@@@-...#@@#.        -@@@.  *@@%....#@@@-...             "
              << RESET << '\n';
    std::cout << GREEN
              << "             .%@@%.:@@@:.-@@@:-@@@@@@@@..@@@@@@-#@@#.  .     -@@@.  *@@@@@* .*@@@@@*             "
              << RESET << '\n';
    std::cout << GREEN
              << "             .=##=.=##+  .*##+..+%@@%=. .######:+##*.   .    :###.  =#####=  ..-#@%=        .    "
              << RESET << '\n';
    std::cout << GREEN
              << "  .                                                             .      .                          "
              << RESET << '\n';
    std::cout << GREEN
              << "           .           ..               ..-+%@@@@@@%+-..                       .                  "
              << RESET << '\n';
    std::cout << GREEN
              << "  .                          .        .=@@@@@@@@@@@@@@@@=.     .           . .      .             "
              << RESET << '\n';
    std::cout << GREEN
              << "           . .                    ...*@@@@%-:.   ..:-%@@@@*.                                      "
              << RESET << '\n';
    std::cout << GREEN
              << "                .-*@@@@@@@@@@@@@@@@@@@@@=.       .    .=@@@@@@@@@@@@@@@@@@@@@*-..             .   "
              << RESET << '\n';
    std::cout << GREEN
              << "                .-%@@@@@@@@@@@@@@@@@@@#.    .-*##*-.  . .#@@@@@@@@@@@@@@@@@@@%-.         ..       "
              << RESET << '\n';
    std::cout << GREEN
              << "                   ..............:@@@+.   :%@@@@@@@@%:   .+@@@:..............                     "
              << RESET << '\n';
    std::cout << GREEN
              << "        .          .          . .#@@%. ..=@@@@@@@@@@@@=.  .%@@*.      .              .     .      "
              << RESET << '\n';
    std::cout << GREEN
              << "   .:+%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+   :@@@@@@@@@@@@@%: . *@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%+:..   ."
              << RESET << '\n';
    std::cout << GREEN
              << "  .*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@+   :@@@@@@@@@@@@@@: . +@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@*.    "
              << RESET << '\n';
    std::cout << GREEN
              << "    ..:-+++++++++++++++++++++++++@@@*.  .%@@@@@@@@@@@@%.  .#@@@+++++++++++++++++++++++++-:..      "
              << RESET << '\n';
    std::cout << GREEN
              << " .                              .+@@@:  ..%@@@@@@@@@@%..  :@@@+                                   "
              << RESET << '\n';
    std::cout << GREEN
              << "      .          .:=*%@@@@@@@@@@@@@@@%.   .=%@@@@@@%-.   .@@@@@@@@@@@@@@@@%*-..                   "
              << RESET << '\n';
    std::cout << GREEN
              << "       .        :%@@@@@@@@@@@@@@@@@@@@@-   .            -@@@@@@@@@@@@@@@@@@@@@%:                  "
              << RESET << '\n';
    std::cout << GREEN
              << "                  .:=*###############@@@@=.          .=@@@@###############*-:.           .        "
              << RESET << '\n';
    std::cout << GREEN
              << "      .            ..                :#@@@@@#+=--=+#@@@@@#.                  .                    "
              << RESET << '\n';
    std::cout << GREEN
              << "            .                .         .=%@@@@@@@@@@@@%=.                                         "
              << RESET << '\n';
    std::cout << GREEN
              << "                  . .               ..    ...-=++=:...                   .                        "
              << RESET << '\n';
}

void GameConsole::showMenu()
{
    std::cout << GREEN << "========== CONSOLA DE OPERACIONES VAULT-TEC v" << CONSOLE_VERSION << " ==========" << RESET
              << '\n';
    std::cout << GREEN << "<> [i] status   " << RESET << " - Mostrar estado del refugio" << '\n';
    std::cout << GREEN << "<> [e] events   " << RESET << " - Ver historial de eventos" << '\n';
    std::cout << GREEN << "<> [c] check    " << RESET << " - Verificar evento activo" << '\n';
    std::cout << GREEN << "<> [x] explore  " << RESET << " - Realizar una exploración" << '\n';
    std::cout << GREEN << "<> [f] fight    " << RESET << " - Enfrentar a un enemigo" << '\n';
    std::cout << GREEN << "<> [s] save     " << RESET << " - Guardar el progreso" << '\n';
    std::cout << GREEN << "<> [q] exit     " << RESET << " - Salir del sistema" << '\n';
    std::cout << GREEN << "====================================" << RESET << '\n';
}

void GameConsole::clearScreen()
{
    std::system(CLEAR_SCREEN);
}

void GameConsole::setEngine(Engine* engine)
{
    m_engine = engine;
}

void GameConsole::executeCommand(const char& command)
{
    m_commandHistory.push_back(command);

    if (m_validOperations.find(command) != m_validOperations.end())
    {
        switch (m_validOperations.at(command))
        {
            case Operation::SHOW_STATUS:
                std::cout << GREEN << "=== [INFO] Cargando información del refugio ===" << RESET << '\n';
                m_engine->playerShelter().showInfo();
                break;
            case Operation::CHECK_EVENT:
                std::cout << GREEN << "=== [INFO] Cargando sistema de eventos ===" << RESET << '\n';
                if (m_engine->checkEvent())
                {
                    std::cout << GREEN << "=== [INFO] Un nuevo evento requiere de su atención ===" << RESET << '\n';
                    m_engine->processEvent();
                }
                else
                {
                    std::cout << GREEN << "=== [INFO] No hay novedades... Sonria :) ===" << RESET << '\n';
                }
                break;
            case Operation::EXIT:
                std::cout << "Saliendo..." << '\n';
                m_keepRunning = false;
                break;
            default: std::cout << "Operación desconocida" << '\n'; break;
        }
    }
    else
    {
        std::cout << "Operación desconocida" << '\n';
    }
    std::cin.ignore();
    std::cin.get();
}

void GameConsole::interativeLoop()
{
    while (m_keepRunning)
    {
        showBanner();
        showMenu();
        std::string input;
        std::cout << GREEN << "> " << RESET;
        std::cin >> input;

        executeCommand(input[0]);
    }
}
