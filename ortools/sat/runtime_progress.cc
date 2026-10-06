// Copyright 2026 Google LLC
// Licensed under the Apache License, Version 2.0 (the "License");

#include "ortools/sat/runtime_progress.h"

#include <chrono>
#include <cstdio>
#include <utility>

#include "absl/strings/str_cat.h"

namespace operations_research {
namespace sat {

int64_t RuntimeProgressNowNanos() {
  return std::chrono::duration_cast<std::chrono::nanoseconds>(
             std::chrono::steady_clock::now().time_since_epoch())
      .count();
}

namespace {
int64_t RuntimeProgressWallNanos() {
  return std::chrono::duration_cast<std::chrono::nanoseconds>(
             std::chrono::system_clock::now().time_since_epoch())
      .count();
}
}  // namespace

void RuntimeProgressPrint(const std::string& line) {
  std::fwrite(line.data(), 1, line.size(), stdout);
  std::fflush(stdout);
}

RuntimeProgressStage::RuntimeProgressStage(bool enabled, std::string owner,
                                           std::string phase,
                                           std::string operation)
    : enabled_(enabled),
      owner_(std::move(owner)),
      phase_(std::move(phase)),
      operation_(std::move(operation)),
      started_ns_(enabled ? RuntimeProgressNowNanos() : 0) {
  if (enabled_) {
    RuntimeProgressPrint(absl::StrCat(
        "CP-SAT-RUNTIME event=START owner=", owner_, " phase=", phase_,
        " operation=", operation_, " monotonic_ns=", started_ns_,
        " wall_time_ns=", RuntimeProgressWallNanos(), "\n"));
  }
}

RuntimeProgressStage::~RuntimeProgressStage() {
  if (!enabled_) return;
  const int64_t elapsed_ns = RuntimeProgressNowNanos() - started_ns_;
  RuntimeProgressPrint(absl::StrCat(
      "CP-SAT-RUNTIME event=END owner=", owner_, " phase=", phase_,
      " operation=", operation_, " elapsed_ns=", elapsed_ns, "\n"));
}

}  // namespace sat
}  // namespace operations_research
