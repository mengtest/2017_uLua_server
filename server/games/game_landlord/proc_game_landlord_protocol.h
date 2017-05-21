#pragma once
#include <net\packet_manager.h>
#include <game_landlord_protocol.pb.h>
#include <net\peer_tcp.h>

class i_game_player;
using namespace game_landlord_protocol;

void init_proc_landlord_protocol();


//进入战场
PACKET_REGEDIT_RECVGATE_LOG(peer_tcp, packetc2l_enter_room, i_game_player);
PACKET_REGEDIT_SEND(packetl2c_enter_room_result);

