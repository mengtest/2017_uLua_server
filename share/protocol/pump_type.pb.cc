// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: pump_type.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "pump_type.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::EnumDescriptor* PropertyReasonType_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_pump_5ftype_2eproto() {
  protobuf_AddDesc_pump_5ftype_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "pump_type.proto");
  GOOGLE_CHECK(file != NULL);
  PropertyReasonType_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_pump_5ftype_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_pump_5ftype_2eproto() {
}

void protobuf_AddDesc_pump_5ftype_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017pump_type.proto*\250\013\n\022PropertyReasonType"
    "\022\034\n\030type_reason_dial_lottery\020\001\022\035\n\031type_r"
    "eason_online_reward\020\002\022\037\n\033type_reason_dep"
    "osit_safebox\020\003\022\034\n\030type_reason_draw_safeb"
    "ox\020\004\022\031\n\025type_reason_send_gift\020\005\022\033\n\027type_"
    "reason_accept_gift\020\006\022\035\n\031type_reason_play"
    "er_notify\020\007\022\030\n\024type_reason_exchange\020\010\022\"\n"
    "\036type_reason_buy_commodity_gain\020\t\022\034\n\030typ"
    "e_reason_receive_alms\020\n\022$\n type_reason_s"
    "ingle_round_balance\020\013\022$\n type_reason_buy"
    "_commodity_expend\020\014\022\035\n\031type_reason_buy_f"
    "ishlevel\020\r\022\034\n\030type_reason_buy_fishitem\020\016"
    "\022\034\n\030type_reason_fish_uplevel\020\017\022\031\n\025type_r"
    "eason_new_guild\020\020\022\033\n\027type_reason_update_"
    "icon\020\021\022\030\n\024type_reason_recharge\020\022\022\037\n\033type"
    "_reason_modify_nickname\020\023\022\035\n\031type_reason"
    "_recharge_send\020\024\022\033\n\027type_reason_gm_recha"
    "rge\020\025\022 \n\034type_reason_gm_recharge_send\020\026\022"
    "%\n!type_reason_month_card_daily_recv\020\027\022\035"
    "\n\031type_reason_recharge_gift\020\030\022\032\n\026type_re"
    "ason_daily_sign\020\031\022!\n\035type_reason_daily_b"
    "ox_lottery\020\032\022\"\n\036type_reason_thank_you_ex"
    "change\020\033\022\'\n#type_reason_continuous_send_"
    "speaker\020\034\022\034\n\030type_reason_receive_mail\020\035\022"
    "\035\n\031type_reason_fishlord_drop\020\036\022\036\n\032type_r"
    "eason_create_account\020\037\022\'\n#type_reason_re"
    "ceive_activity_reward\020 \022\032\n\026type_reason_r"
    "ob_banker\020!\022\034\n\030type_reason_leave_banker\020"
    "\"\022\031\n\025type_reason_use_skill\020#\022\033\n\027type_rea"
    "son_double_game\020$\022\032\n\026type_reason_dragons"
    "_lv\020%\022\032\n\026type_reason_star_award\020&\022\034\n\030typ"
    "e_reason_star_lottery\020\'\022\032\n\026type_reason_n"
    "ew_player\020(\022\032\n\026type_reason_daily_task\020)\022"
    "\033\n\027type_reason_achievement\020*\022\027\n\023type_rea"
    "son_missile\020+\022 \n\034type_reason_recharge_lo"
    "ttery\020,\022\030\n\024type_reason_shopping\020-\022!\n\035typ"
    "e_showhand_synchronization\020.", 1468);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "pump_type.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_pump_5ftype_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_pump_5ftype_2eproto {
  StaticDescriptorInitializer_pump_5ftype_2eproto() {
    protobuf_AddDesc_pump_5ftype_2eproto();
  }
} static_descriptor_initializer_pump_5ftype_2eproto_;
const ::google::protobuf::EnumDescriptor* PropertyReasonType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return PropertyReasonType_descriptor_;
}
bool PropertyReasonType_IsValid(int value) {
  switch(value) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
    case 19:
    case 20:
    case 21:
    case 22:
    case 23:
    case 24:
    case 25:
    case 26:
    case 27:
    case 28:
    case 29:
    case 30:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
