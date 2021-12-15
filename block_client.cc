/*
 *
 * Copyright 2015 gRPC authors.
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

#include <iostream>
#include <memory>
#include <string>
#include <future>

#include <grpcpp/grpcpp.h>

#include "block_event_v1.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using eratos::blocks::BlockEventV1;
using eratos::blocks::RegisterBlockReply;
using eratos::blocks::RegisterBlockRequest;

class BlockEventV1Client {
 public:
  BlockEventV1Client  (std::shared_ptr<Channel> channel)
      : stub_(BlockEventV1::NewStub(channel)) {}

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string RegisterBlockEvent(const std::string& user) {
    // Data we are sending to the server.
    RegisterBlockRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    RegisterBlockReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->RegisterBlockEvent(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string LogBlockEvent(const std::string& user) {
    // Data we are sending to the server.
    RegisterBlockRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    RegisterBlockReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->LogBlockEvent(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

  // Assembles the client's payload, sends it and presents the response back
  // from the server.
  std::string ReportBlockEvent(const std::string& user) {
    // Data we are sending to the server.
    RegisterBlockRequest request;
    request.set_name(user);

    // Container for the data we expect from the server.
    RegisterBlockReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->ReportBlockEvent(&context, request, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.message();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }


 private:
  std::unique_ptr<BlockEventV1::Stub> stub_;
};

std::string callLogBlockEvent(const std::string& user)
{
  std::string target_str= "localhost:50051";
    BlockEventV1Client blockclient(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

  auto reply = blockclient.LogBlockEvent(user);
  std::cout << "in callLogBlockEvent Client received: " << reply << std::endl;
  return reply;
}

std::string callRegisterBlockEvent(const std::string& user)
{
  std::string target_str= "localhost:50051";
    BlockEventV1Client blockclient(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

  auto reply = blockclient.RegisterBlockEvent(user);
  std::cout << "in callRegisterBlockEvent, Client received: " << reply << std::endl;
  return reply;
}

std::string callReportBlockEvent(const std::string& user)
{
  std::string target_str= "localhost:50051";
    BlockEventV1Client blockclient(
      grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()));

  auto reply = blockclient.ReportBlockEvent(user);
  std::cout << "in callReportBlockEvent, Client received: " << reply << std::endl;
  return reply;
}

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint specified by
  // the argument "--target=" which is the only expected argument.
  // We indicate that the channel isn't authenticated (use of
  // InsecureChannelCredentials()).
  // std::string target_str= "localhost:50051";
  // std::string arg_str("--target");
  // if (argc > 1) {
  //   std::string arg_val = argv[1];
  //   size_t start_pos = arg_val.find(arg_str);
  //   if (start_pos != std::string::npos) {
  //     start_pos += arg_str.size();
  //     if (arg_val[start_pos] == '=') {
  //       target_str = arg_val.substr(start_pos + 1);
  //     } else {
  //       std::cout << "The only correct argument syntax is --target="
  //                 << std::endl;
  //       return 0;
  //     }
  //   } else {
  //     std::cout << "The only acceptable argument is --target=" << std::endl;
  //     return 0;
  //   }
  // } 

  std::string user("client block");
  auto f1 = std::async(std::launch::async, callLogBlockEvent, user);

  auto f2 = std::async(std::launch::async, callRegisterBlockEvent, user);

  auto f3 = std::async(std::launch::async, callReportBlockEvent, user);

  std::cout << f2.get() << '\n';
  std::cout << f1.get() << '\n';
  std::cout << f3.get() << '\n';

  return 0;
}
