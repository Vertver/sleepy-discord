#pragma once
#include <uWS/uWS.h>
#ifndef NONEXISTENT_UWEBSOCKETS
#include <thread>
#include "client.h"

namespace SleepyDiscord {
	typedef uWS::WebSocket<uWS::CLIENT>* WebsocketConnection;

	class UWebSocketsDiscordClient : public BaseDiscordClient {
	public:
		UWebSocketsDiscordClient() : maxNumOfThreads(0) {}
		UWebSocketsDiscordClient(const std::string token, const char numOfThreads = 3);
		~UWebSocketsDiscordClient();
		void run();
		Timer schedule(std::function<void()> code, const time_t milliseconds);
	protected:
#include "standard_config_header.h"
	private:
		uWS::Hub hub;
		bool connect(const std::string & uri, GenericMessageReceiver* messageProcessor, WebsocketConnection* connection);
		void disconnect(unsigned int code, const std::string reason, WebsocketConnection* connection);
		void send(std::string message, WebsocketConnection* connection);
		void runAsync();
		uWS::WebSocket<uWS::CLIENT>* theClient;
		std::thread thread;
		const char maxNumOfThreads;
		bool isConnectionBad;
		SLEEPY_LOCK_CLIENT_FUNCTIONS
	};

	typedef UWebSocketsDiscordClient DiscordClient;
}
#endif