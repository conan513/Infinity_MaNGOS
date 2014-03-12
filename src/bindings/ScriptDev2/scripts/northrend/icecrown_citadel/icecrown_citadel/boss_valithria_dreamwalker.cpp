/* Copyright (C) 2006 - 2013 ScriptDev2 <http://www.scriptdev2.com/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: boss_valithria
SD%Complete: 99%
SDComment:  by michalpolko with special thanks to:
            mangosR2 team and all who are supporting us with feedback, testing and fixes
            TrinityCore for some info about spells IDs
            everybody whom I forgot to mention here ;)

SDCategory: Icecrown Citadel
EndScriptData */

#include "precompiled.h"
#include "icecrown_citadel.h"

static LOCATION SpawnLoc[]=
{
    {4240.688477f, 2405.794678f, 364.868591f},  // 0 Valithria Room 1
    {4239.579102f, 2566.753418f, 364.868439f},  // 1 Valithria Room 2
    {4166.216797f, 2564.197266f, 364.873047f},  // 2 Valithria Room 3
    {4165.112305f, 2405.872559f, 364.872925f},  // 3 Valithria Room 4
};

enum BossSpells
{
    SPELL_NIGHTMARE_PORTAL_PRE      = 71977,
    SPELL_NIGHTMARE_PORTAL          = 71987,
    SPELL_TWISTED_NIGHTMARES        = 71941,
 // SPELL_TWISTED_NIGHTMARES_DOT    = 71940,
    SPELL_NIGHTMARE_CLOUD           = 71970, // Nightmare Clouds cast this on dreaming Valithria - she deals this dmg to Real Valithria
    SPELL_NIGHTMARE_CLOUD_VISUAL    = 71939,

    SPELL_DREAM_PORTAL_PRE          = 71301,
    SPELL_DREAM_PORTAL              = 71305,
    SPELL_EMERALD_VIGOR             = 70873,
    SPELL_DREAM_CLOUD_VISUAL        = 70876,

    SPELL_DREAM_STATE               = 70766,

    SPELL_DREAMWALKER_RAGE          = 71189,
    SPELL_IMMUNITY                  = 72724,
    SPELL_CORRUPTION                = 70904,
 // SPELL_DREAM_SLIP                = 71196,
 // SPELL_ICE_SPIKE                 = 70702,

 // SPELL_CLEAR_DREAMS_NIGHTMARES   = 75863, // script effect removes Emerald Vigor and Nightmare auras

    // summons
    // these spells should be applied to dummy npcs in gates
    // they should apply these auras once the encounter has started
    // but how to apply this, which spell on which npc and when? ;/
 // SPELL_SUMMON_TIMER_SUPPRESSER   = 70912,
 // SPELL_SUMMON_TIMER_SKELETON     = 70913,
 // SPELL_SUMMON_TIMER_ZOMBIE       = 70914,
 // SPELL_SUMMON_TIMER_ABOMIN       = 70915,
 // SPELL_SUMMON_TIMER_ARCHMAGE     = 70916,

    // Risen Archmage
    SPELL_FROSTBOLT_VOLLEY          = 70759,
    SPELL_MANA_VOID                 = 71179,
    SPELL_VOID_BUFF                 = 71085,
    SPELL_COLUMN_OF_FROST           = 70704,
    SPELL_COLUMN_OF_FROST_VISUAL    = 70715,
    SPELL_COLUMN_OF_FROST_TRIG      = 70702,

    // Blazing Skeleton
    SPELL_FIREBALL                  = 70754,
    SPELL_LAY_WASTE                 = 69325,

    // Suppresser
    SPELL_SUPPRESSION               = 70588, // NOTE: must stack from many casters

    // Blistering Zombie
    SPELL_CORROSION                 = 70749,
    SPELL_ACID_BURST                = 70744, // 750ms cast time. seems like it is cast always before dying

    // Gluttonous Abomination
    SPELL_GUT_SPRAY                 = 71283,
    SPELL_ROT_WORM_SPAWNER          = 70675, // cast around 30% HP or something?
    SPELL_ROT_WORM                  = 72962,

    NPC_RISEN_ARCHMAGE              = 37868,
 // NPC_COLUMN_OF_FROST             = 37918,
 // NPC_MANA_VOID                   = 38068,
    NPC_SUPPRESSER                  = 37863,
    NPC_BLAZING_SKELETON            = 36791,
    NPC_BLISTERING_ZOMBIE           = 37934,
    NPC_GLUTTONOUS_ABOMINATION      = 37886,
    NPC_ROT_WORM                    = 37907,

    SUMMON_TYPES_NUMBER             = 4,

 // NPC_NIGHTMARE_PORTAL_PRE        = 38429,
 // NPC_NIGHTMARE_PORTAL            = 38430,
 // NPC_NIGHTMARE_CLOUD             = 38421,
 // NPC_DREAM_PORTAL_PRE            = 38186,
 // NPC_DREAM_PORTAL                = 37945,
 // NPC_DREAM_CLOUD                 = 37985,

    // Achievements
    SPELL_ACHIEVEMENT_CREDIT        = 72706,
};

enum
{
    SAY_AGGRO                   = -1631140,
    SAY_PORTAL                  = -1631141,
    SAY_75_HEALTH               = -1631142,
    SAY_25_HEALTH               = -1631143,
    SAY_0_HEALTH                = -1631144,
 // SAY_PLAYER_DIES             = -1631145,
    SAY_BERSERK                 = -1631146,
    SAY_VICTORY                 = -1631147,
};

struct MANGOS_DLL_DECL boss_valithria_dreamwalkerAI : public ScriptedAI
{
    boss_valithria_dreamwalkerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiMapDifficulty = pCreature->GetMap()->GetDifficulty();
        m_bIsHeroic = m_uiMapDifficulty > RAID_DIFFICULTY_25MAN_NORMAL;
        m_bIs25Man = (m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_NORMAL || m_uiMapDifficulty == RAID_DIFFICULTY_25MAN_HEROIC);

        SetCombatMovement(false);
        DoCastSpellIfCan(m_creature, SPELL_CORRUPTION, CAST_TRIGGERED);

        Reset();
    }

    ScriptedInstance* m_pInstance;
    Difficulty m_uiMapDifficulty;
    bool m_bIsHeroic;
    bool m_bIs25Man;

    bool m_bIsEnrage;
    bool m_bSaidOver25;
    bool m_bSaidOver75;
    bool m_bIsHealed;

    uint32 m_uiEnrageTimer;
    uint32 m_uiHealthCheckTimer;
    uint32 m_uiSummonPortalsTimer;
    uint32 m_uiOutroTimer;

    uint32 m_uiSummonSuppresserTimer;
    uint32 m_uiSummonAbominationTimer;
    uint32 m_uiSummonZombieTimer;
    uint32 m_uiSummonSkeletonTimer;
    uint32 m_uiSummonArchmageTimer;

    uint8 m_uiSummonSuppresserCounter;
    uint8 m_uiSummonSkeletonCounter;

    float m_fHP;

    GuidList m_lSummonedAddsGuids;

    void AttackStart(Unit* /*pWho*/) override {}

    void Reset() override
    {
        m_bIsEnrage                 = false;
        m_bSaidOver25               = false;
        m_bSaidOver75               = false;
        m_bIsHealed                 = false;

        m_uiEnrageTimer             = 7 * MINUTE * IN_MILLISECONDS;
        m_uiHealthCheckTimer        = 30000; // no need to check in the beginning of the fight
        m_uiOutroTimer              = 4000;
        m_uiSummonPortalsTimer      = 30000;

        m_uiSummonSuppresserTimer   = 60000;
        m_uiSummonAbominationTimer  = 30000;
        m_uiSummonZombieTimer       = 35000;
        m_uiSummonSkeletonTimer     = 45000;
        m_uiSummonArchmageTimer     = 40000;

        m_uiSummonSuppresserCounter = 0;
        m_uiSummonSkeletonCounter   = 0;

        m_lSummonedAddsGuids.clear();

        m_creature->SetHealth(m_creature->GetMaxHealth() / 2.0f);
        m_fHP = 50.0f;

    }

    void JustDied(Unit* /*pKiller*/) override
    {
        DoScriptText(SAY_0_HEALTH, m_creature);

        if (m_pInstance)
        {
            DoRemoveAdds();
            m_pInstance->SetData(TYPE_VALITHRIA, FAIL);
        }
    }

    void DamageTaken(Unit* /*pDealer*/, uint32& uiDamage) override
    {
        if (m_fHP > 98.0f && m_creature->GetHealthPercent() == 100.0f)
            uiDamage = 0;
    }

    void DoSummonAdd(uint32 uiEntry)
    {
        uint32 loc = urand(0, m_bIs25Man ? 3 : 1);
        m_creature->SummonCreature(uiEntry, SpawnLoc[loc].x, SpawnLoc[loc].y, SpawnLoc[loc].z, 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 10000);

        // some additional control of summoning adds (anti flood system)
        if (!m_bIsEnrage)
        {
            if (m_uiSummonAbominationTimer < 5000)
                m_uiSummonAbominationTimer += 5000;
            else if (m_uiSummonZombieTimer < 5000)
                m_uiSummonZombieTimer += 5000;

            if (m_uiSummonArchmageTimer < 5000)
                m_uiSummonArchmageTimer += 5000;
            else if (m_uiSummonSkeletonTimer < 5000)
                m_uiSummonSkeletonTimer += 5000;
        }
    }

    void DoRemoveAdds()
    {
        for (GuidList::iterator i = m_lSummonedAddsGuids.begin(); i != m_lSummonedAddsGuids.end(); ++i)
        {
            if (Creature* pTmp = m_creature->GetMap()->GetCreature(*i))
                pTmp->ForcedDespawn();
        }

        std::list<Creature*> lWorms;
        GetCreatureListWithEntryInGrid(lWorms, m_creature, NPC_ROT_WORM, 100.0f);
        for (std::list<Creature*>::iterator i = lWorms.begin(); i != lWorms.end(); ++i)
            (*i)->ForcedDespawn();
    }

    Unit* SelectRandomPlayer(float range)
    {
        Map* pMap = m_creature->GetMap();
        Map::PlayerList const& playerlist = pMap->GetPlayers();
        if (playerlist.isEmpty())
            return NULL;

        std::vector<Unit*> list;
        list.clear();

        for (Map::PlayerList::const_iterator i = playerlist.begin(); i != playerlist.end(); ++i)
        {
            if (Player* player = i->getSource())
            {
                if (player->isGameMaster())
                    continue;

                if (!player->IsInMap(m_creature))
                    continue;

                if (player->isAlive() && player->IsWithinDistInMap(m_creature, range))
                    list.push_back((Unit*)player);
            }
        }

        if (list.empty())
            return NULL;
        else
            return list[urand(0, list.size() - 1)];
    }

    void JustSummoned(Creature* pCreature) override
    {
        m_lSummonedAddsGuids.push_back(pCreature->GetObjectGuid());
        if (pCreature->GetEntry() == NPC_SUPPRESSER)
            pCreature->FixateTarget(m_creature);
        else
        {
            pCreature->AddThreat(m_creature, 5000);
            pCreature->AI()->AttackStart(m_creature);
        }
        pCreature->SetInCombatWithZone();
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_VALITHRIA) != IN_PROGRESS)
            return;

        // Outro
        if (m_bIsHealed)
        {
            if (m_uiOutroTimer <= uiDiff)
            {
                if (m_pInstance)
                {
                    m_pInstance->SetData(TYPE_VALITHRIA, DONE);

                    if (Creature* pDummy = m_pInstance->GetSingleCreatureFromStorage(NPC_GREEN_DRAGON_COMBAT_TRIGGER))
                    {
                        // Set Valithria credit
                        pDummy->CastSpell(pDummy, SPELL_ACHIEVEMENT_CREDIT, true);
                    }
                }

                DoRemoveAdds(); // just to be sure
                m_uiOutroTimer = 30000;
                m_creature->ForcedDespawn(1000);
            }
            else
                m_uiOutroTimer -= uiDiff;

            return;
        }

        // Health Check
        if (m_uiHealthCheckTimer <= uiDiff)
        {
            m_fHP = m_creature->GetHealthPercent();

            // when reached 75% health
            if (!m_bSaidOver75)
            {
                if (m_fHP > 75.0f)
                {
                    DoScriptText(SAY_75_HEALTH, m_creature);
                    m_bSaidOver75 = true;
                }
            }

            // when reached 25% health
            if (!m_bSaidOver25)
            {
                if (m_fHP < 25.0f)
                {
                    DoScriptText(SAY_25_HEALTH, m_creature);
                    m_bSaidOver25 = true;
                }
            }

            // check if encounter is completed
            if (m_fHP > 99.0f && m_creature->GetHealth() == m_creature->GetMaxHealth())
            {
                if (DoCastSpellIfCan(m_creature, SPELL_DREAMWALKER_RAGE) == CAST_OK)
                {
                    DoScriptText(SAY_VICTORY, m_creature);
                    m_creature->RemoveAllAuras();
                    m_bIsHealed = true;
                    return;
                }
            }

            m_uiHealthCheckTimer = 1000;
        }
        else
            m_uiHealthCheckTimer -= uiDiff;

        // Enrage
        // After 7 minutes summoning of Suppressers is much faster
        if (!m_bIsEnrage)
        {
            if (m_uiEnrageTimer <= uiDiff)
            {
                DoScriptText(SAY_BERSERK, m_creature);
                m_bIsEnrage = true;
            }
            else
                m_uiEnrageTimer -= uiDiff;
        }

        // Summon Portals
        if (m_uiSummonPortalsTimer <= uiDiff)
        {
            uint8 uiMaxPortals = m_bIs25Man ? 8 : 4;

            // this way makes sure that spell is cast
            // this should be done via ScriptEffect spell, but we don't need it in SD2
            for (uint8 i = 0; i < uiMaxPortals; ++i)
                m_creature->CastSpell(m_creature, m_bIsHeroic ? SPELL_NIGHTMARE_PORTAL_PRE : SPELL_DREAM_PORTAL_PRE, true);

            if (!m_bIsHeroic)
                DoScriptText(SAY_PORTAL, m_creature);

            m_uiSummonPortalsTimer = 45000;
        }
        else
            m_uiSummonPortalsTimer -= uiDiff;

        // Summon adds

        // Summon Suppresser
        if (m_uiSummonSuppresserTimer <= uiDiff)
        {
            for (uint32 i = 0; i < urand(1, m_bIs25Man ? 3 : 2) + m_uiSummonSuppresserCounter; ++i)
                DoSummonAdd(NPC_SUPPRESSER);

            // 5s faster each summoning
            m_uiSummonSuppresserTimer = 60000 - (m_uiSummonSuppresserCounter * 5000); 
            if (m_uiSummonSuppresserCounter < 10)
                ++m_uiSummonSuppresserCounter;
        }
        else
            m_uiSummonSuppresserTimer -= uiDiff;

        // Summon Blazing Skeleton
        if (m_uiSummonSkeletonTimer <= uiDiff)
        {
            DoSummonAdd(NPC_BLAZING_SKELETON);
            // 5s faster each summoning
            m_uiSummonSkeletonTimer = 60000 - (m_uiSummonSkeletonCounter * 5000);
            if (m_uiSummonSkeletonCounter < 10)
                ++m_uiSummonSkeletonCounter;
        }
        else
            m_uiSummonSkeletonTimer -= uiDiff;

        // Summon Abomination
        if (m_uiSummonAbominationTimer <= uiDiff)
        {
            DoSummonAdd(NPC_GLUTTONOUS_ABOMINATION);
            m_uiSummonAbominationTimer = urand(30000, 60000);
        }
        else
            m_uiSummonAbominationTimer -= uiDiff;

        // Summon Zombie
        if (m_uiSummonZombieTimer <= uiDiff)
        {
            DoSummonAdd(NPC_BLISTERING_ZOMBIE);
            m_uiSummonZombieTimer = urand(25000, 50000);
        }
        else
            m_uiSummonZombieTimer -= uiDiff;

        // Summon Archmage
        if (m_uiSummonArchmageTimer <= uiDiff)
        {
            DoSummonAdd(NPC_RISEN_ARCHMAGE);
            m_uiSummonArchmageTimer = urand(20000, 50000);
        }
        else
            m_uiSummonArchmageTimer -= uiDiff;
    }
};

CreatureAI* GetAI_boss_valithria_dreamwalker(Creature* pCreature)
{
    return new boss_valithria_dreamwalkerAI(pCreature);
};

struct MANGOS_DLL_DECL mob_valithria_dream_phaseAI : public ScriptedAI
{
    mob_valithria_dream_phaseAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_creature->HandleEmoteState(EMOTE_STATE_FLYGRABCLOSED);
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
    }

    ScriptedInstance* m_pInstance;

    void Reset() override {}
    void UpdateAI(const uint32 /*uiDiff*/) override {}
    void AttackStart(Unit* /*pWho*/) override {}
    void DamageTaken(Unit* /*pDealer*/, uint32& uiDamage) override
    {
        if (m_pInstance && m_pInstance->GetData(TYPE_VALITHRIA) == IN_PROGRESS)
        {
            Creature* pValithria = m_pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA);
            if (pValithria && pValithria->isAlive())
            {
                pValithria->DealDamage(pValithria, uiDamage, NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NONE, NULL, false);
            }
        }

        uiDamage = 0;
    }
};

CreatureAI* GetAI_mob_valithria_dream_phase(Creature* pCreature)
{
    return new mob_valithria_dream_phaseAI(pCreature);
};

struct MANGOS_DLL_DECL mob_valithria_combat_triggerAI : public ScriptedAI
{
    mob_valithria_combat_triggerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        SetCombatMovement(false);
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_uiCheckTimer;
    uint32 m_uiResetTimer;

    void Reset() override
    {
        m_uiCheckTimer     = 2000;
        m_uiResetTimer     = 0;

        if (m_pInstance && m_pInstance->GetData(TYPE_VALITHRIA) != DONE)
        {
            m_creature->SummonCreature(NPC_VALITHRIA, TEMPSUMMON_MANUAL_DESPAWN, 0);
        }
    }

    void AttackStart(Unit* /*pWho*/) override {}
    void EnterEvadeMode() override {}


    void MoveInLineOfSight(Unit* pWho) override
    {
        if (!m_pInstance)
            return;

        uint32 uiState = m_pInstance->GetData(TYPE_VALITHRIA);
        if (uiState == IN_PROGRESS || uiState == DONE)
            return;

        if (pWho->GetTypeId() == TYPEID_PLAYER && !((Player*)pWho)->isGameMaster() &&
            m_creature->GetDistance(pWho) < 50.0f)
        {
            Creature* pGreenDragon = m_pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA);
            if (pGreenDragon && pGreenDragon->isAlive())
            {
                DoScriptText(SAY_AGGRO, pGreenDragon);
                DoCastSpellIfCan(pGreenDragon, SPELL_IMMUNITY, CAST_TRIGGERED);
                m_pInstance->SetData(TYPE_VALITHRIA, IN_PROGRESS);
                m_creature->SetInCombatWithZone();
            }
        }
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_pInstance || m_pInstance->GetData(TYPE_VALITHRIA) == DONE)
            return;

        if (m_uiResetTimer)
        {
            if (m_uiResetTimer <= uiDiff)
            {
                if (Creature* pGreenDragon = m_pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA))
                {
                    pGreenDragon->ForcedDespawn();
                    Reset();
                }
                m_uiResetTimer = 0;
            }
            else
                m_uiResetTimer -= uiDiff;

            return;
        }

        if (m_uiCheckTimer <= uiDiff)
        {
            if (Creature* pGreenDragon = m_pInstance->GetSingleCreatureFromStorage(NPC_VALITHRIA))
            {
                if (!pGreenDragon->isAlive())
                    m_uiResetTimer = 60000;
            }

            m_uiCheckTimer = 2000;
        }
        else
            m_uiCheckTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_valithria_combat_trigger(Creature* pCreature)
{
    return new mob_valithria_combat_triggerAI(pCreature);
};

// Gluttonous Abomination
struct MANGOS_DLL_DECL mob_gluttonous_abominationAI : public ScriptedAI
{
    mob_gluttonous_abominationAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiGutSprayTimer;

    void Reset() override
    {
        m_uiGutSprayTimer = urand(3000, 5000);
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        DoCastSpellIfCan(m_creature, SPELL_ROT_WORM_SPAWNER, CAST_TRIGGERED);
    }

    void JustSummoned(Creature* pCreature) override
    {
        pCreature->SetInCombatWithZone();
        pCreature->CastSpell(pCreature, SPELL_ROT_WORM, true);
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Gut Spray
        if (m_uiGutSprayTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_GUT_SPRAY) == CAST_OK)
                m_uiGutSprayTimer = urand(5000, 10000);
        }
        else
            m_uiGutSprayTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_gluttonous_abomination(Creature* pCreature)
{
    return new mob_gluttonous_abominationAI(pCreature);
};

// Blistering Zombie
struct MANGOS_DLL_DECL mob_blistering_zombieAI : public ScriptedAI
{
    mob_blistering_zombieAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    bool m_bHasDied;

    void Reset() override
    {
        m_bHasDied = false;
    }

    void Aggro(Unit* /*pWho*/) override
    {
        DoCastSpellIfCan(m_creature, SPELL_CORROSION, CAST_TRIGGERED);
    }

    void DamageTaken(Unit* /*pDealer*/, uint32& uiDamage) override
    {
        if (uiDamage > m_creature->GetHealth())
        {
            uiDamage = 0;
            SetCombatMovement(false, true);
            if (!m_bHasDied)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_ACID_BURST) == CAST_OK)
                {
                    m_bHasDied = true;
                    m_creature->ForcedDespawn(1000); // 750ms need for cast spell
                }
            }
        }
    }

    void UpdateAI(const uint32 /*uiDiff*/) override
    {
        if (m_bHasDied)
            return;

        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_blistering_zombie(Creature* pCreature)
{
    return new mob_blistering_zombieAI(pCreature);
};

// Risen Archmage
struct MANGOS_DLL_DECL mob_risen_archmageAI : public ScriptedAI
{
    mob_risen_archmageAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiFrostboltVolleyTimer;
    uint32 m_uiColumnOfFrostTimer;
    uint32 m_uiManaVoidTimer;

    void Reset() override
    {
        m_uiFrostboltVolleyTimer = urand(3000, 5000);
        m_uiColumnOfFrostTimer   = urand(3000, 5000);
        m_uiManaVoidTimer        = urand(5000, 10000);
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Frostbolt Volley
        if (m_uiFrostboltVolleyTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_FROSTBOLT_VOLLEY) == CAST_OK)
                m_uiFrostboltVolleyTimer = urand(5000, 15000);
        }
        else
            m_uiFrostboltVolleyTimer -= uiDiff;

        // Column of Frost
        if (m_uiColumnOfFrostTimer <= uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, uint32(0), SELECT_FLAG_PLAYER))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_COLUMN_OF_FROST) == CAST_OK)
                    m_uiColumnOfFrostTimer = urand(10000, 15000);
            }
        }
        else
            m_uiColumnOfFrostTimer -= uiDiff;

        // Mana Void
        if (m_uiManaVoidTimer <= uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, uint32(0), SELECT_FLAG_PLAYER))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_MANA_VOID) == CAST_OK)
                    m_uiManaVoidTimer = urand(10000, 15000);
            }
        }
        else
            m_uiManaVoidTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_risen_archmage(Creature* pCreature)
{
    return new mob_risen_archmageAI(pCreature);
};

// Blazing Skeleton
struct MANGOS_DLL_DECL mob_blazing_skeletonAI : public ScriptedAI
{
    mob_blazing_skeletonAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 m_uiFireballTimer;
    uint32 m_uiLayWasteTimer;

    void Reset() override
    {
        m_uiFireballTimer = urand(3000, 5000);
        m_uiLayWasteTimer = urand(15000, 30000);
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // Fireball
        if (m_uiFireballTimer <= uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, uint32(0), SELECT_FLAG_PLAYER))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_FIREBALL) == CAST_OK)
                    m_uiFireballTimer = urand(3000, 5000);
            }
        }
        else
            m_uiFireballTimer -= uiDiff;

        // Lay Waste
        if (m_uiLayWasteTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_LAY_WASTE) == CAST_OK)
                m_uiLayWasteTimer = urand(20000, 25000);
        }
        else
            m_uiLayWasteTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_blazing_skeleton(Creature* pCreature)
{
    return new mob_blazing_skeletonAI(pCreature);
};

// Suppresser
struct MANGOS_DLL_DECL mob_suppresserAI : public ScriptedAI
{
    mob_suppresserAI(Creature* pCreature) : ScriptedAI(pCreature){}

    void Reset() override {}

    void AttackStart(Unit* pWho) override
    {
        if (m_creature->Attack(pWho, false))
        {
            m_creature->AddThreat(pWho);
            m_creature->SetInCombatWith(pWho);
            pWho->SetInCombatWith(m_creature);

            m_creature->GetMotionMaster()->MoveChase(pWho, 20.0f, m_creature->GetAngle(pWho));
        }
    }

    void UpdateAI(const uint32 /*uiDiff*/) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->IsNonMeleeSpellCasted(false))
            return;

        if (m_creature->GetDistance2d(m_creature->getVictim()) < 21.0f)
            DoCastSpellIfCan(m_creature->getVictim(), SPELL_SUPPRESSION);
    }
};

CreatureAI* GetAI_mob_suppresser(Creature* pCreature)
{
    return new mob_suppresserAI(pCreature);
};

struct MANGOS_DLL_DECL mob_dream_portal_preAI : public ScriptedAI
{
    mob_dream_portal_preAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_uiSummonTimer = 10000;
    }

    uint32 m_uiSummonTimer;

    void Reset() override {}
    void AttackStart(Unit* /*pWho*/) override {}
    void UpdateAI(const uint32 uiDiff) override
    {
        if (m_uiSummonTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_DREAM_PORTAL, CAST_TRIGGERED) == CAST_OK)
            {
                m_uiSummonTimer = 1000;
                m_creature->ForcedDespawn(500);
            }
        }
        else
            m_uiSummonTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_dream_portal_pre(Creature* pCreature)
{
    return new mob_dream_portal_preAI(pCreature);
};

bool GossipHello_mob_dream_portal(Player* pPlayer, Creature* pCreature)
{
    pPlayer->CastSpell(pPlayer, SPELL_DREAM_STATE, true);
    pCreature->ForcedDespawn();
    return true;
}

struct MANGOS_DLL_DECL mob_dream_cloudAI : public ScriptedAI
{
    mob_dream_cloudAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_creature->SetRespawnDelay(15);
        Reset();
    }

    bool m_bHasCast;
    uint32 m_uiTimeToReset;

    void Reset() override
    {
        m_bHasCast = false;
        DoCastSpellIfCan(m_creature, SPELL_DREAM_CLOUD_VISUAL, CAST_TRIGGERED);
    }

    void AttackStart(Unit* /*pWho*/) override {}

    void MoveInLineOfSight(Unit* pWho) override
    {
        if (m_bHasCast)
            return;

        if (pWho->GetTypeId() == TYPEID_PLAYER)
        {
            if (m_creature->GetDistance(pWho) < 5.0f)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_EMERALD_VIGOR) == CAST_OK)
                {
                    m_bHasCast = true;
                    m_uiTimeToReset = 30000; // simulating respawn
                    m_creature->RemoveAllAuras();
                }
            }
        }
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (m_bHasCast)
        {
            if (m_uiTimeToReset <= uiDiff)
            {
                Reset();
            }
            else
                m_uiTimeToReset -= uiDiff;
        }
    }
};

CreatureAI* GetAI_mob_dream_cloud(Creature* pCreature)
{
    return new mob_dream_cloudAI(pCreature);
};

struct MANGOS_DLL_DECL mob_nightmare_portal_preAI : public ScriptedAI
{
    mob_nightmare_portal_preAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_uiSummonTimer = 15000;
    }

    uint32 m_uiSummonTimer;

    void Reset() override {}
    void AttackStart(Unit* /*pWho*/) override {}
    void UpdateAI(const uint32 uiDiff) override
    {
        if (m_uiSummonTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_NIGHTMARE_PORTAL, CAST_TRIGGERED) == CAST_OK)
            {
                m_uiSummonTimer = 1000;
                m_creature->ForcedDespawn(500);
            }
        }
        else
            m_uiSummonTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_nightmare_portal_pre(Creature* pCreature)
{
    return new mob_nightmare_portal_preAI(pCreature);
};

bool GossipHello_mob_nightmare_portal(Player* pPlayer, Creature* pCreature)
{
    pPlayer->CastSpell(pPlayer, SPELL_DREAM_STATE, true);
    pCreature->ForcedDespawn();
    return true;
}

struct MANGOS_DLL_DECL mob_nightmare_cloudAI : public ScriptedAI
{
    mob_nightmare_cloudAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    bool m_bHasCast;
    uint32 m_uiTimeToReset;

    void Reset() override
    {
        m_bHasCast = false;
        DoCastSpellIfCan(m_creature, SPELL_NIGHTMARE_CLOUD_VISUAL, CAST_TRIGGERED);
        DoCastSpellIfCan(m_creature, SPELL_NIGHTMARE_CLOUD, CAST_TRIGGERED);
    }

    void AttackStart(Unit* /*pWho*/) override {}

    void MoveInLineOfSight(Unit* pWho) override
    {
        if (m_bHasCast)
            return;

        if (pWho->GetTypeId() == TYPEID_PLAYER)
        {
            if (m_creature->GetDistance(pWho) < 5.0f)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_TWISTED_NIGHTMARES) == CAST_OK)
                {
                    m_bHasCast = true;
                    m_uiTimeToReset = 30000; // simulating respawn
                    m_creature->RemoveAllAuras();
                }
            }
        }
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (m_bHasCast)
        {
            if (m_uiTimeToReset <= uiDiff)
            {
                Reset();
            }
            else
                m_uiTimeToReset -= uiDiff;
        }
    }
};

CreatureAI* GetAI_mob_nightmare_cloud(Creature* pCreature)
{
    return new mob_nightmare_cloudAI(pCreature);
};

struct MANGOS_DLL_DECL mob_mana_voidAI : public ScriptedAI
{
    mob_mana_voidAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        DoCastSpellIfCan(m_creature, SPELL_VOID_BUFF, CAST_TRIGGERED);
        m_creature->ForcedDespawn(30000);
    }
    void Reset() override {}
    void AttackStart(Unit* /*pWho*/) override {}
    void UpdateAI(const uint32 /*uiDiff*/) override {}
};

CreatureAI* GetAI_mob_mana_void(Creature* pCreature)
{
    return new mob_mana_voidAI(pCreature);
};

struct MANGOS_DLL_DECL mob_column_of_frostAI : public ScriptedAI
{
    mob_column_of_frostAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_uiColumnOfFrostTimer = 3000;
        DoCastSpellIfCan(m_creature, SPELL_COLUMN_OF_FROST_VISUAL, CAST_TRIGGERED);
    }

    uint32 m_uiColumnOfFrostTimer;

    void Reset() override {}
    void AttackStart(Unit* /*pWho*/) override {}
    void UpdateAI(const uint32 uiDiff) override
    {
        // Column of Frost
        if (m_uiColumnOfFrostTimer <= uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_COLUMN_OF_FROST_TRIG) == CAST_OK)
            {
                m_uiColumnOfFrostTimer = 2000;
                m_creature->ForcedDespawn(1000);
            }
        }
        else
            m_uiColumnOfFrostTimer -= uiDiff;
    }
};

CreatureAI* GetAI_mob_column_of_frost(Creature* pCreature)
{
    return new mob_column_of_frostAI(pCreature);
};

void AddSC_boss_valithria_dreamwalker()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "boss_valithria_dreamwalker";
    pNewScript->GetAI = &GetAI_boss_valithria_dreamwalker;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_valithria_dream_phase";
    pNewScript->GetAI = &GetAI_mob_valithria_dream_phase;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_valithria_combat_trigger";
    pNewScript->GetAI = &GetAI_mob_valithria_combat_trigger;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_gluttonous_abomination";
    pNewScript->GetAI = &GetAI_mob_gluttonous_abomination;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_blistering_zombie";
    pNewScript->GetAI = &GetAI_mob_blistering_zombie;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_risen_archmage";
    pNewScript->GetAI = &GetAI_mob_risen_archmage;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_blazing_skeleton";
    pNewScript->GetAI = &GetAI_mob_blazing_skeleton;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_suppresser";
    pNewScript->GetAI = &GetAI_mob_suppresser;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_nightmare_portal_pre";
    pNewScript->GetAI = &GetAI_mob_nightmare_portal_pre;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_nightmare_portal";
    pNewScript->pGossipHello = &GossipHello_mob_nightmare_portal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_nightmare_cloud";
    pNewScript->GetAI = &GetAI_mob_nightmare_cloud;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_dream_portal_pre";
    pNewScript->GetAI = &GetAI_mob_dream_portal_pre;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_dream_portal";
    pNewScript->pGossipHello = &GossipHello_mob_dream_portal;

    pNewScript->RegisterSelf();
    pNewScript = new Script;
    pNewScript->Name = "mob_dream_cloud";
    pNewScript->GetAI = &GetAI_mob_dream_cloud;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_mana_void";
    pNewScript->GetAI = &GetAI_mob_mana_void;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_column_of_frost";
    pNewScript->GetAI = &GetAI_mob_column_of_frost;
    pNewScript->RegisterSelf();
}
