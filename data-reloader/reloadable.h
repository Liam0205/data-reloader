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

#include <string>

namespace yuuki {
struct Reloadable {
  Reloadable() = default;
  virtual ~Reloadable() = default;

  Reloadable(const Reloadable&) = delete;
  Reloadable& operator=(const Reloadable&) = delete;

  Reloadable(Reloadable&&) = default;
  Reloadable& operator=(Reloadable&&) = default;

  virtual bool load(const std::string& path) = 0;
};
}  // namespace yuuki
