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

#include "managedprobe.h"

#include <memory>

#include <osquery/status.h>

namespace trailofbits {
class eBPFEventSource;
using eBPFEventSourceRef = std::unique_ptr<eBPFEventSource>;

class eBPFEventSource final {
  struct PrivateData;
  std::unique_ptr<PrivateData> d;

  eBPFEventSource();

 public:
  static osquery::Status create(eBPFEventSourceRef& object);
  ~eBPFEventSource();

  SystemCallEventList getEvents();

  eBPFEventSource(const eBPFEventSource&) = delete;
  eBPFEventSource& operator=(const eBPFEventSource&) = delete;
};
} // namespace trailofbits