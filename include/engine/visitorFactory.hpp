#ifndef VISITORFACTORY_HPP
#define VISITORFACTORY_HPP

class Engine; // Forward declaration of Engine

#include "characters/npc.hpp"
#include "randomEventGenerator.hpp"
#include <cstdint>
#include <unordered_map>

class VisitorFactory
{
    static const std::vector<std::string> NAMES;
    static const std::vector<std::string> SURNAMES;
    static const std::vector<std::string> GROUPS_ENEMIES;
    static const std::vector<std::string> MERCHANTS;

public:
    explicit VisitorFactory(RandomEventGenerator& rng, EngineData::GameConfig& config);
    NPC::VisitanteVariant create(EngineData::Faction faction);

private:
    RandomEventGenerator* m_randomGenetor;
    EngineData::GameConfig* m_config;

    std::unordered_map<EngineData::Resources, uint8_t> bagGenerator(bool isFromVault);
};

#endif // VISITORFACTORY_HPP
