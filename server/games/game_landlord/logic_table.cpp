#include "stdafx.h"
#include "logic_table.h"
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

logic_table::logic_table(int tableId)
{
	m_tableId = tableId;
	logic_table_db::init_game_object();
	logic_table_db::m_db_table_id->set_value(tableId);
	if (!load_table())
	{
		create_table();
	}
}

logic_table::~logic_table(void)
{

}

void logic_table::heartbeat(double elapsed)
{


}

uint16_t logic_table::get_table_id()
{
	return m_tableId;
}

uint16_t logic_table::enter_table(LPlayerPtr player)
{
	/*if (playerMap.find(player->get_pid()) != playerMap.end())
		return msg_type_def::e_rmt_fail;

	if (playerMap.size() >= 10000)		//房间已满
		return msg_type_def::e_rmt_room_full;

	if (!player->enter_room(this))
		return msg_type_def::e_rmt_fail;

	playerMap.insert(std::make_pair(player->get_pid(), player));*/

	return msg_type_def::e_rmt_success;
}

void logic_table::leave_table(uint32_t playerid)
{
	auto it = playerMap.find(playerid);
	if (it == playerMap.end())
	{
		return;
	}

	playerMap.erase(it);
}

void logic_table_db::create_table()
{

}

//房间数据是要保存到数据库的
bool logic_table_db::load_table()
{
	mongo::BSONObj b = db_game::instance().findone(DB_LANDLORD_TABLE, BSON("table_id" << m_db_table_id->get_value()));
	//如果刚开始数据里没有这个数据
	if (b.isEmpty())
		return false;
	return from_bson(b);
}

void logic_table_db::init_game_object()
{
	m_db_table_id = CONVERT_POINT(Tfield<int16_t>, regedit_tfield(e_got_int16, "table_id"));
}

bool logic_table_db::store_game_object(bool to_all)
{
	if (!has_update())
		return true;

	auto err = db_game::instance().update(DB_LANDLORD_ROOM, BSON("room_id" << m_db_table_id->get_value()), BSON("$set" << to_bson(to_all)));
	if (!err.empty())
	{
		SLOG_ERROR << "logic_room::store_game_object :" << err;
		return false;
	}

	return true;
}







