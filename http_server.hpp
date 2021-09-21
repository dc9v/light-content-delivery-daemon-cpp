#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <thread>

#include <boost/asio.hpp>
#include <boost/regex/v5/regex.hpp>

using namespace boost;


namespace LightContentsDelivery
{
	template<class boost::asio::detail::socket_type> class HTTPServer;
	template<class boost::asio::detail::socket_type> class HTTPServerBase
	{
		public:
		HTTPServerBase() {}
		virtual ~HTTPServerBase() {}

		virtual void listen() = 0;
		virtual void accept() = 0;
		void send() { }
		void goodbye() { } // close :D
		void die() { }

		class Configure
		{
			public:
			int port;
			int threadPoolSize = 10;
			int timeoutRequest = 10;
			int timeoutContent = 50;

			Configure(int _port) : port(_port) { }
		};

		class Content : public std::istream
		{
			private:
			boost::asio::streambuf& streamBuffer;

			public:
			Content() { }
		};

		class Request
		{
			private:
			boost::asio::streambuf streamBuffer;
		};

		class Response : public std::ostream
		{
			private:
			boost::asio::streambuf streamBuffer;

			public:
			Response() { }
		};

		protected:
		void requestRead() { }
		void requesrParse() { }

		void response() { }
	};

	/**
	 * LightContentsDelivery HTTP Server
	 *
	 * @author TAEGYUN,KO <kotaegyun@weinwork.com>
	 * @date 2021-09-21
	*/
	typedef boost::asio::ip::tcp::socket HTTP;
	std::shared_ptr<boost::asio::io_service> ioService;

	template<> class HTTPServer<HTTP> : public HTTPServerBase<HTTP>
	{
		public:
		HTTPServer() : HTTPServerBase<HTTP>::HTTPServerBase() { /* read config file - yaml type	*/ }
		HTTPServer(int _port) : HTTPServerBase<HTTP>::HTTPServerBase() { configure.port = _port; }
		HTTPServer(int _port, int _threadPoolSize = 1, int _timeoutRequest = 5, int _timeoutContent = 300) : HTTPServer()
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