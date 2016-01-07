#pragma once
#include <boost/logic/tribool.hpp>
#include <string>
#include "WebsocketPush.h"
#include "request.hpp"
#include "reply.hpp"

namespace http {
	namespace server {

		enum opcodes {
			opcode_continuation = 0x00,
			opcode_text = 0x01,
			opcode_binary = 0x02,
			opcode_close = 0x08,
			opcode_ping = 0x09,
			opcode_pong = 0x0a
		};

		class connection;
		class cWebem;

		class CWebsocket {
		public:
			CWebsocket(connection *pConn, cWebem *pWebEm);
			~CWebsocket();
			boost::tribool parse(const unsigned char *begin, size_t size, size_t &bytes_consumed, bool &keep_alive);
			void SendClose(const std::string &packet_data);
			void SendPing();
			void store_session_id(const request &req, const reply &rep);
			void OnDeviceChanged(const unsigned long long DeviceRowIdx);
		private:
			void OnReceiveText(const std::string &packet_data);
			void OnReceiveBinary(const std::string &packet_data);
			void OnPong(const std::string &packet_data);
			void SendPong(const std::string &packet_data);
			std::string packet_data;
			bool start_new_packet;
			opcodes last_opcode;
			connection *conn;
			const char *OUR_PING_ID = "fd";
			std::string sessionid;
			cWebem* myWebem;
			CWebSocketPush m_Push;
		};

	}
}