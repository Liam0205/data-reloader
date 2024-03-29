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

#include <atomic>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <type_traits>
#include <utility>

#include "data-reloader/reloadable.h"

namespace yuuki {
template <typename Payload, std::enable_if_t<std::is_base_of<Reloadable, Payload>::value, bool> = true>
class Reloader {
 public:
  using payload_t = Payload;
  using ptr_t = std::shared_ptr<payload_t>;
#if __cplusplus >= 201703L
  using shared_mutex = std::shared_mutex;
#else
  using shared_mutex = std::shared_timed_mutex;
#endif

 private:
  std::atomic_bool inited_{false};
  std::once_flag init_flag_;
  mutable shared_mutex mtx_;
  ptr_t payload_;
  std::string path_;

 public:
  Reloader() = default;
  virtual ~Reloader() = default;

 private:
  Reloader(const Reloader&) = delete;
  Reloader& operator=(const Reloader&) = delete;

 public:  // modifiers
  bool init(const std::string& path) {
    std::call_once(init_flag_, [&]() -> void {
      this->path(path);

      reload();
      launch();
      inited_.store(true, std::memory_order_release);
    });
    return inited();
  }

  virtual void terminate() = 0;

 public:  // observers
  bool inited() const {
    return inited_.load(std::memory_order_acquire);
  }

  ptr_t get() const {
    std::shared_lock<shared_mutex> lk(mtx_);
    return payload_;
  }

  const std::string& path() const {
    return path_;
  }

 protected:  // modifiers
  bool reload() {
    ptr_t tmp = std::make_shared<payload_t>();
    if (tmp->load(path_)) {
      {
        std::unique_lock<shared_mutex> lk(mtx_);
        payload_.swap(tmp);
      }
      return true;
    } else {
      return false;
    }
  }

  void path(const std::string& p) {
    path_ = p;
  }

 private:
  virtual void launch() = 0;
};
}  // namespace yuuki
