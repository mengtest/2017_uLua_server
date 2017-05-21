#include "stdafx.h"
#include "logic_room.h"
#include "Landlord_RoomCFG.h"
#include "logic_player.h"
#include "game_db.h"
#include "game_engine.h"
#include "i_game_ehandler.h"
#include <enable_random.h>
#include "game_db_log.h"
#include "msg_type_def.pb.h"
#include <math.h>

using namespace std;

static const int BANKER_MAX_COUNT = 10;	//申请上庄列表最大数量
static const int SYNC_BET_TIME = 1;		//几秒同步一次押注

logic_room::logic_room(const Landlord_RoomCFGData* cfg, logic_lobby* _lobby)
{
	m_cfg = cfg;
	m_lobby = _lobby;

	logic_room_db::init_game_object();
	m_db_room_id->set_value(m_cfg->mRoomID);
	if(!load_room())
	{
		create_room();
	}
}

logic_room::~logic_room(void)
{
	
}

void logic_room::heartbeat(double elapsed)
{

	
}

uint16_t logic_room::get_room_id()
{
	return m_cfg->mRoomID;
}

uint16_t logic_room::enter_room(LPlayerPtr player)
{
	if (playerMap.find(player->get_pid()) != playerMap.end())
		return msg_type_def::e_rmt_fail;

	if (playerMap.size() >= 10000)		//房间已满
		return msg_type_def::e_rmt_room_full;

	if (!player->enter_room(this))
		return msg_type_def::e_rmt_fail;
	
	playerMap.insert(std::make_pair(player->get_pid(), player));

	return msg_type_def::e_rmt_success;
}

void logic_room::leave_room(uint32_t playerid)
{
	auto it = playerMap.find(playerid);
	if(it == playerMap.end())
	{
		return;
	}

	playerMap.erase(it);
}

const Landlord_RoomCFGData* logic_room::get_room_cfg() const
{
	return m_cfg;
}






