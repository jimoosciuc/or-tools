// Copyright 2026 Google LLC
// Licensed under the Apache License, Version 2.0 (the "License");

#ifndef OR_TOOLS_SAT_RUNTIME_PROGRESS_H_
#define OR_TOOLS_SAT_RUNTIME_PROGRESS_H_

#include <cstdint>
#include <string>

namespace operations_research {
namespace sat {

int64_t RuntimeProgressNowNanos();
void RuntimeProgressPrint(const std::string& line);

class RuntimeProgressStage {
 public:
  RuntimeProgressStage(bool enabled, std::string owner, std::string phase,
                       std::string operation);
  ~RuntimeProgressStage();
  RuntimeProgressStage(const RuntimeProgressStage&) = delete;
  RuntimeProgressStage& operator=(const RuntimeProgressStage&) = delete;

 private:
  bool enabled_;
  std::string owner_;
  std::string phase_;
  std::string operation_;
  int64_t started_ns_;
};

}  // namespace sat
}  // namespace operations_research

#endif  // OR_TOOLS_SAT_RUNTIME_PROGRESS_H_
