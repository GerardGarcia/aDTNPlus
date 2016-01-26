/*
 * Copyright (c) 2016 SeNDA
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
 * FILE receiver.cpp
 * AUTHOR Blackcatn13
 * DATE Jan 22, 2016
 * VERSION 1
 *
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <getopt.h>
#include <string>
#include <iostream>
#include <cstring>

static void help(std::string program_name) {
  std::cout
      << program_name << " is part of the SeNDA aDTNPlus platform\n"
      << "Usage: " << program_name << " -i '127.0.0.1' -p '50000' -a '50'\n"
      << "Required options:\n"
      << "   [-i | --listeningIP] Ip\t\t\tIP of the listening node.\n"
      << "   [-p | --port] port\t\t\tPort where the node is listening.\n"
      << "   [-a | --appId] ApplicationID\t\t\tWhat appId we want to listen.\n"
      << "Supported options:\n"
      << "   [-h | --help]\t\t\t\tShows this help message.\n" << std::endl;
}

int main(int argc, char **argv) {
  int opt = -1, option_index = 0;
  std::string ip = "";
  int port = -1;
  int appId = -1;

  static struct option long_options[] = {
      { "listeningIP", required_argument, 0, 'i' },
      { "port", required_argument, 0, 'p' },
      { "appId", required_argument, 0, 'a' },
      { "help", no_argument, 0, 'h' },
      { 0, 0, 0, 0 }
  };

  while ((opt = getopt_long(argc, argv, "i:p:a:h", long_options,
                            &option_index))) {
    switch (opt) {
      case 'i':
        ip = std::string(optarg);
        break;
      case 'p':
        port = std::atoi(optarg);
        break;
      case 'a':
        appId = std::atoi(optarg);
        break;
      case 'h':
        help(std::string(argv[0]));
        exit(0);
      default:
        break;
    }
    if (opt == -1)
      break;
  }
  if (ip == "" || port == -1 || appId == -1) {
    help(std::string(argv[0]));
    exit(0);
  }
  sockaddr_in remoteAddr = { 0 };
  remoteAddr.sin_family = AF_INET;
  remoteAddr.sin_port = htons(port);
  remoteAddr.sin_addr.s_addr = inet_addr(ip.c_str());
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    std::cout << "Cannot create socket, reason: " << strerror(errno)
              << std::endl;
  } else {
    if (connect(sock, reinterpret_cast<sockaddr*>(&remoteAddr),
                sizeof(remoteAddr)) < 0) {
      std::cout << "Cannot connect with node, reason: " << strerror(errno)
                << std::endl;
    } else {
      uint8_t type = htons(0);
      uint32_t appIdn = htonl(appId);
      int writed = send(sock, &type, sizeof(type), 0);
      if (writed < 0) {
        std::cout << "Cannot write to socket, reason: " << strerror(errno)
                  << std::endl;
      } else {
        writed = send(sock, &appIdn, sizeof(appIdn), 0);
        if (writed < 0) {
          std::cout << "Cannot write to socket, reason: " << strerror(errno)
                    << std::endl;
        } else {
          while (true) {
            int payloadSize = 0;
            int receivedSize = recv(sock, &payloadSize, sizeof(payloadSize),
                                        0);
            char* payloadraw = new char[payloadSize];
            int receivedLength = 0;
            while (receivedLength != payloadSize) {
              receivedSize = recv(sock, payloadraw + receivedLength,
                                  payloadSize - receivedLength, 0);
              receivedLength += receivedSize;
            }
            std::string payload = std::string(payloadraw, payloadSize);
            std::cout << "Payload received: " << payload << std::endl;
          }
        }
      }
    }
    close(sock);
  }
  return 0;
}
