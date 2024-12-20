#include "Server.hpp"

#include <ArgoDraft/ArgoLogger.hpp>

Server::Server() {
    host = "127.0.0.1";

    logger.SetFileLogLevel(ArgoDraft::LogLevel::INFO);
    logger.SetConsoleLogLevel(ArgoDraft::LogLevel::INFO);

    logger.LogMessage("Server starting on default port 9876", ArgoDraft::LogLevel::INFO);

    Run();
}

Server::Server(const int port) {
    this->port = port;
    host = "127.0.0.1";

    logger.SetFileLogLevel(ArgoDraft::LogLevel::INFO);
    logger.SetConsoleLogLevel(ArgoDraft::LogLevel::INFO);

    logger.LogMessage(("Server starting on port " + std::to_string(port)).c_str(), ArgoDraft::LogLevel::INFO);

    Run();
}

Server::Server(const int port, const std::string &host) {
    this->port = port;
    this->host = host;

    logger.SetFileLogLevel(ArgoDraft::LogLevel::INFO);
    logger.SetConsoleLogLevel(ArgoDraft::LogLevel::INFO);

    logger.LogMessage(("Server starting on port " + std::to_string(port) + " with host " + host).c_str(),
                            ArgoDraft::LogLevel::INFO);

    Run();
}

Server::Server(const int port, const std::string &host, const int maxConnections, const int maxClients) {
    this->port = port;
    this->host = host;
    this->maxConnections = maxConnections;
    this->maxClients = maxClients;

    logger.SetFileLogLevel(ArgoDraft::LogLevel::INFO);
    logger.SetConsoleLogLevel(ArgoDraft::LogLevel::INFO);

    logger.LogMessage(
        ("Server starting on port " + std::to_string(port) + " with host " + host + " with max connections " +
         std::to_string(maxConnections) + " and max clients " + std::to_string(maxClients)).c_str(),
        ArgoDraft::LogLevel::INFO);

    Run();
}

Server::Server(const int port, const std::string &host, const int maxConnections, const int maxClients,
               const int bufferSize) {
    this->port = port;
    this->host = host;
    this->maxConnections = maxConnections;
    this->maxClients = maxClients;
    this->bufferSize = bufferSize;

    logger.SetFileLogLevel(ArgoDraft::LogLevel::INFO);
    logger.SetConsoleLogLevel(ArgoDraft::LogLevel::INFO);

    logger.LogMessage(
        ("Server starting on port " + std::to_string(port) + " with host " + host + " with max connections " +
         std::to_string(maxConnections) + " and max clients " + std::to_string(maxClients) + " with buffer size " +
         std::to_string(bufferSize)).c_str(), ArgoDraft::LogLevel::INFO);

    Run();
}

auto Server::CreateSocket() -> void {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        logger.LogMessage("Failed to create server socket", ArgoDraft::LogLevel::CRITICAL);
        exit(EXIT_FAILURE);
    }

    logger.LogMessage("Server socket created", ArgoDraft::LogLevel::INFO);
}

auto Server::BindSocket() const -> void {
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(host.c_str());

    if (const int bindResults = bind(serverSocket, reinterpret_cast<sockaddr *>(&serverAddress),
                                     sizeof(serverAddress));
        bindResults < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        logger.LogMessage("Failed to bind server socket", ArgoDraft::LogLevel::CRITICAL);
        exit(EXIT_FAILURE);
    }

    logger.LogMessage("Server socket bound", ArgoDraft::LogLevel::INFO);
}

auto Server::Listen() const -> void {
    // Listen for incoming connections
    if (const int listenResults = listen(serverSocket, maxConnections); listenResults < 0) {
        std::cerr << "Failed to listen for connections" << std::endl;
        logger.LogMessage("Failed to listen for connections", ArgoDraft::LogLevel::CRITICAL);
        exit(EXIT_FAILURE);
    }

    // Log the listening
    logger.LogMessage("Server listening for connections", ArgoDraft::LogLevel::INFO);
}

auto Server::Accept() -> void {
    // Create a sockaddr_in struct to hold the client address
    sockaddr_in clientAddress{};
    socklen_t clientAddressLength = sizeof(clientAddress);

    // Accept the incoming connection
    clientSocket = accept(serverSocket, reinterpret_cast<sockaddr *>(&clientAddress), &clientAddressLength);
    if (clientSocket < 0) {
        std::cerr << "Failed to accept connection" << std::endl;
        logger.LogMessage("Failed to accept connection", ArgoDraft::LogLevel::CRITICAL);
        exit(EXIT_FAILURE);
    }

    // Log the connection
    logger.LogMessage("Server accepted connection", ArgoDraft::LogLevel::INFO);
}

auto Server::Receive() const -> void {
    // If the client socket is invalid, return
    if (clientSocket < 0) {
        return;
    }

    // Loop to receive messages
    while (clientSocket > 0) {
        // Create a buffer to hold the incoming message
        char buffer[bufferSize];

        // Receive the message
        if (const int receiveResults = recv(clientSocket, buffer, bufferSize, 0); receiveResults < 0) {
            std::cerr << "Failed to receive message" << std::endl;
            logger.LogMessage("Failed to receive message", ArgoDraft::LogLevel::CRITICAL);
            exit(EXIT_FAILURE);
        }

        // Log the message
        logger.LogMessage(("Server received message: " + std::string(buffer)).c_str(), ArgoDraft::LogLevel::INFO);
    }
}

auto Server::Send() -> void {
    // If the message queue is empty, return
    if (messageQueue.empty() || clientSocket < 0) {
        return;
    }

    while (!messageQueue.empty()) {
        // Get the message from the front of the queue
        const std::string message = messageQueue.front();

        // Filter out internal commands
        if (message != "//exit" && message != "//shutdown") {
            // Send the message
            if (const int sendResults = send(clientSocket, message.c_str(), message.length(), 0); sendResults < 0) {
                std::cerr << "Failed to send message" << std::endl;
                logger.LogMessage("Failed to send message", ArgoDraft::LogLevel::CRITICAL);
                exit(EXIT_FAILURE);
            }

            // Log the message
            logger.LogMessage(("Server sent message: " + message).c_str(), ArgoDraft::LogLevel::INFO);

            // Remove the message from the queue
            messageQueue.pop();
        }

        // If the message was "//exit", close the client socket
        if (message == "//exit") {
            CloseClient();
        }

        // If the message was "//shutdown", close the server socket
        if (message == "//shutdown") {
            Close();
        }
    }
}

auto Server::Close() -> void {
    if (clientSocket > 0) {
        CloseClient();
    }

    if (serverSocket < 0) {
        return;
    }

    if (const int closeResults = close(serverSocket); closeResults < 0) {
        std::cerr << "Failed to close socket" << std::endl;
        logger.LogMessage("Failed to close server socket", ArgoDraft::LogLevel::CRITICAL);
        exit(EXIT_FAILURE);
    }

    serverSocket = 0;
    logger.LogMessage("Server socket closed", ArgoDraft::LogLevel::INFO);
}

auto Server::CloseClient() -> void {
    if (clientSocket < 0) {
        return;
    }

    if (const int closeResults = close(clientSocket); closeResults < 0) {
        std::cerr << "Server failed to close client socket" << std::endl;
        logger.LogMessage("Server failed to close client socket", ArgoDraft::LogLevel::CRITICAL);
        return;
    }

    clientSocket = 0;
    logger.LogMessage("Server client socket closed", ArgoDraft::LogLevel::INFO);
}

auto Server::Run() -> void {
    logger.LogMessage("Starting server", ArgoDraft::LogLevel::INFO);

#ifdef __WIN32__
    logger.LogMessage("Starting Windows Sockets", ArgoDraft::LogLevel::DEBUG);
    constexpr WORD versionWanted = MAKEWORD(1, 1);
    WSADATA wsaData;
    if (const int WASockResult = WSAStartup(versionWanted, &wsaData); WASockResult != 0) {
        std::cerr << "WSAStartup failed with error: " << WASockResult << std::endl;
        logger.LogMessage("Server WSAStartup failed", ArgoDraft::LogLevel::CRITICAL);
        return;
    }
    logger.LogMessage("Windows Sockets started", ArgoDraft::LogLevel::DEBUG);
#endif

    messageQueue.emplace("Server Hello!");
    messageQueue.emplace("A second message from the server.");
    messageQueue.emplace("A third message from the server.");

    // Create the server socket
    CreateSocket();
    BindSocket();

    // Listen for incoming connections
    Listen();

    // Accept incoming connections
    Accept();

    // If the client socket is valid, receive and send messages
    if (clientSocket > 0) {
        // Ideally send and receive would be in separate threads or non-blocking calls
        // For now, we'll just call them in sequence
        // The client and server should have these in opposite order for now
        Receive();
        Send();
    }

    // If all clients have disconnected, close the server socket
    // Close();

#ifdef __WIN32__
    logger.LogMessage("Cleaning up Windows Sockets", ArgoDraft::LogLevel::DEBUG);
    WSACleanup();
#endif
}
