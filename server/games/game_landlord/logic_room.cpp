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

logic_room::logic_room(const Landlord_RoomCFGData* cfg, logic_lobby* _lobby):
	m_cd_time(0.0)
	,is_have_bet(false)
	,m_banker_once_win(0)
	,m_banker_total_win(0)
	,m_system_draw_water(0)
	,m_draw_water_rate(0.0)
	,m_once_income(0)
	,m_once_outcome(0)
	,m_continue_banker_count(0)
	,m_now_banker_id(0)
	,m_old_banker_id(0)
	,m_elapse(0.0)
	,is_change_banker(false)
	,m_checksave(0.0)
	,is_have_banker(false)
	,is_can_rob_banker(false)
	,m_rob_banker_id(0)
	,m_rob_banker_cost(0)
	,is_have_rob_banker(false)
	,m_total_bet_count(0)
	,m_rob_cd(0.0)
	,m_rob_count(0)
	,m_rob_earn_rate(0.0)
	,m_no_banker_count(0)
	,is_refresh_history(false)
	,IsOpenRob(false)
	,currentNeedRobCount_cd(0.0)
{
	m_cfg = cfg;
	m_lobby = _lobby;

	m_core_engine = new logic_core;

	/*logic_room_db::init_game_object();
	m_db_room_id->set_value(m_cfg->mRoomID);
	if(!load_room())
	{
		create_room();
	}

	//历史记录
	m_history_list.clear();
	for(int i = 0; i < m_db_room_historyPtr->get_obj_count(); i++)
	{
		auto ptr = m_db_room_historyPtr->get_Tobj<HistoryItem>(i);
		history_info temp;

		msg_bet_result_info* info=temp.add_result_list();
		info->set_type(e_bettype_forwarddoor);
		if(ptr->is_forwarddoor_win->get_value())
		{
			info->set_result(e_betresult_win);
		}else
		{
			info->set_result(e_betresult_lose);
		}

		info=temp.add_result_list();
		info->set_type(e_bettype_oppositedoor);
		if(ptr->is_oppositedoor_win->get_value())
		{
			info->set_result(e_betresult_win);
		}else
		{
			info->set_result(e_betresult_lose);
		}

		info=temp.add_result_list();
		info->set_type(e_bettype_reversedoor);
		if(ptr->is_reversedoor_win->get_value())
		{
			info->set_result(e_betresult_win);
		}else
		{
			info->set_result(e_betresult_lose);
		}
		m_history_list.push_back(temp);
	}*/
}

logic_room::~logic_room(void)
{
	SAFE_DELETE(m_core_engine);
}

void logic_room::heartbeat( double elapsed )
{
	
}

//得到机器人概率（没有引用）
int logic_room::GetPeopleRate(int iMaxNum)
{
	int  iNum = 0;
	__time64_t times;
	errno_t err;
	_time64(&times);
	tm tms;

	if (iMaxNum <= 0)
	{
		return 0;
	}

	err = _localtime64_s(&tms, &times);

	if (tms.tm_hour > 19)
	{
		iNum = iMaxNum / 2 + rand() % (iMaxNum / 2);
	}
	else if (tms.tm_hour > 4 && tms.tm_hour < 7)
	{
		iNum = -(2 + rand() % (iMaxNum / 2));
	}
	else
	{
		iNum = rand() % (iMaxNum / 2);
	}
	return iNum;
}


bool logic_room::sync_bet_to_room()
{
	if (!is_have_bet)
		return false;

	/*m_room_bet_list.clear();
	m_total_bet_count = 0;
	for (auto it = playerMap.begin(); it != playerMap.end(); ++it)
	{
		std::map<e_bet_type,GOLD_TYPE>& temp_bet = it->second->get_bet_list();
		for (auto& it : temp_bet)
		{
			m_room_bet_list[it.first] += it.second;
			m_total_bet_count += it.second;
		}
	}

	is_have_bet = false;*/
	return true;
}

uint16_t logic_room::get_room_id()
{
	return m_cfg->mRoomID;
}

void logic_room::set_is_have_bet(bool is_have)
{
	is_have_bet = is_have;
}

bool logic_room::room_is_full()
{
	if (playerMap.size() >= 5000)
		return true;
	return false;
}

//玩家进入房间
uint16_t logic_room::enter_room(LPlayerPtr player)
{
	/*if (playerMap.find(player->get_pid()) != playerMap.end())
		return msg_type_def::e_rmt_fail;

	if (playerMap.size() >= m_cfg->mPlayerMaxCount)		//房间已满
		return msg_type_def::e_rmt_room_full;

	if (!player->enter_room(this))
		return msg_type_def::e_rmt_fail;
	
	playerMap.insert(std::make_pair(player->get_pid(), player));

	if (player->is_robot())
		m_rob_count++;

	m_db_enter_count->add_value(1);

	if (!player->is_robot())
		db_log::instance().joingame(player->get_pid(), get_room_id());

	return msg_type_def::e_rmt_success;*/
	return 0;
}

void logic_room::leave_room(uint32_t playerid)
{
	/*auto it = playerMap.find(playerid);
	if(it == playerMap.end())
	{
		return;
	}
	if (it->second->get_is_banker())
	{
		it->second->set_is_banker(false);
		set_now_banker_null(playerid);
	}

	if (it->second->is_robot())
	{
		m_rob_count-- ;
	}

	if (!it->second->is_robot())//只记录非机器人的
	{
		db_log::instance().leavegame(playerid);
	}

	playerMap.erase(it);

	for (auto ita = m_banker_list.begin(); ita != m_banker_list.end(); )
	{
		if ((*ita) == playerid)
		{
			ita = m_banker_list.erase(ita);
		}
		else
		{
			++ita;
		}
	}

	if (playerid == m_rob_banker_id)
	{
		m_rob_banker_id = 0;
		bc_rob_banker_info();//
	}*/
}

const Landlord_RoomCFGData* logic_room::get_room_cfg() const
{
	return m_cfg;
}






