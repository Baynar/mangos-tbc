/* This file is part of the ScriptDev2 Project. See AUTHORS file for Copyright information
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
SDName: Example_Creature
SD%Complete: 100
SDComment: Short custom scripting example
SDCategory: Script Examples
EndScriptData */

#include "AI/ScriptDevAI/include/precompiled.h"

// **** This script is designed as an example for others to build on ****
// **** Please modify whatever you'd like to as this script is only for developement ****

// **** Script Info ****
// This script is written in a way that it can be used for both friendly and hostile monsters
// Its primary purpose is to show just how much you can really do with scripts
// I recommend trying it out on both an agressive NPC and on friendly npc

// **** Quick Info ****
// Functions with Handled Function marked above them are functions that are called automatically by the core
// Functions that are marked Custom Function are functions I've created to simplify code

enum
{
    // List of text id's. The text is stored in database, also in a localized version
    // (if translation not exist for the textId, default english text will be used)
    SAY_AGGRO       = -1999900,
    SAY_RANDOM_0    = -1999901,
    SAY_RANDOM_1    = -1999902,
    SAY_RANDOM_2    = -1999903,
    SAY_RANDOM_3    = -1999904,
    SAY_RANDOM_4    = -1999905,
    SAY_BESERK      = -1999906,
    SAY_PHASE       = -1999907,
    SAY_DANCE       = -1999908,
    SAY_SALUTE      = -1999909,

    // List of used spells
    SPELL_BUFF      = 25661,
    SPELL_ONE       = 12555,
    SPELL_ONE_ALT   = 24099,
    SPELL_TWO       = 10017,
    SPELL_THREE     = 26027,
    SPELL_ENRAGE    = 23537,
    SPELL_BESERK    = 32309,

    // Some other information we need to store
    TEXT_ID_GREET   = 907,
    FACTION_WORGEN  = 24
};

// List of gossip item texts. Items will appear in the gossip window.
// Actually such gossip can already be handled in normal World-Database
// If (and only if) a gossip must be handled within SD2, then it should be moved to SD2-database!
#define GOSSIP_COMBAT "You are in combat!"
#define GOSSIP_CLOSE "Have a nice day in Xtreme WoW Reborn!"
#define GOSSIP_HEAL     "Heal me!"
#define GOSSIP_BUFF     "Buff me!"
#define GOSSIP_BYE     "I will come back later."

#define GOSSIP_SENDER_HEAL         14254524
#define GOSSIP_SENDER_BUFF       345345345
#define GOSSIP_SENDER_CLOSE        452452452

// This function is called when the player opens the gossip menu
// In this case as there is nothing special about this gossip dialogue, it should be moved to world-DB
bool GossipHello_npc_healbuff(Player* pPlayer, Creature* pCreature)
{
	if (pPlayer->isInCombat()) { 
		pCreature->MonsterWhisper(GOSSIP_COMBAT, pPlayer);
		pPlayer->CLOSE_GOSSIP_MENU();
		return true;
	}

    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_HEAL, GOSSIP_SENDER_HEAL, GOSSIP_ACTION_INFO_DEF + 5555555);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BUFF, GOSSIP_SENDER_BUFF, GOSSIP_ACTION_INFO_DEF + 5555556);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BYE, GOSSIP_SENDER_CLOSE, GOSSIP_ACTION_INFO_DEF + 5555557);

	pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

void SendActionMenu_npc_heal(Player* pPlayer, Creature* pCreature, uint32 uiAction) {
	pCreature->CastSpell(pPlayer, 25840, TRIGGERED_NORMAL_COMBAT_CAST);
	pPlayer->CLOSE_GOSSIP_MENU();
}

void SendActionMenu_npc_buff(Player* pPlayer, Creature* pCreature, uint32 uiAction) {
	pCreature->CastSpell(pPlayer, 26990, TRIGGERED_OLD_TRIGGERED);
	pCreature->CastSpell(pPlayer, 467, TRIGGERED_OLD_TRIGGERED);
	pCreature->CastSpell(pPlayer, 25898, TRIGGERED_OLD_TRIGGERED);
	pCreature->CastSpell(pPlayer, 33944, TRIGGERED_OLD_TRIGGERED);
	pCreature->CastSpell(pPlayer, 25389, TRIGGERED_OLD_TRIGGERED);
	pCreature->CastSpell(pPlayer, 25433, TRIGGERED_OLD_TRIGGERED);
	pCreature->CastSpell(pPlayer, 25312, TRIGGERED_OLD_TRIGGERED);
	pCreature->CastSpell(pPlayer, 27126, TRIGGERED_OLD_TRIGGERED);
	pPlayer->CLOSE_GOSSIP_MENU();
}

void SendActionMenu_npc_close(Player* pPlayer, Creature* pCreature, uint32 uiAction) {
	pCreature->MonsterWhisper(GOSSIP_CLOSE, pPlayer);
	pPlayer->CLOSE_GOSSIP_MENU();
}

// This function is called when the player clicks an option on the gossip menu
// In this case here the faction change could be handled by world-DB gossip, hence it should be handled there!
bool GossipSelect_npc_healbuff(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
	switch (uiSender)
	{
		case GOSSIP_SENDER_HEAL:	SendActionMenu_npc_heal(pPlayer, pCreature, uiAction); break;
		case GOSSIP_SENDER_BUFF:	SendActionMenu_npc_buff(pPlayer, pCreature, uiAction); break;
		case GOSSIP_SENDER_CLOSE:   SendActionMenu_npc_close(pPlayer, pCreature, uiAction); break;
	}
	return true;
}

// This is the actual function called only once durring InitScripts()
// It must define all handled functions that are to be run in this script
void AddSC_npc_healbuff()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_healbuff";
    pNewScript->pGossipHello = &GossipHello_npc_healbuff;
    pNewScript->pGossipSelect = &GossipSelect_npc_healbuff;
    pNewScript->RegisterSelf(true);
}
