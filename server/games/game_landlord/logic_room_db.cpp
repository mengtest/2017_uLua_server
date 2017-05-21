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

void logic_room_db::create_room()
{
	
}

//房间数据是要保存到数据库的
bool logic_room_db::load_room()
{
	mongo::BSONObj b = db_game::instance().findone(DB_LANDLORD_ROOM, BSON("room_id"<<m_db_room_id->get_value()));
	//如果刚开始数据里没有这个数据
	if(b.isEmpty())
		return false;	
	return from_bson(b);
}

void logic_room_db::init_game_object()
{
	m_db_room_id = CONVERT_POINT(Tfield<int16_t>, regedit_tfield(e_got_int16, "room_id"));
}

bool logic_room_db::store_game_object(bool to_all)
{
	if(!has_update())
		return true;

	auto err = db_game::instance().update(DB_LANDLORD_ROOM, BSON("room_id"<<m_db_room_id->get_value()), BSON("$set"<<to_bson(to_all)));
	if(!err.empty())
	{
		SLOG_ERROR << "logic_room::store_game_object :" <<err;
		return false;
	}

	return true;
}

