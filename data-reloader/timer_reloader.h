// =========================================================================
// Copyright 2021 -- present Liam Huang (Yuuki) [liamhuang0205@gmail.com].
// Author: Liam Huang
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// =========================================================================

#pragma once

#include <countdown/countdown/countdown.h>

#include <string>
#include <thread>
#include <utility>

#include "data-reloader/reloader_base.h"

namespace yuuki {
template <typename Payload>
class TimerReloader : public Reloader<Payload> {
 private:
  uint64_t sleep_{0UL};
  std::thread thread_;
  Countdown cd_;

 public:
  TimerReloader() = default;
  ~TimerReloader() {
    terminate();
    if (thread_.joinable()) {
      thread_.join();
    }
  }

 public:  // modifiers
  bool init(const std::string& path, uint64_t sleep) {
    sleep_ = sleep;
    return Reloader<Payload>::init(path);
  }

 private:
  void launch() override {
    thread_ = std::move(std::thread(&TimerReloader::loop, this));
  }

 public:  // modifiers
  void terminate() override {
    cd_.terminate();
  }

 private:
  void loop() {
    while (cd_.wait_for(std::chrono::seconds(sleep_))) {
      Reloader<Payload>::reload();
    }
  }
};
}  // namespace yuuki
