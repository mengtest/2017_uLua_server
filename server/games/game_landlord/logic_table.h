#pragma once
#include "logic_def.h"
#include "logic_core.h"
#include "proc_game_landlord_protocol.h"

class logic_table_db :public game_object
{
protected:
	void create_table();
	bool load_table();
public:
	virtual void init_game_object() override;//注册属性
	virtual bool store_game_object(bool to_all = false) override;//非数组对象必须实现此接口

	Tfield<int16_t>::TFieldPtr		m_db_table_id;			//房间id
};

class logic_table :public logic_table_db
{
public:
	logic_table(int);
	~logic_table(void);

	void heartbeat(double elapsed);
	uint16_t get_table_id();			//房间ID

	uint16_t enter_table(LPlayerPtr player);		//进入房间
	void leave_table(uint32_t playerid);			//离开房间

	logic_lobby* get_lobby() { return m_lobby; };
public:
	template<class T>
	int broadcast_msg_to_client(T msg, uint32_t except_id = 0)
	{
		return broadcast_msg_to_client(msg->packet_id(), msg, except_id);
	};
	int broadcast_msg_to_client(uint16_t packet_id, boost::shared_ptr<google::protobuf::Message> msg, uint32_t except_id);
private:
	logic_lobby* m_lobby;
	LPLAYER_MAP playerMap;		//所有玩家字典
	int32_t m_tableId;
};