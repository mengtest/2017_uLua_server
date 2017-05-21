#include "stdafx.h"
#include "proc_game_landlord_protocol.h"
#include <i_game_player.h>
#include "game_engine.h"

using namespace boost;

void init_proc_landlord_protocol()
{
	packetc2l_enter_room_factory::regedit_factory();
	packetl2c_enter_room_result_factory::regedit_factory();
}

//进入斗地主房间
bool packetc2l_enter_room_factory::packet_process(shared_ptr<peer_tcp> peer, shared_ptr<i_game_player> player,shared_ptr<packetc2l_enter_room> msg)
{	
	__ENTER_FUNCTION_CHECK;

	auto sendmsg = PACKET_CREATE(packetl2c_enter_room_result, e_mst_l2c_enter_room);

	
	
	player->send_msg_to_client(sendmsg);

	__LEAVE_FUNCTION_CHECK
		return !EX_CHECK;
}

