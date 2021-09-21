#include <boost/algorithm/string/predicate.hpp>
#include <boost/asio.hpp>
#include <boost/functional/hash.hpp>
#include <boost/regex/v5/regex.hpp>

#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <thread>
#include <unordered_map>

/**
 * LightContentsDelivery HTTP Server
 *
 * @author TAEGYUN,KO <taegyun.ko@weinwork.com>
 * @date 2021-09-21
 */

namespace LightContentsDelivery
{
static const int DEFAULT_PORT = 9099;
static const int DEFAULT_THREAD_POOL_SIZE = 10;
static const int DEFAULT_TIME_OUT_REQUEST = 30;
static const int DEFAULT_TIME_OUT_CONTENT = 30;

typedef boost::asio::ip::tcp::socket Socket;
typedef boost::asio::detail::socket_type SocketType;

class HTTPServer;
class HTTPServerBase;

std::shared_ptr<boost::asio::io_service> ioService;
std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;
std::vector<std::thread> threadPool;

class Configure
{
  public:
    std::string address = "";
    int port = LightContentsDelivery::DEFAULT_PORT;
    int threadPoolSize = LightContentsDelivery::DEFAULT_THREAD_POOL_SIZE;
    int timeoutRequest = LightContentsDelivery::DEFAULT_TIME_OUT_REQUEST;
    int timeoutContent = LightContentsDelivery::DEFAULT_TIME_OUT_CONTENT;
};

class HTTPServerBase
{
    std::shared_ptr<boost::asio::io_service> ioService;
    std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;
    class Content;
    class Request;
    class Response;

    void onError(std::shared_ptr<typename HTTPServerBase::Request> request, boost::system::error_code &errorCode)
    {
        ;
    }

    class Content : public std::istream
    {
      private:
        boost::asio::streambuf &streamBuffer;

      public:
        Content(boost::asio::streambuf &streamBuffer) : std::istream(&streamBuffer), streamBuffer(streamBuffer)
        {
        }
    };

    class Request
    {
      private:
        Content content;
        boost::asio::streambuf streamBuffer;

      public:
        Request(const Socket &socket) : content(streamBuffer)
        {
        }
    };

    class Response : std::ostream
    {
      private:
        boost::asio::streambuf streamBuffer;

      public:
        Response(const Socket &socket)
        {
        }
    };

  public:
    Configure configure;
    virtual void listen()
    {
        boost::asio::ip::tcp::endpoint endPoint;

        if (!ioService)
        {
            ioService = std::make_shared<boost::asio::io_service>();
        }

        if (ioService->stopped())
        {
            ioService->reset();
        }

        if (configure.address.size() > 0)
        {
            endPoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(configure.address), configure.port);
        }
        else
        {
            endPoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), configure.port);
        }

        if (!acceptor)
        {
            acceptor = std::unique_ptr<boost::asio::ip::tcp::acceptor>(new boost::asio::ip::tcp::acceptor(*ioService));
        }

        acceptor->open(endPoint.protocol());
        acceptor->set_option(boost::asio::socket_base::reuse_address(true));
        acceptor->bind(endPoint);
        acceptor->listen();

        accept();
        threadPool.clear();

        for (int c = 1; c < configure.threadPoolSize; c++)
        {
            threadPool.emplace_back([this]() { ioService->run(); });
        }

        for (std::thread &t : threadPool)
        {
            t.join();
        }

        ioService->run();
    };

  protected:
    void requestGet(const std::shared_ptr<Socket> &socket)
    {
    }
    void requesrParse()
    {
    }
    void response()
    {
    }

    virtual void accept()
    {
        auto socket = std::make_shared<Socket>(*ioService);

        acceptor->async_accept(*socket, [this, socket](boost::system::error_code &errorCode) {
            if (errorCode)
            {
                onError(std::shared_ptr<Request>(new Request(*socket)), errorCode);
            }
            else
            {
                boost::asio::ip::tcp::no_delay option(true);

                socket->set_option(option);
                this->requestGet(socket);
            }
        });
    };
};

class HTTPServer : public HTTPServerBase
{
  public:
    HTTPServer(int port = LightContentsDelivery::DEFAULT_PORT, int threadPoolSize = LightContentsDelivery::DEFAULT_THREAD_POOL_SIZE, int timeoutRequest = LightContentsDelivery::DEFAULT_TIME_OUT_REQUEST, int timeoutContent = LightContentsDelivery::DEFAULT_TIME_OUT_CONTENT)
    {
        configure.port = port;
        configure.threadPoolSize = threadPoolSize;
        configure.timeoutRequest = timeoutRequest;
        configure.timeoutContent = timeoutContent;

        HTTPServerBase::listen();
    }

  protected:
    void accept()
    {
        // ...->async();
    }
};
} // namespace LightContentsDelivery