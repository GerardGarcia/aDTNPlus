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
 * FILE Logger.h
 * AUTHOR Blackcatn13
 * DATE Jul 1, 2015
 * VERSION 1
 * This file contains the Logger class.
 */
#ifndef BUNDLEAGENT_UTILS_LOGGER_H_
#define BUNDLEAGENT_UTILS_LOGGER_H_

#ifndef MAX_LOG_LEVEL
#define MAX_LOG_LEVEL 100
#endif

#include <cstring>
#include <fstream>
#include <string>
#include <mutex>
#include <chrono>
#include "Utils/Logstream.h"
#include "Utils/ConfigLoader.h"

using std::chrono::time_point;
using std::chrono::system_clock;
using std::chrono::duration;

#define INIT_CHRONO() std::chrono::time_point<std::chrono::system_clock> start, end; 
#define START_CHRONO() start = std::chrono::system_clock::now()
#define END_CHRONO() std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now()-start 
#define GET_CHRONO_SECS() elapsed_seconds.count()

/**
 * CLASS Logger
 * This class will be used to log the application.
 * To log something, the LOG macro is used.
 * The logger uses 2 types of levels.
 * A compiler time level MAX_LOG_LEVEL, and a execution time m_logLevel.
 * This levels go from 1 to 100.
 *
 * The distribution of the levels is as follows:
 *
 * 1 : ERROR
 * 2 - 5 : WARNING
 * 6 - 21 : INFO
 * 22 - 100 : DEBUG
 *
 * This levels will be used for the application as follows
 * Utils logs : WARNING 5, INFO 18-21, DEBUG 71-80
 * NeighbourDiscovery logs : WARNING 4, INFO 14-17, DEBUG 61-70
 * Bundle logs : WARNING 3, INFO 10-13, DEBUG 31-40
 * BundleSenderReceiver logs : WARNING 3, INFO 10-11, DEBUG 41-50
 * BundleProcessor logs : WARNING 3, INFO 12-13, DEBUG 51-60
 * Node logs : WARNING 2, INFO 6-9, DEBUG 22-30
 */
class Logger {
 public:
  /**
   * Destructor of the class
   */
  virtual ~Logger();
  /**
   * @brief Function to add a log.
   *
   * This function will add a timestamp and the type label to the log.
   *
   * @param level of the log to add.
   * @param message to log.
   */
  void log(int level, std::string message);
  /**
   * Function to get the current log level.
   * @return The current log level.
   */
  int logLevel();
  /**
   * Function to set a new log level.
   * @param level the new level to set.
   */
  void setLogLevel(int level);
  /**
   * Function to get the instance of the logger.
   * @return an instance to the logger.
   */
  static Logger* getInstance();
  /**
   * Operator to get a Logstream to put the log.
   *
   * @param level of the log.
   * @return a Logstream to add the log.
   */
  Logstream operator()(int level);
  /**
   * @brief Function to set the configuration and start the Logger.
   *
   * This functions sets the file to save the logs.
   *
   * @param filename File to save to logs.
   */
  void setLoggerConfigAndStart(std::string filename);

 private:
  /**
   * Constructor of the class.
   */
  Logger();
  /**
   * Instance of the logger.
   */
  static Logger* m_instance;
  /**
   * Stream to save the logs.
   */
  std::ofstream os;
  /**
   * Current level of log.
   */
  int m_logLevel;
  /**
   * Mutex for the stringstream.
   */
  std::mutex m_mutex;
  /**
   * File to save the logs.
   */
  std::string m_filename;
};

/**
 * Macro to get only the name of the file.
 */
#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__

/**
 * Macro to get a Logstream, and add to it the file name and the line
 * that generate the log.
 */
#define LOG(level)                                          \
  if (level > MAX_LOG_LEVEL) ;                              \
  else if (level > Logger::getInstance()->logLevel()) ;     \
  else                                                      \
    Logger::getInstance()->operator()(level) << "[" <<      \
        std::string(_FILE) << ":" << __LINE__ << "] - "

#endif  // BUNDLEAGENT_UTILS_LOGGER_H_
