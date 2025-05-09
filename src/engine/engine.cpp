#include "engine/engine.hpp"
#include "uiDef.hpp"
#include <filesystem>
#include <fstream>

void Engine::start()
{
    m_randomGenerator = RandomEventGenerator();

    loadConfig();

    loadGame();

    initResources();

    initEntities();

    initConsole();

    m_eventManager->stop();
}

void Engine::initResources()
{
    std::cout << GREEN << "Inicializando recursos..." << RESET << '\n';
    m_console = std::make_unique<GameConsole>();
    m_console->setEngine(this);

    m_eventManager = std::make_unique<EventManager>();
    m_eventManager->setEngine(this);

    m_factory = std::make_unique<VisitorFactory>(m_randomGenerator, m_gameConfig);

    m_eventManager->setFactory(m_factory.get());

    m_eventManager->start();

    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Engine::initEntities()
{
    std::cout << GREEN << "Inicializando entidades..." << RESET << '\n';
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Engine::initConsole()
{
    m_console->interativeLoop();
}

void Engine::engineConfig(const EngineData::GameConfig& config)
{
    m_gameConfig = config;
}

const EngineData::GameConfig& Engine::engineConfig() const
{
    return m_gameConfig;
}

void Engine::playerShelter(const Refugio& refugio)
{
    m_shelter = std::make_unique<Refugio>(refugio);
}

const Refugio& Engine::playerShelter() const
{
    return *m_shelter;
}

void Engine::playerInfo(const EngineData::PlayerInfo& player)
{
    m_player = player;
}

const EngineData::PlayerInfo& Engine::playerInfo() const
{
    return m_player;
}

void Engine::loadGame()
{
    // Verifica sino existe un archivo de guardado
    if (std::filesystem::exists(SAVE_FILE))
    {
        std::cout << GREEN << "\n\n[INFO] Restableciendo información desde servidores centrales..." << RESET << '\n';
        if (!GameSerializer::load(*this, SAVE_FILE))
        {
            std::cout << RED << "[ERROR] Corte de luz detectado. EPEC no responde." << RESET << '\n';
            std::cout << RED << "Por favor, reinicie el sistema y verifique que estén los cables conectados." << RESET
                      << '\n';
            exit(1);
        }
    }
    else
    {
        std::cout << "\n\nNo se encontró información de guardado. Iniciando sistema después de masivo reinicio..."
                  << '\n';
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "\n\nAlgunos datos no están disponibles. Por favor, ingreselos" << '\n';
        std::cout << "Si no recuerda alguno, tome un descanso y vuelva a intentarlo." << '\n';
        std::cout << "Si no recuerda nada, por favor, reinicie el sistema." << '\n';
        std::cout << "Si no recuerda como reiniciar el sistema, por favor, largo de aqui." << '\n';

        std::cout << "\n\nPresione ENTER para continuar...";

        std::cin.get();

        std::cout << "Ingrese su nombre: ";
        std::string playerName;
        std::getline(std::cin, playerName);
        std::cout << "Ingrese el identificador unico provisto por VAULT TEC del refugio: ";
        std::string vaultId;
        std::getline(std::cin, vaultId);

        m_player.level = "1"; // Nivel inicial
        m_player.name = playerName;

        // Crea el refugio
        m_shelter = std::make_unique<Refugio>(vaultId, playerName);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        if (m_randomGenerator.chance(0.5f))
        {
            std::cout << GREEN << "\n\n ===== SISTEMA VAULT CARGADO ====" << RESET << '\n';
        }
        else
        {
            std::cout << RED << "\n\n ===== [ERROR] SISTEMA VAULT DAÑADO ====" << RESET << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            std::cout << RED << "\n\n ===== [ERROR] SISTEMA VAULT DAÑADO ====" << RESET << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
            std::cout << RED << "\n\n ===== [ERROR] SISTEMA VAULT DAÑADO ====" << RESET << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            std::cout << YELLOW << "\n\n ===== [INFO] PATEANDO SERVIDOR CENTRAL ====" << RESET << '\n';
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            std::cout << GREEN << "\n\n ===== SISTEMA VAULT CARGADO ====" << RESET << '\n';
        }

        // Guardar nueva información
        GameSerializer::save(*this, SAVE_FILE);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void Engine::loadConfig()
{
    std::cout << GREEN << "\n\n[INFO] Cargando configuracion..." << RESET << '\n';
    if (!std::filesystem::exists(CONFIG_FILE))
    {
        std::ofstream fileOut(CONFIG_FILE);
        if (!fileOut)
        {
            std::cerr << RED << "[ERROR] No se pudo crear el archivo de configuración. Hubo... un... corte de luz?"
                      << RESET << '\n';
            return;
        }
        fileOut << R"(# === CONFIGURACIÓN DEL SISTEMA REFUGIO 33 ===
# Este archivo define los parámetros de eventos, exploración y combates
# ¡Modifique bajo su propia responsabilidad!

[exploration]
successRate=0.45
lootChance=0.30
dangerChance=0.25

[fight]
criticalHitChance=0.15
criticalHitMultiplier=2.0
enemyAttackMultiplier=1.5
enemyDefenseMultiplier=1.2
enemyHealthMultiplier=1.3
enemyLootMultiplier=1.5
enemyExperienceMultiplier=1.5
luckyFactor=1.2
minEnemy=1
maxEnemy=10
surrenderChance=0.10

[resources]
successRate=0.50
lootChance=0.40
badLuckChance=0.20
durationFactor=1.5

[shelter]
defenseFactor=1.5
attackFactor=1.2

[events]
eventsPerSecond=10
rateRefugee=0.10
rateBrother=0.05
rateEnemy=0.50
rateCommerce=0.70
rateCaravane=0.02

# === FIN DEL ARCHIVO ===
)";
        fileOut.close();
        std::cout << GREEN << "[SUCCESS] Se generó el archivo de configuración por defecto.\n" << RESET;
    }

    std::ifstream inFile(CONFIG_FILE);
    if (!inFile)
    {
        std::cerr << RED << "[ERROR] No se pudo abrir el archivo de configuración. Que rompió?" << RESET << '\n';
        return;
    }

    std::string line;
    std::string section;
    while (std::getline(inFile, line))
    {
        if (line.empty() || line[0] == '#' || line[0] == ';')
        {
            continue;
        }
        if (line.front() == '[')
        {
            section = line;
            continue;
        }

        size_t eq = line.find('=');
        if (eq == std::string::npos)
        {
            continue;
        }

        std::string key = line.substr(0, eq);
        std::string val = line.substr(eq + 1);

        double value = std::stod(val);

        if (section == "[exploration]")
        {
            if (key == "successRate")
            {
                m_gameConfig.exploration.successRate = value;
            }
            else if (key == "lootChance")
            {
                m_gameConfig.exploration.lootChance = value;
            }
            else if (key == "dangerChance")
            {
                m_gameConfig.exploration.dangerChance = value;
            }
        }
        else if (section == "[fight]")
        {
            if (key == "criticalHitChance")
            {
                m_gameConfig.fight.criticalHitChance = value;
            }
            else if (key == "criticalHitMultiplier")
            {
                m_gameConfig.fight.criticalHitMultiplier = value;
            }
            else if (key == "enemyAttackMultiplier")
            {
                m_gameConfig.fight.enemyAttackMultiplier = value;
            }
            else if (key == "enemyDefenseMultiplier")
            {
                m_gameConfig.fight.enemyDefenseMultiplier = value;
            }
            else if (key == "enemyHealthMultiplier")
            {
                m_gameConfig.fight.enemyHealthMultiplier = value;
            }
            else if (key == "enemyLootMultiplier")
            {
                m_gameConfig.fight.enemyLootMultiplier = value;
            }
            else if (key == "enemyExperienceMultiplier")
            {
                m_gameConfig.fight.enemyExperienceMultiplier = value;
            }
            else if (key == "luckyFactor")
            {
                m_gameConfig.fight.luckyFactor = value;
            }
            else if (key == "minEnemy")
            {
                m_gameConfig.fight.minEnemy = static_cast<int>(value);
            }
            else if (key == "maxEnemy")
            {
                m_gameConfig.fight.maxEnemy = static_cast<int>(value);
            }
            else if (key == "surrenderChance")
            {
                m_gameConfig.fight.surrenderChance = value;
            }
        }
        else if (section == "[resources]")
        {
            if (key == "successRate")
            {
                m_gameConfig.resources.successRate = value;
            }
            else if (key == "lootChance")
            {
                m_gameConfig.resources.lootChance = value;
            }
            else if (key == "badLuckChance")
            {
                m_gameConfig.resources.badLuckChance = value;
            }
            else if (key == "durationFactor")
            {
                m_gameConfig.resources.durationFactor = value;
            }
        }
        else if (section == "[shelter]")
        {
            if (key == "defenseFactor")
            {
                m_gameConfig.shelter.defenseFactor = value;
            }
            else if (key == "attackFactor")
            {
                m_gameConfig.shelter.attackFactor = value;
            }
        }
        else if (section == "[events]")
        {
            if (key == "eventsPerSecond")
            {
                m_gameConfig.events.eventsPerSecond = static_cast<int>(value);
            }
            else if (key == "rateRefugee")
            {
                m_gameConfig.events.rateRefugee = value;
            }
            else if (key == "rateBrother")
            {
                m_gameConfig.events.rateBrother = value;
            }
            else if (key == "rateEnemy")
            {
                m_gameConfig.events.rateEnemy = value;
            }
            else if (key == "rateCommerce")
            {
                m_gameConfig.events.rateCommerce = value;
            }
            else if (key == "rateCaravane")
            {
                m_gameConfig.events.rateCaravane = value;
            }
        }
    }

    std::cout << GREEN << "[SUCCESS] Configuración cargada correctamente desde el servidor de VAULT\n" << RESET;
}

bool Engine::checkEvent()
{
    return !m_eventManager->isEmpty();
}

void Engine::processEvent()
{
    if (m_eventManager->isEmpty())
    {
        std::cout << YELLOW << "[INFO] No hay eventos disponibles." << RESET << '\n';
        return;
    }

    auto event = m_eventManager->popEvent();
    m_shelter->registerVisitant(event);
}
