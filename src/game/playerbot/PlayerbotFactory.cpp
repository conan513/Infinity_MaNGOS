#include "../pchdef.h"
#include "playerbot.h"
#include "PlayerbotFactory.h"
#include "../SQLStorages.h"
#include "../ItemPrototype.h"
#include "PlayerbotAIConfig.h"
#include "../AccountMgr.h"
#include "../../shared/Database/DBCStore.h"
#include "../SharedDefines.h"

using namespace ai;
using namespace std;

void PlayerbotFactory::Randomize(bool incremental)
{
    if (!itemQuality)
    {
        if (level <= 10)
            itemQuality = urand(ITEM_QUALITY_NORMAL, ITEM_QUALITY_UNCOMMON);
        else if (level <= 20)
            itemQuality = urand(ITEM_QUALITY_UNCOMMON, ITEM_QUALITY_RARE);
        else if (level <= 40)
            itemQuality = urand(ITEM_QUALITY_UNCOMMON, ITEM_QUALITY_EPIC);
        else if (level < 60)
            itemQuality = urand(ITEM_QUALITY_UNCOMMON, ITEM_QUALITY_EPIC);
        else
            itemQuality = urand(ITEM_QUALITY_RARE, ITEM_QUALITY_EPIC);
    }

    if (bot->isDead())
        bot->ResurrectPlayer(1.0f, false);

    bot->CombatStop(true);
    bot->SetLevel(level);
    bot->SetFlag(PLAYER_FLAGS, PLAYER_FLAGS_HIDE_HELM);
    bot->SetFlag(PLAYER_FLAGS, PLAYER_FLAGS_HIDE_CLOAK);

    bot->resetTalents(true, true);
    ClearSpells();
    ClearInventory();
    bot->SaveToDB();

    InitQuests();
    // quest rewards boost bot level, so reduce back
    bot->SetLevel(level);
    ClearInventory();
    bot->SetUInt32Value(PLAYER_XP, 0);
    CancelAuras();
    bot->SaveToDB();

    InitAvailableSpells();
    InitSkills();
    InitTalents();
    InitAvailableSpells();
    InitSpecialSpells();
    InitMounts();
    bot->SaveToDB();

    InitEquipment(incremental);
    InitBags();
    InitAmmo();
    InitPotions();
    InitSecondEquipmentSet();
    InitInventory();
    bot->SaveToDB();

    InitPet();
    bot->SaveToDB();
}

void PlayerbotFactory::InitPet()
{
    Pet* pet = bot->GetPet();
    if (!pet)
    {
        if (bot->getClass() != CLASS_HUNTER)
            return;

        Map* map = bot->GetMap();
        if (!map)
            return;

		vector<uint32> ids;
        for (uint32 id = 0; id < sCreatureStorage.GetMaxEntry(); ++id)
        {
            CreatureInfo const* co = sCreatureStorage.LookupEntry<CreatureInfo>(id);
            if (!co || !co->isTameable(false))
                continue;

			PetLevelInfo const* petInfo = sObjectMgr.GetPetLevelInfo(co->Entry, bot->getLevel());
            if (!petInfo)
                continue;

			ids.push_back(id);
		}

		for (int i = 0; i < 100; i++)
		{
			int index = urand(0, ids.size());
			CreatureInfo const* co = sCreatureStorage.LookupEntry<CreatureInfo>(ids[index]);

            uint32 guid = map->GenerateLocalLowGuid(HIGHGUID_PET);
            CreatureCreatePos pos(map, bot->GetPositionX(), bot->GetPositionY(), bot->GetPositionZ(), bot->GetOrientation(), bot->GetPhaseMask());
            pet = new Pet(HUNTER_PET);
            if (!pet->Create(guid, pos, co, 0, bot))
            {
                delete pet;
                pet = NULL;
                continue;
            }

            pet->SetOwnerGuid(bot->GetObjectGuid());
            pet->SetCreatorGuid(bot->GetObjectGuid());
            pet->setFaction(bot->getFaction());
            pet->SetLevel(bot->getLevel());
            bot->SetPet(pet);

            pet->Summon();
            pet->SavePetToDB(PET_SAVE_AS_CURRENT);
            break;
        }
    }

    if (!pet)
    {
        sLog.outError("Cannot create pet for bot %s", bot->GetName());
        return;
    }

    for (PetSpellMap::const_iterator itr = pet->m_spells.begin(); itr != pet->m_spells.end(); ++itr)
    {
        if(itr->second.state == PETSPELL_REMOVED)
            continue;

        uint32 spellId = itr->first;
        if(IsPassiveSpell(spellId))
            continue;

        pet->ToggleAutocast(spellId, true);
    }
}

void PlayerbotFactory::ClearSpells()
{
    list<uint32> spells;
    for(PlayerSpellMap::iterator itr = bot->GetSpellMap().begin(); itr != bot->GetSpellMap().end(); ++itr)
    {
        uint32 spellId = itr->first;
        if(itr->second.state == PLAYERSPELL_REMOVED || itr->second.disabled || IsPassiveSpell(spellId))
            continue;

        spells.push_back(spellId);
    }

    for (list<uint32>::iterator i = spells.begin(); i != spells.end(); ++i)
    {
        bot->removeSpell(*i);
    }
}

void PlayerbotFactory::InitSpells()
{
    for (int i = 0; i < 15; i++)
        InitAvailableSpells();
}

void PlayerbotFactory::InitTalents()
{
    uint32 specNo = urand(0, 2);
    InitTalents(specNo);

    if (bot->GetFreeTalentPoints())
        InitTalents(2 - specNo);
}


class DestroyItemsVisitor : public IterateItemsVisitor
{
public:
    DestroyItemsVisitor(Player* bot) : IterateItemsVisitor(), bot(bot) {}

    virtual bool Visit(Item* item)
    {
        uint32 id = item->GetProto()->ItemId;
        if (CanKeep(id))
        {
            keep.insert(id);
            return true;
        }

        bot->DestroyItem(item->GetBagSlot(), item->GetSlot(), true);
        return true;
    }

private:
    bool CanKeep(uint32 id)
    {
        if (keep.find(id) != keep.end())
            return false;

        if (sPlayerbotAIConfig.IsInRandomQuestItemList(id))
            return true;

        ItemPrototype const* proto = sItemStorage.LookupEntry<ItemPrototype>(id);
        if (proto->Class == ITEM_CLASS_MISC && (proto->SubClass == ITEM_SUBCLASS_JUNK_REAGENT || proto->SubClass == ITEM_SUBCLASS_JUNK))
            return true;

        return false;
    }

private:
    Player* bot;
    set<uint32> keep;

};

bool PlayerbotFactory::CanEquipArmor(ItemPrototype const* proto, uint8 slot)
{
    if (bot->HasSkill(SKILL_SHIELD) && proto->SubClass == ITEM_SUBCLASS_ARMOR_SHIELD)
        return true;

    if (bot->HasSkill(SKILL_PLATE_MAIL))
    {
        if (proto->SubClass != ITEM_SUBCLASS_ARMOR_PLATE)
            return false;
    }
    else if (bot->HasSkill(SKILL_MAIL))
    {
        if (proto->SubClass != ITEM_SUBCLASS_ARMOR_MAIL)
            return false;
    }
    else if (bot->HasSkill(SKILL_LEATHER))
    {
        if (proto->SubClass != ITEM_SUBCLASS_ARMOR_LEATHER)
            return false;
    }

    if (proto->Quality <= ITEM_QUALITY_NORMAL)
        return true;

    uint8 sp = 0, ap = 0, tank = 0;
    for (int j = 0; j < MAX_ITEM_PROTO_STATS; ++j)
    {
        // for ItemStatValue != 0
        if(!proto->ItemStat[j].ItemStatValue)
            continue;

        AddItemStats(proto->ItemStat[j].ItemStatType, sp, ap, tank);
    }

    return CheckItemStats(sp, ap, tank);
}

bool PlayerbotFactory::CheckItemStats(uint8 sp, uint8 ap, uint8 tank)
{
    switch (bot->getClass())
    {
    case CLASS_PRIEST:
    case CLASS_MAGE:
    case CLASS_WARLOCK:
        if (!sp || ap > sp || tank > sp)
            return false;
        break;
    case CLASS_PALADIN:
    case CLASS_WARRIOR:
        if ((!ap && !tank) || sp > ap || sp > tank)
            return false;
        break;
    case CLASS_HUNTER:
    case CLASS_ROGUE:
        if (!ap || sp > ap || sp > tank)
            return false;
        break;
    }

    return sp || ap || tank;
}

void PlayerbotFactory::AddItemStats(uint32 mod, uint8 &sp, uint8 &ap, uint8 &tank)
{
    switch (mod)
    {
    case ITEM_MOD_HIT_RATING:
    case ITEM_MOD_CRIT_RATING:
    case ITEM_MOD_HASTE_RATING:
    case ITEM_MOD_HEALTH:
    case ITEM_MOD_STAMINA:
    case ITEM_MOD_HEALTH_REGEN:
    case ITEM_MOD_MANA:
    case ITEM_MOD_INTELLECT:
    case ITEM_MOD_SPIRIT:
    case ITEM_MOD_MANA_REGENERATION:
    case ITEM_MOD_SPELL_POWER:
    case ITEM_MOD_SPELL_PENETRATION:
    case ITEM_MOD_HIT_SPELL_RATING:
    case ITEM_MOD_CRIT_SPELL_RATING:
    case ITEM_MOD_HASTE_SPELL_RATING:
        sp++;
        break;
    }

    switch (mod)
    {
    case ITEM_MOD_HIT_RATING:
    case ITEM_MOD_CRIT_RATING:
    case ITEM_MOD_HASTE_RATING:
    case ITEM_MOD_AGILITY:
    case ITEM_MOD_STRENGTH:
    case ITEM_MOD_HEALTH:
    case ITEM_MOD_STAMINA:
    case ITEM_MOD_HEALTH_REGEN:
    case ITEM_MOD_DEFENSE_SKILL_RATING:
    case ITEM_MOD_DODGE_RATING:
    case ITEM_MOD_PARRY_RATING:
    case ITEM_MOD_BLOCK_RATING:
    case ITEM_MOD_HIT_TAKEN_MELEE_RATING:
    case ITEM_MOD_HIT_TAKEN_RANGED_RATING:
    case ITEM_MOD_HIT_TAKEN_SPELL_RATING:
    case ITEM_MOD_CRIT_TAKEN_MELEE_RATING:
    case ITEM_MOD_CRIT_TAKEN_RANGED_RATING:
    case ITEM_MOD_CRIT_TAKEN_SPELL_RATING:
    case ITEM_MOD_HIT_TAKEN_RATING:
    case ITEM_MOD_CRIT_TAKEN_RATING:
    case ITEM_MOD_RESILIENCE_RATING:
    case ITEM_MOD_BLOCK_VALUE:
        tank++;
        break;
    }

    switch (mod)
    {
    case ITEM_MOD_HEALTH:
    case ITEM_MOD_STAMINA:
    case ITEM_MOD_HEALTH_REGEN:
    case ITEM_MOD_AGILITY:
    case ITEM_MOD_STRENGTH:
    case ITEM_MOD_HIT_MELEE_RATING:
    case ITEM_MOD_HIT_RANGED_RATING:
    case ITEM_MOD_CRIT_MELEE_RATING:
    case ITEM_MOD_CRIT_RANGED_RATING:
    case ITEM_MOD_HASTE_MELEE_RATING:
    case ITEM_MOD_HASTE_RANGED_RATING:
    case ITEM_MOD_HIT_RATING:
    case ITEM_MOD_CRIT_RATING:
    case ITEM_MOD_HASTE_RATING:
    case ITEM_MOD_EXPERTISE_RATING:
    case ITEM_MOD_ATTACK_POWER:
    case ITEM_MOD_RANGED_ATTACK_POWER:
    case ITEM_MOD_ARMOR_PENETRATION_RATING:
        ap++;
        break;
    }
}

bool PlayerbotFactory::CanEquipWeapon(ItemPrototype const* proto, uint8 slot)
{
    switch (bot->getClass())
    {
    case CLASS_PRIEST:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_STAFF &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_WAND &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE)
            return false;
        break;
    case CLASS_MAGE:
    case CLASS_WARLOCK:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_STAFF &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_WAND &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD)
            return false;
        break;
    case CLASS_WARRIOR:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE2 &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD2 &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_GUN &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_CROSSBOW &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_BOW &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_THROWN)
            return false;
        break;
    case CLASS_PALADIN:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE2 &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD2 &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD)
            return false;
        break;
    case CLASS_SHAMAN:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE)
            return false;
        break;
    case CLASS_DRUID:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE2 &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_STAFF)
            return false;
        break;
    case CLASS_HUNTER:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_AXE2 &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD2 &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_GUN &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_CROSSBOW &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_BOW)
            return false;
        break;
    case CLASS_ROGUE:
        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_DAGGER &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_GUN &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_CROSSBOW &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_BOW &&
                proto->SubClass != ITEM_SUBCLASS_WEAPON_THROWN)
            return false;
        break;
    }

    return true;
}

bool PlayerbotFactory::CanEquipItem(ItemPrototype const* proto, uint32 desiredQuality)
{
    if (proto->Duration & 0x80000000)
        return false;

    if (proto->Quality != desiredQuality)
        return false;

    uint32 requiredLevel = proto->RequiredLevel;
    if (desiredQuality > ITEM_QUALITY_NORMAL &&
            (!requiredLevel || requiredLevel > level || requiredLevel < level - 10))
        return false;

    if (!requiredLevel)
        return true;

    for (uint32 gap = 60; gap <= 80; gap += 10)
    {
        if (level > gap && requiredLevel <= gap)
            return false;
    }

    return true;
}

void PlayerbotFactory::InitEquipment(bool incremental)
{
    DestroyItemsVisitor visitor(bot);
    IterateItems(&visitor, ITERATE_ALL_ITEMS);

    map<uint8, vector<uint32> > items;
    for(uint8 slot = 0; slot < EQUIPMENT_SLOT_END; ++slot)
    {
        if (slot == EQUIPMENT_SLOT_TABARD || slot == EQUIPMENT_SLOT_BODY)
            continue;

        uint32 desiredQuality = itemQuality;
        if (urand(0, 100) < 100 * sPlayerbotAIConfig.randomGearLoweringChance && desiredQuality > ITEM_QUALITY_NORMAL) {
            desiredQuality--;
        }

        do
        {
            for (uint32 itemId = 0; itemId < sItemStorage.GetMaxEntry(); ++itemId)
            {
                ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);
                if (!proto)
                    continue;

                if (proto->Class != ITEM_CLASS_WEAPON &&
                    proto->Class != ITEM_CLASS_ARMOR &&
                    proto->Class != ITEM_CLASS_CONTAINER &&
                    proto->Class != ITEM_CLASS_PROJECTILE)
                    continue;

                if (!CanEquipItem(proto, desiredQuality))
                    continue;

                if (proto->Class == ITEM_CLASS_ARMOR && (
                    slot == EQUIPMENT_SLOT_HEAD ||
                    slot == EQUIPMENT_SLOT_SHOULDERS ||
                    slot == EQUIPMENT_SLOT_CHEST ||
                    slot == EQUIPMENT_SLOT_WAIST ||
                    slot == EQUIPMENT_SLOT_LEGS ||
                    slot == EQUIPMENT_SLOT_FEET ||
                    slot == EQUIPMENT_SLOT_WRISTS ||
                    slot == EQUIPMENT_SLOT_HANDS) && !CanEquipArmor(proto, slot))
                        continue;

                if (proto->Class == ITEM_CLASS_WEAPON && !CanEquipWeapon(proto, slot))
                    continue;

                if (slot == EQUIPMENT_SLOT_OFFHAND && bot->getClass() == CLASS_ROGUE && proto->Class != ITEM_CLASS_WEAPON)
                    continue;

                uint16 dest = 0;
                if (CanEquipUnseenItem(slot, dest, itemId))
                    items[slot].push_back(itemId);
            }
        } while (items[slot].empty() && desiredQuality-- > ITEM_QUALITY_NORMAL);
    }

    for(uint8 slot = 0; slot < EQUIPMENT_SLOT_END; ++slot)
    {
        if (slot == EQUIPMENT_SLOT_TABARD || slot == EQUIPMENT_SLOT_BODY)
            continue;

        vector<uint32>& ids = items[slot];
        if (ids.empty())
        {
            sLog.outError("%s: no items to equip for slot %d", bot->GetName(), slot);
            continue;
        }

        for (int attempts = 0; attempts < 15; attempts++)
        {
            uint32 index = urand(0, ids.size() - 1);
            uint32 newItemId = ids[index];
            Item* oldItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);

            if (incremental && !IsDesiredReplacement(oldItem)) {
                continue;
            }

            uint16 dest;
            if (!CanEquipUnseenItem(slot, dest, newItemId))
                continue;

            if (oldItem)
            {
                bot->RemoveItem(INVENTORY_SLOT_BAG_0, slot, true);
                oldItem->DestroyForPlayer(bot, false);
            }

            Item* newItem = bot->EquipNewItem(dest, newItemId, true);
            if (newItem)
            {
                newItem->AddToWorld();
                newItem->AddToUpdateQueueOf(bot);
                bot->AutoUnequipOffhandIfNeed();
                EnchantItem(newItem);
                break;
            }
        }
    }
}

bool PlayerbotFactory::IsDesiredReplacement(Item* item)
{
    if (!item)
        return true;

    ItemPrototype const* proto = item->GetProto();
    int delta = 1 + (80 - bot->getLevel()) / 10;
    return (int)bot->getLevel() - (int)proto->RequiredLevel > delta;
}

void PlayerbotFactory::InitSecondEquipmentSet()
{
    if (bot->getClass() != CLASS_WARRIOR && bot->getClass() != CLASS_PALADIN && bot->getClass() != CLASS_SHAMAN)
        return;

    map<uint32, vector<uint32> > items;

    uint32 desiredQuality = itemQuality;
    while (urand(0, 100) < 100 * sPlayerbotAIConfig.randomGearLoweringChance && desiredQuality > ITEM_QUALITY_NORMAL) {
        desiredQuality--;
    }

    do
    {
        for (uint32 itemId = 0; itemId < sItemStorage.GetMaxEntry(); ++itemId)
        {
            ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);
            if (!proto)
                continue;

            if (!CanEquipItem(proto, desiredQuality))
                continue;

            if (proto->Class == ITEM_CLASS_WEAPON)
            {
                if (!CanEquipWeapon(proto, EQUIPMENT_SLOT_MAINHAND))
                    continue;

                Item* existingItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                if (existingItem)
                {
                    switch (existingItem->GetProto()->SubClass)
                    {
                    case ITEM_SUBCLASS_WEAPON_AXE:
                    case ITEM_SUBCLASS_WEAPON_DAGGER:
                    case ITEM_SUBCLASS_WEAPON_FIST:
                    case ITEM_SUBCLASS_WEAPON_MACE:
                    case ITEM_SUBCLASS_WEAPON_SWORD:
                        if (proto->SubClass == ITEM_SUBCLASS_WEAPON_AXE || proto->SubClass == ITEM_SUBCLASS_WEAPON_DAGGER ||
                            proto->SubClass == ITEM_SUBCLASS_WEAPON_FIST || proto->SubClass == ITEM_SUBCLASS_WEAPON_MACE ||
                            proto->SubClass == ITEM_SUBCLASS_WEAPON_SWORD)
                            continue;
                        break;
                    default:
                        if (proto->SubClass != ITEM_SUBCLASS_WEAPON_AXE && proto->SubClass != ITEM_SUBCLASS_WEAPON_DAGGER &&
                            proto->SubClass != ITEM_SUBCLASS_WEAPON_FIST && proto->SubClass != ITEM_SUBCLASS_WEAPON_MACE &&
                            proto->SubClass != ITEM_SUBCLASS_WEAPON_SWORD)
                            continue;
                        break;
                    }
                }
            }
            else if (proto->Class == ITEM_CLASS_ARMOR && proto->SubClass == ITEM_SUBCLASS_ARMOR_SHIELD)
            {
                if (!CanEquipArmor(proto, EQUIPMENT_SLOT_OFFHAND))
                    continue;

                Item* existingItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
                if (existingItem && existingItem->GetProto()->SubClass == ITEM_SUBCLASS_ARMOR_SHIELD)
                    continue;
            }
            else
                continue;

            items[proto->Class].push_back(itemId);
        }
    } while (items[ITEM_CLASS_ARMOR].empty() && items[ITEM_CLASS_WEAPON].empty() && desiredQuality-- > ITEM_QUALITY_NORMAL);

    for (map<uint32, vector<uint32> >::iterator i = items.begin(); i != items.end(); ++i)
    {
        vector<uint32>& ids = i->second;
        if (ids.empty())
        {
            sLog.outError("%s: no items to make second equipment set for slot %d", bot->GetName(), i->first);
            continue;
        }

        for (int attempts = 0; attempts < 15; attempts++)
        {
            uint32 index = urand(0, ids.size() - 1);
            uint32 newItemId = ids[index];

            Item* newItem = bot->StoreNewItemInInventorySlot(newItemId, 1);
            if (newItem)
            {
                EnchantItem(newItem);
                newItem->AddToWorld();
                newItem->AddToUpdateQueueOf(bot);
                break;
            }
        }
    }
}

void PlayerbotFactory::InitBags()
{
    vector<uint32> ids;

    for (uint32 itemId = 0; itemId < sItemStorage.GetMaxEntry(); ++itemId)
    {
        ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);
        if (!proto || proto->Class != ITEM_CLASS_CONTAINER)
            continue;

        if (!CanEquipItem(proto, ITEM_QUALITY_NORMAL))
            continue;

        ids.push_back(itemId);
    }

    if (ids.empty())
    {
        sLog.outError("%s: no bags found", bot->GetName());
        return;
    }

    for (uint8 slot = INVENTORY_SLOT_BAG_START; slot < INVENTORY_SLOT_BAG_END; ++slot)
    {
        for (int attempts = 0; attempts < 15; attempts++)
        {
            uint32 index = urand(0, ids.size() - 1);
            uint32 newItemId = ids[index];

            uint16 dest;
            if (!CanEquipUnseenItem(slot, dest, newItemId))
                continue;

            Item* newItem = bot->EquipNewItem(dest, newItemId, true);
            if (newItem)
            {
                newItem->AddToWorld();
                newItem->AddToUpdateQueueOf(bot);
                break;
            }
        }
    }
}

void PlayerbotFactory::EnchantItem(Item* item)
{
    if (urand(0, 100) < 100 * sPlayerbotAIConfig.randomGearLoweringChance)
        return;

    ItemPrototype const* proto = item->GetProto();
    int32 itemLevel = proto->ItemLevel;

    vector<uint32> ids;
    for (int id = 0; id < sSpellStore.GetNumRows(); ++id)
    {
        SpellEntry const *entry = sSpellStore.LookupEntry(id);
        if (!entry)
            continue;

        int32 requiredLevel = (int32)entry->baseLevel;
        if (requiredLevel && (requiredLevel > itemLevel || requiredLevel < itemLevel - 35))
            continue;

        if (entry->maxLevel && level > entry->maxLevel)
            continue;

        uint32 spellLevel = entry->spellLevel;
        if (spellLevel && (spellLevel > level || spellLevel < level - 10))
            continue;

        for (int j = 0; j < 3; ++j)
        {
            if (entry->Effect[j] != SPELL_EFFECT_ENCHANT_ITEM)
                continue;

            uint32 enchant_id = entry->EffectMiscValue[j];
            if (!enchant_id)
                continue;

            SpellItemEnchantmentEntry const* enchant = sSpellItemEnchantmentStore.LookupEntry(enchant_id);
            if (!enchant || enchant->slot != PERM_ENCHANTMENT_SLOT)
                continue;

            uint8 sp = 0, ap = 0, tank = 0;
            for (int i = 0; i < 3; ++i)
            {
                if (enchant->type[i] != ITEM_ENCHANTMENT_TYPE_STAT)
                    continue;

                AddItemStats(enchant->spellid[i], sp, ap, tank);
            }

            if (!CheckItemStats(sp, ap, tank))
                continue;

            if (enchant->EnchantmentCondition && !bot->EnchantmentFitsRequirements(enchant->EnchantmentCondition, -1))
                continue;

            if (!item->IsFitToSpellRequirements(entry))
                continue;

            ids.push_back(enchant_id);
        }
    }

    if (ids.empty())
    {
        sLog.outDetail("%s: no enchantments found for item %d", bot->GetName(), item->GetProto()->ItemId);
        return;
    }

    int index = urand(0, ids.size() - 1);
    uint32 id = ids[index];
    bot->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, false);
    item->SetEnchantment(PERM_ENCHANTMENT_SLOT, id, 0, 0);
    bot->ApplyEnchantment(item, PERM_ENCHANTMENT_SLOT, true);
}

bool PlayerbotFactory::CanEquipUnseenItem(uint8 slot, uint16 &dest, uint32 item)
{
    dest = 0;
    Item *pItem = Item::CreateItem(item, 1, bot);
    if (pItem)
    {
        InventoryResult result = bot->CanEquipItem(slot, dest, pItem, true, false);
        pItem->RemoveFromUpdateQueueOf(bot);
        delete pItem;
        return result == EQUIP_ERR_OK;
    }

    return false;
}


void PlayerbotFactory::InitSkills()
{
    uint32 maxValue = level * 5;
    SetRandomSkill(SKILL_DEFENSE);
    SetRandomSkill(SKILL_SWORDS);
    SetRandomSkill(SKILL_AXES);
    SetRandomSkill(SKILL_BOWS);
    SetRandomSkill(SKILL_GUNS);
    SetRandomSkill(SKILL_MACES);
    SetRandomSkill(SKILL_2H_SWORDS);
    SetRandomSkill(SKILL_STAVES);
    SetRandomSkill(SKILL_2H_MACES);
    SetRandomSkill(SKILL_2H_AXES);
    SetRandomSkill(SKILL_DAGGERS);
    SetRandomSkill(SKILL_THROWN);
    SetRandomSkill(SKILL_CROSSBOWS);
    SetRandomSkill(SKILL_WANDS);
    SetRandomSkill(SKILL_POLEARMS);
    SetRandomSkill(SKILL_FIST_WEAPONS);

    if (bot->getLevel() >= 70)
        bot->SetSkill(SKILL_RIDING, 300, 300);
    else if (bot->getLevel() >= 60)
        bot->SetSkill(SKILL_RIDING, 225, 225);
    else if (bot->getLevel() >= 40)
        bot->SetSkill(SKILL_RIDING, 150, 150);
    else if (bot->getLevel() >= 20)
        bot->SetSkill(SKILL_RIDING, 75, 75);
    else
        bot->SetSkill(SKILL_RIDING, 0, 0);

    uint32 skillLevel = bot->getLevel() < 40 ? 0 : 1;
    switch (bot->getClass())
    {
    case CLASS_DEATH_KNIGHT:
    case CLASS_WARRIOR:
    case CLASS_PALADIN:
        bot->SetSkill(SKILL_PLATE_MAIL, skillLevel, skillLevel);
        break;
    case CLASS_SHAMAN:
    case CLASS_HUNTER:
        bot->SetSkill(SKILL_MAIL, skillLevel, skillLevel);
    }
}

void PlayerbotFactory::SetRandomSkill(uint16 id)
{
    uint32 maxValue = level * 5;
    uint32 curValue = urand(maxValue - level, maxValue);
    bot->SetSkill(id, curValue, maxValue);

}

void PlayerbotFactory::InitAvailableSpells()
{
    bot->learnDefaultSpells();

    for (uint32 id = 0; id < sCreatureStorage.GetMaxEntry(); ++id)
    {
        CreatureInfo const* co = sCreatureStorage.LookupEntry<CreatureInfo>(id);
        if (!co ||co->trainer_type != TRAINER_TYPE_CLASS || co->trainer_class != bot->getClass())
            continue;

        uint32 trainerId = co->trainerId;
        if (!trainerId)
            trainerId = co->Entry;

		TrainerSpellData const* trainer_spells = sObjectMgr.GetNpcTrainerTemplateSpells(trainerId);
        if (!trainer_spells)
            trainer_spells = sObjectMgr.GetNpcTrainerSpells(trainerId);

        if (!trainer_spells)
            continue;

        for (TrainerSpellMap::const_iterator itr =  trainer_spells->spellList.begin(); itr !=  trainer_spells->spellList.end(); ++itr)
        {
            TrainerSpell const* tSpell = &itr->second;

            if (!tSpell)
                continue;

            uint32 reqLevel = 0;
            if (!tSpell->learnedSpell && !bot->IsSpellFitByClassAndRace(tSpell->learnedSpell, &reqLevel))
                continue;

            reqLevel = tSpell->isProvidedReqLevel ? tSpell->reqLevel : std::max(reqLevel, tSpell->reqLevel);
            TrainerSpellState state = bot->GetTrainerSpellState(tSpell, reqLevel);
            if (state != TRAINER_SPELL_GREEN)
                continue;

            if (tSpell->learnedSpell)
                bot->learnSpell(tSpell->learnedSpell, false);
            else
                ai->CastSpell(tSpell->spell, bot);
        }
    }
}

void PlayerbotFactory::InitSpecialSpells()
{
    for (list<uint32>::iterator i = sPlayerbotAIConfig.randomBotSpellIds.begin(); i != sPlayerbotAIConfig.randomBotSpellIds.end(); ++i)
    {
        uint32 spellId = *i;
        bot->learnSpell(spellId, false);
    }
}

void PlayerbotFactory::InitTalents(uint32 specNo)
{
    uint32 classMask = bot->getClassMask();

    map<uint32, vector<TalentEntry const*> > spells;
    for (uint32 i = 0; i < sTalentStore.GetNumRows(); ++i)
    {
        TalentEntry const *talentInfo = sTalentStore.LookupEntry(i);
        if(!talentInfo)
            continue;

        TalentTabEntry const *talentTabInfo = sTalentTabStore.LookupEntry( talentInfo->TalentTab );
        if(!talentTabInfo || talentTabInfo->tabpage != specNo)
            continue;

        if( (classMask & talentTabInfo->ClassMask) == 0 )
            continue;

        spells[talentInfo->Row].push_back(talentInfo);
    }

    uint32 freePoints = bot->GetFreeTalentPoints();
    for (map<uint32, vector<TalentEntry const*> >::iterator i = spells.begin(); i != spells.end(); ++i)
    {
        vector<TalentEntry const*> &spells = i->second;
        if (spells.empty())
        {
            sLog.outError("%s: No spells for talent row %d", bot->GetName(), i->first);
            continue;
        }

        int attemptCount = 0;
        while (!spells.empty() && (int)freePoints - (int)bot->GetFreeTalentPoints() < 5 && attemptCount++ < 3 && bot->GetFreeTalentPoints())
        {
            int index = urand(0, spells.size() - 1);
            TalentEntry const *talentInfo = spells[index];
            for (int rank = 0; rank < MAX_TALENT_RANK && bot->GetFreeTalentPoints(); ++rank)
            {
                uint32 spellId = talentInfo->RankID[rank];
                if (!spellId)
                    continue;
                bot->learnSpell(spellId, false);
                bot->UpdateFreeTalentPoints(false);
            }
			spells.erase(spells.begin() + index);
        }

        freePoints = bot->GetFreeTalentPoints();
    }

    for (uint32 i = 0; i < MAX_TALENT_SPEC_COUNT; ++i)
    {
        for (PlayerTalentMap::iterator itr = bot->GetTalentMap(i).begin(); itr != bot->GetTalentMap(i).end(); ++itr)
        {
            if (itr->second.state != PLAYERSPELL_REMOVED)
                itr->second.state = PLAYERSPELL_CHANGED;
        }
    }
}

ObjectGuid PlayerbotFactory::GetRandomBot()
{
    vector<ObjectGuid> guids;
    for (list<uint32>::iterator i = sPlayerbotAIConfig.randomBotAccounts.begin(); i != sPlayerbotAIConfig.randomBotAccounts.end(); i++)
    {
        uint32 accountId = *i;
        if (!sAccountMgr.GetCharactersCount(accountId))
            continue;

        QueryResult *result = CharacterDatabase.PQuery("SELECT guid FROM characters WHERE account = '%u'", accountId);
        if (!result)
            continue;

        do
        {
            Field* fields = result->Fetch();
            ObjectGuid guid = ObjectGuid(fields[0].GetUInt64());
            if (!sObjectMgr.GetPlayer(guid))
                guids.push_back(guid);
        } while (result->NextRow());

        delete result;
    }

    if (guids.empty())
        return ObjectGuid();

    int index = urand(0, guids.size() - 1);
    return guids[index];
}

void PlayerbotFactory::InitQuests()
{
    QueryResult *results = WorldDatabase.PQuery("SELECT entry, RequiredClasses, RequiredRaces FROM quest_template where QuestLevel = -1 and MinLevel <= '%u'",
            bot->getLevel());
    if (!results)
        return;

    list<uint32> ids;
    do
    {
        Field* fields = results->Fetch();
        uint32 questId = fields[0].GetUInt32();
        uint32 requiredClasses = fields[1].GetUInt32();
        uint32 requiredRaces = fields[2].GetUInt32();
        if ((requiredClasses & bot->getClassMask()) && (requiredRaces & bot->getRaceMask()))
            ids.push_back(questId);
    } while (results->NextRow());

    delete results;

    for (int i = 0; i < 15; i++)
    {
        for (list<uint32>::iterator i = ids.begin(); i != ids.end(); ++i)
        {
			uint32 questId = *i;
            Quest const *quest = sObjectMgr.GetQuestTemplate(questId);

            bot->SetQuestStatus(questId, QUEST_STATUS_NONE);

            if (!bot->SatisfyQuestClass(quest, false) ||
                    !bot->SatisfyQuestRace(quest, false) ||
                    !bot->SatisfyQuestStatus(quest, false))
                continue;

            if (quest->IsDailyOrWeekly() || quest->IsRepeatable() || quest->IsMonthly())
                continue;

            bot->SetQuestStatus(questId, QUEST_STATUS_COMPLETE);
            bot->RewardQuest(quest, 0, bot, false);
            ClearInventory();
        }
    }
}

void PlayerbotFactory::ClearInventory()
{
    DestroyItemsVisitor visitor(bot);
    IterateItems(&visitor);
}

void PlayerbotFactory::InitAmmo()
{
    if (bot->getClass() != CLASS_HUNTER && bot->getClass() != CLASS_ROGUE && bot->getClass() != CLASS_WARRIOR)
        return;

    Item* const pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);
    if (!pItem)
        return;

    uint32 subClass = 0;
    switch (pItem->GetProto()->SubClass)
    {
    case ITEM_SUBCLASS_WEAPON_GUN:
        subClass = ITEM_SUBCLASS_BULLET;
        break;
    case ITEM_SUBCLASS_WEAPON_BOW:
    case ITEM_SUBCLASS_WEAPON_CROSSBOW:
        subClass = ITEM_SUBCLASS_ARROW;
        break;
    }

    if (!subClass)
        return;

    QueryResult *results = WorldDatabase.PQuery("select max(entry), max(RequiredLevel) from item_template where class = '%u' and subclass = '%u' and RequiredLevel <= '%u'",
            ITEM_CLASS_PROJECTILE, subClass, bot->getLevel());
    if (!results)
        return;

    Field* fields = results->Fetch();
    if (fields)
    {
        uint32 entry = fields[0].GetUInt32();
        for (int i = 0; i < 5; i++)
        {
            Item* newItem = bot->StoreNewItemInInventorySlot(entry, 1000);
            if (newItem)
                newItem->AddToUpdateQueueOf(bot);
        }
        bot->SetAmmo(entry);
    }

    delete results;
}

void PlayerbotFactory::InitMounts()
{
    map<uint32, map<int32, vector<uint32> > > allSpells;

    for (uint32 spellId = 0; spellId < sSpellStore.GetNumRows(); ++spellId)
    {
        SpellEntry const *spellInfo = sSpellStore.LookupEntry(spellId);
        if (!spellInfo || spellInfo->EffectApplyAuraName[0] != SPELL_AURA_MOUNTED)
            continue;

        if (GetSpellCastTime(spellInfo) < 500 || GetSpellDuration(spellInfo) != -1)
            continue;

        int32 effect = max(spellInfo->EffectBasePoints[1], spellInfo->EffectBasePoints[2]);
        if (effect < 50)
            continue;

        uint32 index = (spellInfo->EffectApplyAuraName[1] == SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED ||
                spellInfo->EffectApplyAuraName[2] == SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED) ? 1 : 0;
        allSpells[index][effect].push_back(spellId);
    }

    for (uint32 type = 0; type < 2; ++type)
    {
        map<int32, vector<uint32> >& spells = allSpells[type];
        for (map<int32, vector<uint32> >::iterator i = spells.begin(); i != spells.end(); ++i)
        {
            int32 effect = i->first;
            vector<uint32>& ids = i->second;
            uint32 index = urand(0, ids.size() - 1);
            if (index >= ids.size())
                continue;

            bot->learnSpell(ids[index], false);
        }
    }
}

void PlayerbotFactory::InitPotions()
{
    map<uint32, vector<uint32> > items;
    for (uint32 itemId = 0; itemId < sItemStorage.GetMaxEntry(); ++itemId)
    {
        ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);
        if (!proto)
            continue;

        if (proto->Class != ITEM_CLASS_CONSUMABLE ||
            proto->SubClass != ITEM_SUBCLASS_POTION ||
            proto->Spells[0].SpellCategory != 4 ||
            proto->Bonding != NO_BIND)
            continue;

        if (proto->RequiredLevel > bot->getLevel() || proto->RequiredLevel < bot->getLevel() - 10)
            continue;

        if (proto->RequiredSkill && !bot->HasSkill(proto->RequiredSkill))
            continue;

        if (proto->Area || proto->Map || proto->RequiredCityRank || proto->RequiredHonorRank)
            continue;

        for (int j = 0; j < MAX_ITEM_PROTO_SPELLS; j++)
        {
            const SpellEntry* const spellInfo = sSpellStore.LookupEntry(proto->Spells[j].SpellId);
            if (!spellInfo)
                continue;

            for (int i = 0 ; i < 3; i++)
            {
                if (spellInfo->Effect[i] == SPELL_EFFECT_HEAL || spellInfo->Effect[i] == SPELL_EFFECT_ENERGIZE)
                {
                    items[spellInfo->Effect[i]].push_back(itemId);
                    break;
                }
            }
        }
    }

    uint32 effects[] = { SPELL_EFFECT_HEAL, SPELL_EFFECT_ENERGIZE };
    for (int i = 0; i < sizeof(effects) / sizeof(uint32); ++i)
    {
        uint32 effect = effects[i];
        vector<uint32>& ids = items[effect];
        uint32 index = urand(0, ids.size() - 1);
        if (index >= ids.size())
            continue;

        uint32 itemId = ids[index];
        ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);
        Item* newItem = bot->StoreNewItemInInventorySlot(itemId, urand(1, proto->GetMaxStackSize()));
        if (newItem)
            newItem->AddToUpdateQueueOf(bot);
   }
}


void PlayerbotFactory::CancelAuras()
{
    bot->RemoveAllAuras();
}

void PlayerbotFactory::InitInventory()
{
    vector<uint32> ids;
    for (uint32 itemId = 0; itemId < sItemStorage.GetMaxEntry(); ++itemId)
    {
        ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);
        if (!proto)
            continue;

        if (proto->Class != ITEM_CLASS_TRADE_GOODS || proto->Bonding != NO_BIND)
            continue;

        if (bot->getLevel() >= 40 && proto->Quality < ITEM_QUALITY_RARE)
            continue;

        if (bot->getLevel() >= 20 && proto->Quality < ITEM_QUALITY_UNCOMMON)
            continue;

        if (proto->RequiredLevel > bot->getLevel() || proto->RequiredLevel < bot->getLevel() - 10)
            continue;

        if (proto->RequiredSkill && !bot->HasSkill(proto->RequiredSkill))
            continue;

        ids.push_back(itemId);
    }

    int maxCount = urand(0, 3);
    int count = 0;
    for (int attempts = 0; attempts < 15; attempts++)
    {
        uint32 index = urand(0, ids.size() - 1);
        if (index >= ids.size())
            continue;

        uint32 itemId = ids[index];
        ItemPrototype const* proto = sObjectMgr.GetItemPrototype(itemId);
        Item* newItem = bot->StoreNewItemInInventorySlot(itemId, urand(1, proto->GetMaxStackSize()));
        if (newItem)
        {
            newItem->AddToUpdateQueueOf(bot);
            if (count++ >= maxCount)
                break;
        }
   }
}
