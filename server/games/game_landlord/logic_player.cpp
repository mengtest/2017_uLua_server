#include "stdafx.h"
#include "logic_player.h"
#include "logic_room.h"
#include "logic_lobby.h"
#include <i_game_player.h>
#include <net\packet_manager.h>
#include "game_db.h"
#include "game_engine.h"
#include "game_db_log.h"
#include <enable_random.h>
#include <time_helper.h>
#include "Landlord_RoomCFG.h"

logic_player::logic_player(void)
	:m_lobby(nullptr)
	, m_room(nullptr)
	, m_table(nullptr)
	, m_logic_gold(0)
	, m_change_gold(0)
	, m_checksave(0.0)
	, is_first_save(true)
	,deskId(0)
	,player_state(e_player_game_state::e_player_game_state_none)
{
	logic_player_db::init_game_object();
}


logic_player::~logic_player(void)
{


}

//------------------------i_game_phandler-----------------------------------------
void logic_player::on_attribute_change(int atype, int v)
{
	if(atype == msg_type_def::e_itd_gold)
	{
		std::cout<<"玩家金币改变00："<<v<<std::endl;
		m_logic_gold += v;
	}
}

void logic_player::on_change_state()	//通知游戏状态改变，是否断线
{
	
}

void logic_player::on_attribute64_change(int atype, GOLD_TYPE v)
{
	std::cout<<"atype:"<<atype<<"  玩家金币改变11："<<v<<std::endl;
	m_logic_gold += v;
}
//-----------------------------------------------------------------


void logic_player::heartbeat( double elapsed )
{
	m_checksave += elapsed;
	if (m_checksave > 30)
	{
		if (is_first_save)
		{
			logic_player_db::store_game_object(true);
			is_first_save = false;
		}
		else
		{
			logic_player_db::store_game_object();
		}
		m_checksave = 0.0;
	}

	if (m_room == nullptr)
		return;

	if (is_robot())//机器人AI
	{
		if (m_room == nullptr)
		{

		}

		if (m_table == nullptr)
		{

		}
	}
}

uint32_t logic_player::get_pid()
{
	return m_player->get_playerid();
}

uint16_t logic_player::get_viplvl()
{
	return m_player->get_attribute(msg_type_def::e_itd_vip);
}

GOLD_TYPE logic_player::get_gold()
{
	return m_logic_gold;
}

bool logic_player::change_gold(GOLD_TYPE v)
{
	if(m_logic_gold>=-v)
	{
		m_logic_gold += v;
		m_change_gold += v;
		return true;
	}
	return false;
}

void logic_player::sycn_gold()
{
	if (m_change_gold != 0)
	{
		m_player->change_gold(m_change_gold);
		m_change_gold = 0;
	}
}

bool logic_player::is_robot()
{
	return m_player->is_robot();
}

bool logic_player::change_gold2(int v, int season)
{
	bool ret = m_player->change_gold(v);
	if (ret)
	{
		m_logic_gold += v;
	}
	return ret;
}

bool logic_player::change_ticket(int count,int reason)
{
	m_player->change_ticket(count);
	if (reason != -1)
	{
		
	}
	return true;
}

int logic_player::get_ticket()
{
	return m_player->get_attribute(msg_type_def::e_itd_ticket);
}


const std::string& logic_player::get_nickname()
{
	return m_player->get_nickname();
}

const std::string& logic_player::get_icon_custom()
{
	return m_player->get_icon_custom();
}

const uint32_t logic_player::get_head_frame_id()
{
	return m_player->get_attribute(msg_type_def::e_itd_photoframe);
}

const int16_t logic_player::get_player_sex()
{
	return m_player->get_attribute(msg_type_def::e_itd_sex);
}

void logic_player::onAcceptGift(int receiverId, int giftId)
{
	if (m_room != nullptr)
	{
		//m_table->bc_accept_gift(receiverId,giftId);
	}
}

void logic_player::quest_change(int quest_type, int count, int param)
{
	if (is_robot())
		return;

	m_player->quest_change(quest_type, count, param);
}

void logic_player::release()
{
	leave_table();
	m_player.reset();
}

e_player_state logic_player::get_game_state()
{
	return m_player->get_state();
}

void logic_player::enter_game(logic_lobby* lobby)
{
	m_lobby = lobby;
	m_player_id->set_value(get_pid());
	logic_player_db::load_player();

	m_logic_gold = m_player->get_attribute64(msg_type_def::e_itd_gold);
}

bool logic_player::enter_room(logic_room* room)
{
	if (m_room != nullptr || room == nullptr)
		return false;

	m_room = room;
	m_logic_gold = m_player->get_attribute64(msg_type_def::e_itd_gold);

	return true;
}

bool logic_player::leave_room()
{
	if (m_table != nullptr)
	{
		m_table->leave_table(this->get_pid());
		m_table = nullptr;
		deskId = 0;
	}

	if (m_room != nullptr)
	{
		m_room->leave_room(getpid());
		m_room = nullptr;
	}
	return true;
}


bool logic_player::enter_table()
{
	if (m_table != nullptr)
	{
		return false;
	}

	LPlayerPtr player(this);
	m_room->enter_table(player);

	return true;
}

bool logic_player::leave_table()
{
	if (m_table != nullptr)
	{
		m_table->leave_table(get_pid());
		m_table = nullptr;
		deskId = 0;
	}

	sycn_gold();
	if (is_first_save)		//保存数据
	{
		logic_player_db::store_game_object(true);
		is_first_save = false;
	}
	else
	{
		logic_player_db::store_game_object();
	}

	return true;
}

void logic_player::start_match()// 抢地主
{
	player_state = e_player_game_state::e_player_game_state_matching;
}

int logic_player::get_wait_time()// 抢地主
{
	return 10;
}

void logic_player::robLandlord(int or_Rob)// 抢地主
{
	m_table->rob_Landlord(this,or_Rob);
}

//出牌
e_server_error_code logic_player::playhand(const game_landlord_protocol::card_Info& cards)
{
	if (cards.deskid() != get_deskId())
	{
		return  e_server_error_code::e_error_code_failed;
	}

	bool result=m_table->check_playhand(cards);
	if (result == false)
	{
		e_server_error_code::e_error_code_failed;
	}
	m_table->do_protobuf_notice_playhand(cards);
	return e_server_error_code::e_error_code_success;
}

bool logic_player_db::load_player()
{
	mongo::BSONObj b = db_game::instance().findone(DB_LANDLORD_PLAYER, BSON("player_id" << m_player_id->get_value()));
	if (b.isEmpty())
		return false;

	return from_bson(b);
}

void logic_player_db::init_game_object()
{
	m_player_id = CONVERT_POINT(Tfield<int32_t>, regedit_tfield(e_got_int32, "player_id"));
}

//to_all：表示是否插入
bool logic_player_db::store_game_object(bool to_all)
{
	if (!has_update())
		return true;

	auto err = db_game::instance().update(DB_LANDLORD_PLAYER, BSON("player_id" << m_player_id->get_value()), BSON("$set" << to_bson(to_all)));
	if (!err.empty())
	{
		SLOG_ERROR << "logic_player::store_game_object :" << err;
		return false;
	}
	return true;
}




