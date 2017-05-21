// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: client2world_activity.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "client2world_activity.pb.h"

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

namespace client2world_protocols {

namespace {

const ::google::protobuf::Descriptor* packetc2w_receive_activity_reward_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  packetc2w_receive_activity_reward_reflection_ = NULL;
const ::google::protobuf::Descriptor* packetw2c_receive_activity_reward_result_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  packetw2c_receive_activity_reward_result_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_client2world_5factivity_2eproto() {
  protobuf_AddDesc_client2world_5factivity_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "client2world_activity.proto");
  GOOGLE_CHECK(file != NULL);
  packetc2w_receive_activity_reward_descriptor_ = file->message_type(0);
  static const int packetc2w_receive_activity_reward_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(packetc2w_receive_activity_reward, packet_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(packetc2w_receive_activity_reward, activityid_),
  };
  packetc2w_receive_activity_reward_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      packetc2w_receive_activity_reward_descriptor_,
      packetc2w_receive_activity_reward::default_instance_,
      packetc2w_receive_activity_reward_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(packetc2w_receive_activity_reward, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(packetc2w_receive_activity_reward, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(packetc2w_receive_activity_reward));
  packetw2c_receive_activity_reward_result_descriptor_ = file->message_type(1);
  static const int packetw2c_receive_activity_reward_result_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(packetw2c_receive_activity_reward_result, packet_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(packetw2c_receive_activity_reward_result, result_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(packetw2c_receive_activity_reward_result, activityid_),
  };
  packetw2c_receive_activity_reward_result_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      packetw2c_receive_activity_reward_result_descriptor_,
      packetw2c_receive_activity_reward_result::default_instance_,
      packetw2c_receive_activity_reward_result_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(packetw2c_receive_activity_reward_result, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(packetw2c_receive_activity_reward_result, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(packetw2c_receive_activity_reward_result));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_client2world_5factivity_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    packetc2w_receive_activity_reward_descriptor_, &packetc2w_receive_activity_reward::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    packetw2c_receive_activity_reward_result_descriptor_, &packetw2c_receive_activity_reward_result::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_client2world_5factivity_2eproto() {
  delete packetc2w_receive_activity_reward::default_instance_;
  delete packetc2w_receive_activity_reward_reflection_;
  delete packetw2c_receive_activity_reward_result::default_instance_;
  delete packetw2c_receive_activity_reward_result_reflection_;
}

void protobuf_AddDesc_client2world_5factivity_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::client2world_protocols::protobuf_AddDesc_client2world_5fmsg_5ftype_2eproto();
  ::msg_type_def::protobuf_AddDesc_msg_5ftype_5fdef_2eproto();
  ::msg_info_def::protobuf_AddDesc_msg_5finfo_5fdef_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\033client2world_activity.proto\022\026client2wo"
    "rld_protocols\032\033client2world_msg_type.pro"
    "to\032\022msg_type_def.proto\032\022msg_info_def.pro"
    "to\"\230\001\n!packetc2w_receive_activity_reward"
    "\022_\n\tpacket_id\030\001 \001(\0162).client2world_proto"
    "cols.e_server_msg_type:!e_mst_c2w_receiv"
    "e_activity_reward\022\022\n\nactivityId\030\002 \001(\005\"\266\001"
    "\n(packetw2c_receive_activity_reward_resu"
    "lt\022f\n\tpacket_id\030\001 \001(\0162).client2world_pro"
    "tocols.e_server_msg_type:(e_mst_w2c_rece"
    "ive_activity_reward_result\022\016\n\006result\030\002 \001"
    "(\005\022\022\n\nactivityId\030\003 \001(\005", 462);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "client2world_activity.proto", &protobuf_RegisterTypes);
  packetc2w_receive_activity_reward::default_instance_ = new packetc2w_receive_activity_reward();
  packetw2c_receive_activity_reward_result::default_instance_ = new packetw2c_receive_activity_reward_result();
  packetc2w_receive_activity_reward::default_instance_->InitAsDefaultInstance();
  packetw2c_receive_activity_reward_result::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_client2world_5factivity_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_client2world_5factivity_2eproto {
  StaticDescriptorInitializer_client2world_5factivity_2eproto() {
    protobuf_AddDesc_client2world_5factivity_2eproto();
  }
} static_descriptor_initializer_client2world_5factivity_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int packetc2w_receive_activity_reward::kPacketIdFieldNumber;
const int packetc2w_receive_activity_reward::kActivityIdFieldNumber;
#endif  // !_MSC_VER

packetc2w_receive_activity_reward::packetc2w_receive_activity_reward()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:client2world_protocols.packetc2w_receive_activity_reward)
}

void packetc2w_receive_activity_reward::InitAsDefaultInstance() {
}

packetc2w_receive_activity_reward::packetc2w_receive_activity_reward(const packetc2w_receive_activity_reward& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:client2world_protocols.packetc2w_receive_activity_reward)
}

void packetc2w_receive_activity_reward::SharedCtor() {
  _cached_size_ = 0;
  packet_id_ = 5056;
  activityid_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

packetc2w_receive_activity_reward::~packetc2w_receive_activity_reward() {
  // @@protoc_insertion_point(destructor:client2world_protocols.packetc2w_receive_activity_reward)
  SharedDtor();
}

void packetc2w_receive_activity_reward::SharedDtor() {
  if (this != default_instance_) {
  }
}

void packetc2w_receive_activity_reward::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* packetc2w_receive_activity_reward::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return packetc2w_receive_activity_reward_descriptor_;
}

const packetc2w_receive_activity_reward& packetc2w_receive_activity_reward::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_client2world_5factivity_2eproto();
  return *default_instance_;
}

packetc2w_receive_activity_reward* packetc2w_receive_activity_reward::default_instance_ = NULL;

packetc2w_receive_activity_reward* packetc2w_receive_activity_reward::New() const {
  return new packetc2w_receive_activity_reward;
}

void packetc2w_receive_activity_reward::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    packet_id_ = 5056;
    activityid_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool packetc2w_receive_activity_reward::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:client2world_protocols.packetc2w_receive_activity_reward)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .client2world_protocols.e_server_msg_type packet_id = 1 [default = e_mst_c2w_receive_activity_reward];
      case 1: {
        if (tag == 8) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::client2world_protocols::e_server_msg_type_IsValid(value)) {
            set_packet_id(static_cast< ::client2world_protocols::e_server_msg_type >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_activityId;
        break;
      }

      // optional int32 activityId = 2;
      case 2: {
        if (tag == 16) {
         parse_activityId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &activityid_)));
          set_has_activityid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:client2world_protocols.packetc2w_receive_activity_reward)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:client2world_protocols.packetc2w_receive_activity_reward)
  return false;
#undef DO_
}

void packetc2w_receive_activity_reward::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:client2world_protocols.packetc2w_receive_activity_reward)
  // optional .client2world_protocols.e_server_msg_type packet_id = 1 [default = e_mst_c2w_receive_activity_reward];
  if (has_packet_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->packet_id(), output);
  }

  // optional int32 activityId = 2;
  if (has_activityid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->activityid(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:client2world_protocols.packetc2w_receive_activity_reward)
}

::google::protobuf::uint8* packetc2w_receive_activity_reward::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:client2world_protocols.packetc2w_receive_activity_reward)
  // optional .client2world_protocols.e_server_msg_type packet_id = 1 [default = e_mst_c2w_receive_activity_reward];
  if (has_packet_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->packet_id(), target);
  }

  // optional int32 activityId = 2;
  if (has_activityid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->activityid(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:client2world_protocols.packetc2w_receive_activity_reward)
  return target;
}

int packetc2w_receive_activity_reward::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .client2world_protocols.e_server_msg_type packet_id = 1 [default = e_mst_c2w_receive_activity_reward];
    if (has_packet_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->packet_id());
    }

    // optional int32 activityId = 2;
    if (has_activityid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->activityid());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void packetc2w_receive_activity_reward::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const packetc2w_receive_activity_reward* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const packetc2w_receive_activity_reward*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void packetc2w_receive_activity_reward::MergeFrom(const packetc2w_receive_activity_reward& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_packet_id()) {
      set_packet_id(from.packet_id());
    }
    if (from.has_activityid()) {
      set_activityid(from.activityid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void packetc2w_receive_activity_reward::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void packetc2w_receive_activity_reward::CopyFrom(const packetc2w_receive_activity_reward& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool packetc2w_receive_activity_reward::IsInitialized() const {

  return true;
}

void packetc2w_receive_activity_reward::Swap(packetc2w_receive_activity_reward* other) {
  if (other != this) {
    std::swap(packet_id_, other->packet_id_);
    std::swap(activityid_, other->activityid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata packetc2w_receive_activity_reward::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = packetc2w_receive_activity_reward_descriptor_;
  metadata.reflection = packetc2w_receive_activity_reward_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int packetw2c_receive_activity_reward_result::kPacketIdFieldNumber;
const int packetw2c_receive_activity_reward_result::kResultFieldNumber;
const int packetw2c_receive_activity_reward_result::kActivityIdFieldNumber;
#endif  // !_MSC_VER

packetw2c_receive_activity_reward_result::packetw2c_receive_activity_reward_result()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:client2world_protocols.packetw2c_receive_activity_reward_result)
}

void packetw2c_receive_activity_reward_result::InitAsDefaultInstance() {
}

packetw2c_receive_activity_reward_result::packetw2c_receive_activity_reward_result(const packetw2c_receive_activity_reward_result& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:client2world_protocols.packetw2c_receive_activity_reward_result)
}

void packetw2c_receive_activity_reward_result::SharedCtor() {
  _cached_size_ = 0;
  packet_id_ = 7559;
  result_ = 0;
  activityid_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

packetw2c_receive_activity_reward_result::~packetw2c_receive_activity_reward_result() {
  // @@protoc_insertion_point(destructor:client2world_protocols.packetw2c_receive_activity_reward_result)
  SharedDtor();
}

void packetw2c_receive_activity_reward_result::SharedDtor() {
  if (this != default_instance_) {
  }
}

void packetw2c_receive_activity_reward_result::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* packetw2c_receive_activity_reward_result::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return packetw2c_receive_activity_reward_result_descriptor_;
}

const packetw2c_receive_activity_reward_result& packetw2c_receive_activity_reward_result::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_client2world_5factivity_2eproto();
  return *default_instance_;
}

packetw2c_receive_activity_reward_result* packetw2c_receive_activity_reward_result::default_instance_ = NULL;

packetw2c_receive_activity_reward_result* packetw2c_receive_activity_reward_result::New() const {
  return new packetw2c_receive_activity_reward_result;
}

void packetw2c_receive_activity_reward_result::Clear() {
#define OFFSET_OF_FIELD_(f) (reinterpret_cast<char*>(      \
  &reinterpret_cast<packetw2c_receive_activity_reward_result*>(16)->f) - \
   reinterpret_cast<char*>(16))

#define ZR_(first, last) do {                              \
    size_t f = OFFSET_OF_FIELD_(first);                    \
    size_t n = OFFSET_OF_FIELD_(last) - f + sizeof(last);  \
    ::memset(&first, 0, n);                                \
  } while (0)

  if (_has_bits_[0 / 32] & 7) {
    ZR_(result_, activityid_);
    packet_id_ = 7559;
  }

#undef OFFSET_OF_FIELD_
#undef ZR_

  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool packetw2c_receive_activity_reward_result::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:client2world_protocols.packetw2c_receive_activity_reward_result)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional .client2world_protocols.e_server_msg_type packet_id = 1 [default = e_mst_w2c_receive_activity_reward_result];
      case 1: {
        if (tag == 8) {
          int value;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::client2world_protocols::e_server_msg_type_IsValid(value)) {
            set_packet_id(static_cast< ::client2world_protocols::e_server_msg_type >(value));
          } else {
            mutable_unknown_fields()->AddVarint(1, value);
          }
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_result;
        break;
      }

      // optional int32 result = 2;
      case 2: {
        if (tag == 16) {
         parse_result:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &result_)));
          set_has_result();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_activityId;
        break;
      }

      // optional int32 activityId = 3;
      case 3: {
        if (tag == 24) {
         parse_activityId:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &activityid_)));
          set_has_activityid();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:client2world_protocols.packetw2c_receive_activity_reward_result)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:client2world_protocols.packetw2c_receive_activity_reward_result)
  return false;
#undef DO_
}

void packetw2c_receive_activity_reward_result::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:client2world_protocols.packetw2c_receive_activity_reward_result)
  // optional .client2world_protocols.e_server_msg_type packet_id = 1 [default = e_mst_w2c_receive_activity_reward_result];
  if (has_packet_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->packet_id(), output);
  }

  // optional int32 result = 2;
  if (has_result()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->result(), output);
  }

  // optional int32 activityId = 3;
  if (has_activityid()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->activityid(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:client2world_protocols.packetw2c_receive_activity_reward_result)
}

::google::protobuf::uint8* packetw2c_receive_activity_reward_result::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:client2world_protocols.packetw2c_receive_activity_reward_result)
  // optional .client2world_protocols.e_server_msg_type packet_id = 1 [default = e_mst_w2c_receive_activity_reward_result];
  if (has_packet_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->packet_id(), target);
  }

  // optional int32 result = 2;
  if (has_result()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->result(), target);
  }

  // optional int32 activityId = 3;
  if (has_activityid()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->activityid(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:client2world_protocols.packetw2c_receive_activity_reward_result)
  return target;
}

int packetw2c_receive_activity_reward_result::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional .client2world_protocols.e_server_msg_type packet_id = 1 [default = e_mst_w2c_receive_activity_reward_result];
    if (has_packet_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::EnumSize(this->packet_id());
    }

    // optional int32 result = 2;
    if (has_result()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->result());
    }

    // optional int32 activityId = 3;
    if (has_activityid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->activityid());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void packetw2c_receive_activity_reward_result::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const packetw2c_receive_activity_reward_result* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const packetw2c_receive_activity_reward_result*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void packetw2c_receive_activity_reward_result::MergeFrom(const packetw2c_receive_activity_reward_result& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_packet_id()) {
      set_packet_id(from.packet_id());
    }
    if (from.has_result()) {
      set_result(from.result());
    }
    if (from.has_activityid()) {
      set_activityid(from.activityid());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void packetw2c_receive_activity_reward_result::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void packetw2c_receive_activity_reward_result::CopyFrom(const packetw2c_receive_activity_reward_result& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool packetw2c_receive_activity_reward_result::IsInitialized() const {

  return true;
}

void packetw2c_receive_activity_reward_result::Swap(packetw2c_receive_activity_reward_result* other) {
  if (other != this) {
    std::swap(packet_id_, other->packet_id_);
    std::swap(result_, other->result_);
    std::swap(activityid_, other->activityid_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata packetw2c_receive_activity_reward_result::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = packetw2c_receive_activity_reward_result_descriptor_;
  metadata.reflection = packetw2c_receive_activity_reward_result_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace client2world_protocols

// @@protoc_insertion_point(global_scope)
