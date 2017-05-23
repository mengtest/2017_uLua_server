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

logic_table::logic_table(logic_room* room, int tableId):current_deskId(1)
{
	deskCount = 3;
	m_room = room;
	gameState = e_game_state::e_game_state_none;
	m_tableId = tableId;
	logic_table_db::init_game_object();
	logic_table_db::m_db_table_id->set_value(m_tableId);
	if (!load_table())
	{
		create_table();
	}
	m_cardManager=new logic_core(deskCount);
}

logic_table::~logic_table(void)
{
	if (m_cardManager != nullptr)
	{
		delete m_cardManager;
		m_cardManager = nullptr;
	}
}

void logic_table::heartbeat(double elapsed)
{
	if (gameState == e_game_state::e_game_state_none)
	{
		return;
	}

	if (gameState == e_game_state::e_game_state_matching)//匹配
	{
		if (playerMap.size() >= deskCount)
		{
			gameState = e_game_state::e_game_state_startgame;
		}	
	}
	else if (gameState == e_game_state::e_game_state_startgame)//开始游戏，发完所有牌
	{
		do_protobuf_notice_start_game();

	}
	else if (gameState == e_game_state::e_game_state_robLandlore)//叫地主
	{
		
	}
	else if (gameState == e_game_state::e_game_state_playhand)//玩家出牌
	{

	}
	else if (gameState == e_game_state::e_game_state_award)//开奖
	{

	}
}

uint16_t logic_table::get_table_id()
{
	return m_tableId;
}

e_server_error_code logic_table::enter_table(LPlayerPtr player)
{
	if (playerMap.size() >= 3)
	{
		return e_error_code_failed;
	}
	auto it = playerMap.find(player->get_pid());
	if (it != playerMap.end())
	{
		return e_error_code_success;
	}

	playerMap.insert(make_pair(player->get_pid(),player));
	player->set_deskId(current_deskId);
	current_deskId++;
	return e_error_code_success;
}

e_server_error_code logic_table::leave_table(uint32_t playerId)
{
	auto it = playerMap.find(playerId);
	if (it == playerMap.end())
	{
		return e_error_code_success;
	}
	m_room->leave_room(playerId);
	playerMap.erase(it);

	return e_error_code_success;
}

TableState logic_table::get_table_state()
{
	return TableState_None;
}

void logic_table::do_protobuf_notice_start_game()
{
	auto sendmsg = PACKET_CREATE(packetl2c_notice_start_game, e_mst_l2c_enter_room);

	broadcast_msg_to_client(sendmsg);
	
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







