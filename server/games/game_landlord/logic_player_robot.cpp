#include "stdafx.h"
#include "logic_player.h"
#include "logic_room.h"
#include "game_engine.h"
#include <enable_random.h>
#include "Landlord_RoomCFG.h"

//创建机器人
void logic_room::create_robot()
{
	/*static int player_min = landlord_BaseCFG::GetSingleton()->GetData("PlayerMinCount")->mValue;
	if (m_rob_count < robMinCount)
	{
		//--------------------there code is skill--------------------------
		std::vector<int> tempProb;
		int tempTotal = 0;
		for (int k = 0; k < m_cfg->mCreateProb.size(); k++)
		{
			tempTotal += m_cfg->mCreateProb.at(k);
			tempProb.push_back(tempTotal);
		}
		int tempInt = 1;
		if (m_db_room_id->get_value() == 1)
		{
			tempInt = global_random::instance().rand_int(1,tempTotal);
		}
		else
		{
			int minInx=m_cfg->mCreateProb[0]-10>30?m_cfg->mCreateProb[0]:30;
			tempInt = global_random::instance().rand_int(minInx,tempTotal);
		}

		int random_tag = 1;
		for (int i = 0; i < tempProb.size(); i++)
		{
			if (tempInt <= tempProb[i])
			{
				random_tag = m_cfg->mRobTag.at(i);
				break;
			}
		}
		//----------------------------------------------------------------
		int gold_min = landlord_RobCFG::GetSingleton()->GetData(random_tag)->mGoldMin;
		int gold_max = landlord_RobCFG::GetSingleton()->GetData(random_tag)->mGoldMax;
		int vip_min = landlord_RobCFG::GetSingleton()->GetData(random_tag)->mVipMin;
		int vip_max = landlord_RobCFG::GetSingleton()->GetData(random_tag)->mVipMax;
		game_engine::instance().request_robot(m_db_room_id->get_value(), global_random::instance().rand_int(gold_min,gold_max), global_random::instance().rand_int(vip_min,vip_max));
	}*/
}
//机器人AI
void logic_player::robot_heartbeat( double elapsed )
{
	//投注砝码最小
	/*static int chip_min = m_room->get_room_cfg()->mWeightList[0];
	if (is_robot() && !is_banker)
	{
		if (m_room->get_room_state() == e_game_state::e_state_game_begin)
		{
			//机器人现有金币大于上庄金币
			if (get_gold() > landlord_RoomCFG::GetSingleton()->GetData(get_room()->get_room_id())->mBankerCondition)
			{
				m_room->add_banker_list(get_pid());
			}
			static const int RobBetMin = landlord_BaseCFG::GetSingleton()->GetData("RobBetMin")->mValue;//机器人下注最小金额
			static const int RobBetMax = landlord_BaseCFG::GetSingleton()->GetData("RobBetMax")->mValue;//机器人下注最大金额
			m_rob_bet_max = get_gold()/20;
			m_rob_bet_remain = m_rob_bet_max;
		}
		else if (m_room->get_room_state() == e_game_state::e_state_game_bet)
		{
			m_rob_bet_cd -= elapsed;
			if (m_rob_bet_cd <= 0 && m_rob_bet_remain > chip_min && m_room->get_cd_time() > 1.0)
			{
				int bet_count = get_rob_bet();
				m_rob_bet_remain -= bet_count;
				int random_index = global_random::instance().rand_int(1,100);

				int randIndex=global_random::instance().rand_int(1,9);
				if(randIndex==1)
				{
					add_bet(e_bettype_forwarddoor,bet_count);
				}else if(randIndex==2)
				{
					add_bet(e_bettype_oppositedoor,bet_count);
				}
				else if(randIndex==3)
				{
					add_bet(e_bettype_reversedoor,bet_count);
				}else if(randIndex==4 ||randIndex==5)
				{
					add_bet(e_bettype_forward_opposite_door,bet_count);
				}
				else if(randIndex==6 ||randIndex==7)
				{
					add_bet(e_bettype_reverse_opposite_door,bet_count);
				}
				else if(randIndex==8 ||randIndex==9)
				{
					add_bet(e_bettype_forward_reverse_door,bet_count);
				}
				m_rob_bet_cd = global_random::instance().rand_int(1, 3);
			}	
		}
	}*/
}
