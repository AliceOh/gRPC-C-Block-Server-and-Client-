# gRPC C++ Block Server and Client Example

## To build
$ mkdir -p cmake/build
$ pushd cmake/build
$ cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ../..
$ make -j

## To run
Terminal 1:
$ ./block_server 
Server listening on 0.0.0.0:50051

Terminal 2:
$ ./block_client 

## To update block C++ GRPC proto
1. Update proto file: ./proto/block_event_v1.proto
2. /cmake/build$make -j  ←- to generate block_event_v1.pb.cc, block_event_v1.pb.h, block_event_v1.grpc.pb.cc, block_event_v1.grpc.pb.h
3. Update server code block_server.cc, class RegisterBlockReplyServiceImpl
4. Update client code block_client.cc, class BlockEventV1Client
5. invoke this new method in main()of block_client.cc.
6. /block_grpc/cmake/build$make -j  ←- to generate exe files

Terminal 1:
$ ./block_server 
Server listening on 0.0.0.0:50051

Terminal 2:
$ ./block_client 

## Reference

You can find a complete set of instructions for building gRPC and running the
Hello World app in the [C++ Quick Start][].

[C++ Quick Start]: https://grpc.io/docs/languages/cpp/quickstart

