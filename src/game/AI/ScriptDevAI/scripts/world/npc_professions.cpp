#include "AI/ScriptDevAI/include/precompiled.h"

enum Texts
{
	NPC_TEXT_LEVELUP_ALREADY_DONE = 19997,
	NPC_TEXT_LEVELUP_OK = 19998,
	NPC_TEXT_LEVELUP_RULES = 19999,
	NPC_TEXT_TELEPORT_GOSSIP = 20000,
	NPC_TEXT_LEVELUP_SUB = 20001,
	NPC_TEXT_LEVELUP_MAX_PROF = 20002,
};

enum Levels
{
	NPC_PROFESSIONS_LEVEL_255 = 255
};

// helpers
void LearnAllRecipes(Player* player, uint32 skillEntry)
{
	SkillLineEntry const* skillInfo = sSkillLineStore.LookupEntry(skillEntry);
	if (!skillInfo)
		return;

	uint32 classmask = player->getClassMask();

	for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
	{
		SkillLineAbilityEntry const* skillLine = sSkillLineAbilityStore.LookupEntry(j);
		if (!skillLine)
			continue;

		// wrong skill
		if (skillLine->skillId != skillEntry)
			continue;

		// not high rank
		if (skillLine->forward_spellid)
			continue;

		// skip racial skills
		if (skillLine->racemask != 0)
			continue;

		// skip wrong class skills
		if (skillLine->classmask && (skillLine->classmask & classmask) == 0)
			continue;

		SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(skillLine->spellId);
		if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, player, false))
			continue;

		player->learnSpell(skillLine->spellId, false);
	}

	uint16 maxLevel = player->GetPureMaxSkillValue(skillInfo->id);
	player->SetSkill(skillInfo->id, maxLevel, maxLevel);
}

/*######
## npc_welcome
######*/

bool GossipHello_npc_professions(Player *player, Creature *_Creature)
{
	// max level reached - offer professions
	if (player->getLevel() >= NPC_PROFESSIONS_LEVEL_255)
	{
		if (player->GetFreePrimaryProfessionPoints())
		{
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Alchemy", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 20);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Blacksmithing", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 21);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Enchanting", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 22);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Engineering", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 23);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Jewelcrafting", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 24);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Leatherworking", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 25);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Tailroing", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 26);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Herbalism", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 27);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Mining", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 28);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Skinning", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 29);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "First Aid", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 30);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Cooking", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 31);
			player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Fishing", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 32);
			player->SEND_GOSSIP_MENU(NPC_TEXT_LEVELUP_ALREADY_DONE, _Creature->GetObjectGuid());
			return true;
		}

		player->SEND_GOSSIP_MENU(NPC_TEXT_LEVELUP_MAX_PROF, _Creature->GetObjectGuid());
		return true;
	}

	player->SEND_GOSSIP_MENU(NPC_TEXT_LEVELUP_RULES, _Creature->GetObjectGuid());
	return true;
}

bool GossipSelect_npc_professions(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
	if (sender != GOSSIP_SENDER_MAIN)
		return false;

	switch (action)
	{
		// professions
	case GOSSIP_ACTION_INFO_DEF + 20: // Alchemy
		LearnAllRecipes(player, SKILL_ALCHEMY);
		break;
	case GOSSIP_ACTION_INFO_DEF + 21: // Blacksmithing
		LearnAllRecipes(player, SKILL_BLACKSMITHING);
		break;
	case GOSSIP_ACTION_INFO_DEF + 22: // Enchanting
		LearnAllRecipes(player, SKILL_ENCHANTING);
		break;
	case GOSSIP_ACTION_INFO_DEF + 23: // Engineering
		LearnAllRecipes(player, SKILL_ENGINEERING);
		break;
	case GOSSIP_ACTION_INFO_DEF + 24: // Jewelcrafting
		LearnAllRecipes(player, SKILL_JEWELCRAFTING);
		break;
	case GOSSIP_ACTION_INFO_DEF + 25: // Leatherworking
		LearnAllRecipes(player, SKILL_LEATHERWORKING);
		break;
	case GOSSIP_ACTION_INFO_DEF + 26: // Tailoring
		LearnAllRecipes(player, SKILL_TAILORING);
		break;
	case GOSSIP_ACTION_INFO_DEF + 27: // Herbalism
		LearnAllRecipes(player, SKILL_HERBALISM);
		break;
	case GOSSIP_ACTION_INFO_DEF + 28: // Mining
		LearnAllRecipes(player, SKILL_MINING);
		break;
	case GOSSIP_ACTION_INFO_DEF + 29: // Skinning
		LearnAllRecipes(player, SKILL_SKINNING);
		break;
	case GOSSIP_ACTION_INFO_DEF + 30: // First Aid
		LearnAllRecipes(player, SKILL_FIRST_AID);
		break;
	case GOSSIP_ACTION_INFO_DEF + 31: // Cooking
		LearnAllRecipes(player, SKILL_COOKING);
		break;
	case GOSSIP_ACTION_INFO_DEF + 32: // Fishing
		LearnAllRecipes(player, SKILL_FISHING);
		break;
	}

	player->CLOSE_GOSSIP_MENU();
	return true;
}

void AddSC_npc_professions()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_professions";
    pNewScript->pGossipHello =  &GossipHello_npc_professions;
    pNewScript->pGossipSelect = &GossipSelect_npc_professions;
    pNewScript->RegisterSelf();
}
