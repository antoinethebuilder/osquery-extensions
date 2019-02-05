/*
 * Copyright (c) 2018 Trail of Bits, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "ebpfprobe.h"

#include <map>
#include <string>
#include <vector>

#include <boost/optional.hpp>
#include <boost/variant.hpp>

namespace trailofbits {
class ManagedProbe;
using ManagedProbeRef = std::unique_ptr<ManagedProbe>;

struct SystemCallEvent final {
  struct StringList final {
    bool truncated{false};
    std::vector<std::string> data;
  };

  using FieldValue = boost::variant<std::int64_t,
                                    std::uint64_t,
                                    std::string,
                                    std::vector<std::uint8_t>,
                                    StringList>;

  using FieldList = std::map<std::string, FieldValue>;

  std::uint64_t timestamp{0U};
  std::uint64_t syscall_number{0U};
  pid_t pid{0U};
  pid_t tgid{0U};
  uid_t uid{0U};
  gid_t gid{0U};
  boost::optional<int> exit_code;
  FieldList field_list;
};

using SystemCallEventList = std::vector<SystemCallEvent>;

class ManagedProbe final {
  struct PrivateData;
  std::unique_ptr<PrivateData> d;

  ManagedProbe(const ManagedProbeDescriptor& desc);

  static void callbackDispatcher(void* callback_data,
                                 void* data,
                                 int data_size);

  void callback(const std::uint32_t* data, std::size_t data_size);

 public:
  static osquery::Status create(ManagedProbeRef& object,
                                const ManagedProbeDescriptor& desc);
  ~ManagedProbe();

  ManagedProbe(const ManagedProbe&) = delete;
  ManagedProbe& operator=(const ManagedProbe&) = delete;
};

std::ostream& operator<<(std::ostream& stream,
                         const SystemCallEvent& system_call_event);
} // namespace trailofbits
