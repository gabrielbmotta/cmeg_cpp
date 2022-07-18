#ifndef NETWORKING_TCPSOCKET_HPP
#define NETWORKING_TCPSOCKET_HPP

#if defined __linux__ || defined __APPLE__
#include <netinet/in.h>
#elif defined _WIN32
  static_assert(false, "Sorry, windows not yey supported.")
#endif

#include <string>

class TCPSocket
{
public:
  TCPSocket();
  ~TCPSocket();

  void connect(const char* addr, unsigned short int port);
  void connect(std::string addr, unsigned short int port);
  void disconnect();
  bool isConnected() const;

  void send(const std::string& msg);
  void send(const char* msg);
  void send(const char* msg, size_t size);
  void send(const void* msg, size_t size);

  std::string receive_blocking();
  //todo: create non-blocking receive function

private:
  void setAddressAndPort(const char* addr, unsigned short int port);
#if defined __linux__ || defined __APPLE__
  void setPOSIXSocketAddress();
#elif defined _WIN32
#endif

  std::string mAddress;
  unsigned short int mPort;
  int mSocketId;
  bool mIsConnected;
  const unsigned long int mReceivingBufferSize;
  sockaddr_in mServerAddress;
};

#endif

