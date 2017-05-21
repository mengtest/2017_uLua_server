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
,m_room(nullptr)
,m_logic_gold(0)
,m_change_gold(0)
,m_checksave(0.0)
,is_first_save(true)
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
	//leave_room();
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
			logic_player_db::store_game_object();
		m_checksave = 0.0;
	}

	if (m_room == nullptr)
		return;

	robot_heartbeat(elapsed);
}

void logic_player::enter_game(logic_lobby* lobby)
{
	m_lobby = lobby;
	m_player_id->set_value(get_pid());
	logic_player_db::load_player();

	m_logic_gold = m_player->get_attribute64(msg_type_def::e_itd_gold);//m_player->get_attribute(msg_type_def::e_itd_gold);

}

bool logic_player::enter_room(logic_room* room)
{
	if(m_room != nullptr && room == nullptr)
		return false;

	m_room = room;
	m_logic_gold = m_player->get_attribute64(msg_type_def::e_itd_gold);

	return true;
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

bool logic_player::is_GM_CONTROL()
{
	return m_player->get_attribute(msg_type_def::e_itd_privilege)> 0;
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

void logic_player::leave_room()
{
	/*if(m_room != nullptr)
	{
		if (m_room->get_room_state() == e_game_state::e_state_game_bet)
		{
			m_room->set_is_have_bet(true);
		}		
		m_room->leave_room(get_pid());
		m_room = nullptr;
	}	
	clear_table_data();

	sycn_gold();

	if (is_first_save)		//保存数据
	{
		logic_player_db::store_game_object(true);
		is_first_save = false;
	}
	else
	{
		logic_player_db::store_game_object();
	}*/
}

void logic_player::escapeHandle()
{


}

e_player_state logic_player::get_game_state()
{
	return m_player->get_state();
}

void logic_player::release()
{
	leave_room();
	m_player.reset();
}

void logic_player::quest_change(int quest_type,int count,int param)
{
	if (is_robot())
		return;

	m_player->quest_change(quest_type,count,param);
}





