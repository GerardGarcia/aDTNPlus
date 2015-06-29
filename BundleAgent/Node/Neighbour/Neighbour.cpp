/*
 * Copyright (c) 2015 SeNDA
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
 *
 */
/**
 * FILE Neighbour.cpp
 * AUTHOR Blackcatn13
 * DATE Jun 29, 2015
 * VERSION 1
 *
 */

#include "Neighbour.h"
#include <string>
#include <cstdint>
#include <chrono>

Neighbour::Neighbour(const std::string &nodeId, const std::string &nodeAddress,
                     const uint16_t &nodePort)
    : m_nodeId(nodeId),
      m_nodeAddress(nodeAddress),
      m_nodePort(nodePort),
      m_lastActivity(std::chrono::steady_clock::now()) {
}

Neighbour::~Neighbour() {
}

int Neighbour::getElapsedActivityTime() {
  std::chrono::nanoseconds now = std::chrono::steady_clock::now()
      - m_lastActivity;
  return now.count() * std::chrono::nanoseconds::period::num
      / std::chrono::nanoseconds::period::den;
}

void Neighbour::Update() {
  m_lastActivity = std::chrono::steady_clock::now();
}

