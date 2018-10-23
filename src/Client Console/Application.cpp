// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "..\Service\pch.hpp"

#include "Application.hpp"
#include "..\Network\TCP\TCPClient.hpp"
#include "..\Network\Protocols\CommandMessageProtocol.hpp"
#include "..\Server\CommandProperties.hpp"
#include "..\Service\Debugger.hpp"
#include "..\Network\UDP\UDPClient.hpp"

Application::Application() :
	m_io{ },
	m_tcp_client{ new TCPClient{ m_io, boost::asio::ip::tcp::resolver(m_io).resolve(SERVER_IP, DEFAULT_PORT) } },
	m_udp_client{ new UDPClient{ m_io, boost::asio::ip::udp::resolver(m_io).resolve(SERVER_IP, DEFAULT_PORT) } },
	m_thread{ [this]() { m_io.run(); } }
{ }

Application::Application(char *argv[]) :
	m_io{ },
	m_tcp_client{ new TCPClient{ m_io, boost::asio::ip::tcp::resolver(m_io).resolve(argv[1], argv[2]) } },
	m_udp_client{ new UDPClient{ m_io, boost::asio::ip::udp::resolver(m_io).resolve(argv[1], argv[2]) } },
	m_thread{ [this]() { m_io.run(); } }
{ }

Application::Application(std::string_view ip, std::string_view port) :
	m_io{ },
	m_tcp_client{ new TCPClient{ m_io, boost::asio::ip::tcp::resolver(m_io).resolve(ip, port) } },
	m_udp_client{ new UDPClient{ m_io, boost::asio::ip::udp::resolver(m_io).resolve(ip, port) } },
	m_thread{ [this]() { m_io.run(); } }
{ }

Application::~Application()
{ }

void Application::run()
{
	std::string command;
	while (std::getline(std::cin, command))
		send_command(command);
}

void Application::send_command(std::string_view command)
{
	static CMPROTO msg;
	msg.clear_data();

	size_t separator_pos = command.find_first_of(' ');
	if (separator_pos == std::string::npos)
		separator_pos = command.length();

	auto cmd_line = command.substr(0, separator_pos);
	auto args     = command.substr(separator_pos);
	if (cmd_line == args)
		args = "";

	msg.set_body_length(CMPROTO::COMMAND_LENGTH + (args.empty() ? 0 : CMPROTO::SPACE_LENGTH + args.length()));
	if (auto iter = std::find_if(std::begin(COMMAND_PROPERTIES), std::end(COMMAND_PROPERTIES), [&cmd_line](const auto &prop) { return (cmd_line == std::get<1>(prop.command)); }); iter != std::end(COMMAND_PROPERTIES))
	{	
		// Translate command
		char buff[CMPROTO::COMMAND_LENGTH + 1]{ };
		int cmd = static_cast<int>(std::get<Commands>(iter->command));
		sprintf_s(buff, "%2d", cmd);

		// Copy full command 
		std::memcpy(msg.get_body(), buff, CMPROTO::COMMAND_LENGTH);
		std::memcpy(msg.get_args(), args.data(), CMPROTO::MAX_ARGS_LENGTH);

		msg.encode_header();

		if (iter->exec_func.index() == 0)
			m_tcp_client->write(&msg);
		else
			m_udp_client->send(&msg);
	}
	else
		$ERROR(TEXTH("Wrong Command: '%s'\n"), command.data());
}

void Application::close()
{
	m_tcp_client->close();
	m_thread.join();
}
