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

#include "data-reloader/reloader_base.h"

#include <catch.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <iostream>

#include "data-reloader/reloadable.h"

struct Test final : public yuuki::Reloadable {
  bool load(const std::string& path) final {
    struct stat info;
    if (stat(path.c_str(), &info) == 0) {
      // print some info log here.
      return true;
    } else {
      // print some error log here.
      std::cerr << "Loading failed with path: " << path << '\n';
      return false;
    }
  }
};

template <typename Payload>
class ReloaderTest final : public yuuki::Reloader<Payload> {
 public:
  void terminate() override {
    return;
  }

 private:
  void launch() override {
    return;
  }
};

TEST_CASE("Construct") {
  REQUIRE_NOTHROW(ReloaderTest<Test>());
}

TEST_CASE("Observers") {
  ReloaderTest<Test> tester;

  REQUIRE_FALSE(tester.inited());
  REQUIRE_FALSE(tester.get());
}

TEST_CASE("Modifiers") {
  ReloaderTest<Test> tester;

  SECTION("init failed") {
    REQUIRE(tester.init("nonexists"));
    REQUIRE_FALSE(tester.get());
    REQUIRE(tester.path() == "nonexists");
  }

  SECTION("init succ") {
    REQUIRE(tester.init("./blade"));
    REQUIRE(tester.inited());
    REQUIRE(tester.get());
    REQUIRE(tester.path() == "./blade");
  }
}
