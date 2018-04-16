/* Copyright (c) 2017-2018, Hans Erik Thrane */

#pragma once

#include <rapidjson/document.h>

#include <string>

namespace examples {
namespace config {

class JSON final {
 public:
  explicit JSON(const std::string& path);

  std::ostream& write(std::ostream&) const;

 private:
  rapidjson::Document _document;
};

inline std::ostream& operator<<(
    std::ostream& stream,
    const JSON& json) {
  return json.write(stream);
}

}  // namespace config
}  // namespace examples