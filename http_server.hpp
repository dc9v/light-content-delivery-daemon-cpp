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

using namespace boost;

/**
 * LightContentsDelivery HTTP Server
 *
 * @author TAEGYUN,KO <taegyun.ko@weinwork.com>
 * @date 2021-09-21
 */

namespace LightContentsDelivery {

typedef boost::asio::detail::socket_type SocketType;
typedef boost::asio::ip::tcp::socket Socket;

template <class SocketType> class HTTPServerBase;

class Request;
class Response;
class Content;

std::shared_ptr<boost::asio::io_service> ioService;
std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;
std::vector<std::thread> thread;

class Configure {
	public:
	int port;
	std::string address;

	int threadPoolSize = 10;
	int timeoutRequest = 10;
	int timeoutContent = 50;

	Configure(int _port) { port = _port; }
};

template <SocketType> class HTTPServerBase {
	public:
	Configure configure;
	HTTPServerBase() { }
	virtual ~HTTPServerBase() { }

	std::shared_ptr<boost::asio::io_service> ioService;
	std::unique_ptr<boost::asio::ip::tcp::acceptor> acceptor;

	virtual void listen()
	{
		boost::asio::ip::tcp::endpoint endPoint;

		if (!ioService) {
			ioService = std::make_shared<boost::asio::io_service>();
		}

		if (ioService->stopped()) {
			ioService->reset();
		}

		if (configure.address.size() > 0) {
			endPoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(configure.address), configure.port);
		} else {
			endPoint = boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), configure.port);
		}

		if (!acceptor) {
			acceptor = std::unique_ptr<boost::asio::ip::tcp::acceptor>(new boost::asio::ip::tcp::acceptor(*ioService));
		}

		acceptor->open(endPoint.protocol());
		acceptor->set_option(boost::asio::socket_base::reuse_address(true));
		acceptor->bind(endPoint);
		acceptor->listen();
	};

	class Content : std::istream {
		private:
		boost::asio::streambuf& streamBuffer;

		public:
		Content() { }
	};

	class Request {
		private:
		boost::asio::streambuf streamBuffer;
	};

	class Response : std::ostream {
		private:
		boost::asio::streambuf streamBuffer;

		public:
		Response() { }
	};

	protected:
	void requestRead() { }
	void requesrParse() { }
	void response() { }

	void accept()
	{
		auto socket = std::make_shared<Socket>(*ioService);

		acceptor->async_accept(*socket, [this, socket](const boost::system::error_code& errorCode) {
			if (errorCode) {
				onError(std::shared_ptr<Request>(new Request(*socket)), errorCode);
			} else {
				boost::asio::ip::tcp::no_delay option(true);
				socket->set_option(option);
				this->read_request_and_content(socket);
			}
		});
	};
};

template <> class HTTPServer<class Socket> : public HTTPServerBase<SocketType> {
	public:
	HTTPServer()
			: HTTPServerBase<Socket>::ServerBase(80)
	{
		/* read config file - yaml type	*/
	}

	HTTPServer(int _port, int _threadPoolSize = 1, int _timeoutRequest = 5, int _timeoutContent = 300)
			: HTTPServerBase<Socket>::ServerBase(80)
	{
		configure.port = _port;
		configure.threadPoolSize = _threadPoolSize;
		configure.timeoutRequest = _timeoutRequest;
		configure.timeoutContent = _timeoutContent;
	}

	protected:
	void accept()
	{
		// ...->async();
	}
};
}