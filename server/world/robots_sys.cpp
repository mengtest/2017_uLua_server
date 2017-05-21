#include "stdafx.h"
#include "robots_sys.h"
#include "game_db.h"
#include "game_player.h"
#include "game_sys_recharge.h"
#include "game_player_mgr.h"
#include <algorithm>
#include "M_RobotNameCFG.h"
#include <enable_random.h>
#include "M_BaseInfoCFG.h"

using namespace boost;

//////////////////////////////////////////////////////////////////////////
bool sort_robot(idle_robot& a, idle_robot& b)
{
	return a.vip <= b.vip;
}

class find_robot
{
public:
	find_robot(int tmpvip)
	{
		needvip = tmpvip;
	}

	bool operator()(const idle_robot& ir) 
	{
		return needvip == ir.vip;
	}
private:
	int needvip;
};

class check_robot
{
public:
	check_robot(int _playerid)
	{
		playerid = _playerid;
	}

	bool operator()(const idle_robot& ir) 
	{
		return playerid == ir.playerid;
	}
private:
	int playerid;
};
//////////////////////////////////////////////////////////////////////////
RobotsSys::RobotsSys()
	:m_robotcount(0)
{

}

void RobotsSys::init_sys_object()
{
}


bool RobotsSys::sys_load()
{
	mongo::BSONObj cond = BSON("is_robot" << true);
	mongo::BSONObj fields = BSON("player_id" << 1 << "VipLevel"<<1);

	std::vector<mongo::BSONObj> vec;
	db_player::instance().find(vec, DB_PLAYER_INFO, cond, &fields);

	m_robots.clear();

	if(!vec.empty())
	{
		for(int i = 0; i < (int)vec.size(); i++)
		{
			mongo::BSONObj& obj = vec[i];
			idle_robot ir;
			ir.playerid = obj.getIntField("player_id");
			ir.vip = obj.getIntField("VipLevel");
			//ir.gold = obj.getField("gold").Long();
			m_robots.push_back(ir);
		}

		//std::sort(m_robots.begin(), m_robots.end(), sort_robot);
	}
	return true;
}

GPlayerPtr RobotsSys::request_robot(GOLD_TYPE needgold, int needvip)
{
	//先找个已创建的
	int playerid = -1;
	auto it = std::find_if(m_robots.begin(), m_robots.end(), find_robot(needvip));
	if(it != m_robots.end())
	{
		playerid = (*it).playerid;
		m_robots.erase(it);
	}

	//if(playerid <=0 && m_robots.size()>0)
	//{
	//	auto fit = m_robots.front();
	//	playerid = fit.playerid;
	//	m_robots.pop_front();
	//}

	auto p = game_player::malloc();
	p->load_robot(playerid);

	//这里做改名，升级VIP，增加金币等操作
	//static int maxgold = M_BaseInfoCFG::GetSingleton()->GetData("MaxGold")->mValue;
	//if(p->Gold->get_value()<needgold || maxgold < p->Gold->get_value())
	//{
		p->Gold->set_value(needgold);//金币
	//}

	if(p->get_viplvl() < needvip)
	{
		auto vipmgr = p->get_sys<game_sys_recharge>();
		vipmgr->VipLevel->set_value(needvip);//vip
	}
	


	//p->store_game_object();

	m_robotcount++;

	return p;
}


void RobotsSys::release_robot(int playerid, int vip, GOLD_TYPE gold)
{
	auto it = std::find_if(m_robots.begin(), m_robots.end(), check_robot(playerid));
	if(it != m_robots.end())
		return;

	idle_robot ir;
	ir.playerid = playerid;
	ir.vip = vip;
	ir.gold = gold;
	m_robots.push_back(ir);
	//std::sort(m_robots.begin(), m_robots.end(), sort_robot);

	m_robotcount--;
}

int RobotsSys::get_count()
{
	return m_robotcount;
}