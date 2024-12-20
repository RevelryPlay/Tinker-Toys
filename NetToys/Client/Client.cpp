#include "Client.hpp"
#include <ArgoDraft/ArgoLogger.hpp>

Client::Client() {
    host = "127.0.0.1";

    logger.SetFileLogLevel(ArgoDraft::LogLevel::INFO);
    logger.SetConsoleLogLevel(ArgoDraft::LogLevel::INFO);

    logger.LogMessage("Client starting on default port 9876", ArgoDraft::LogLevel::INFO);

    Run();
}

Client::Client(const int port) {
    this->port = port;
    host = "127.0.0.1";

    logger.SetFileLogLevel(ArgoDraft::LogLevel::INFO);
    logger.SetConsoleLogLevel(ArgoDraft::LogLevel::INFO);

    logger.LogMessage(("Client starting on port " + std::to_string(port)).c_str(), ArgoDraft::LogLevel::INFO);

    Run();
}

Client::Client(const int port, const std::string &host) {
    this->port = port;
    this->host = host;

    logger.SetFileLogLevel(ArgoDraft::LogLevel::INFO);
    logger.SetConsoleLogLevel(ArgoDraft::LogLevel::INFO);

    logger.LogMessage(("Client starting on port " + std::to_string(port) + " with host " + host).c_str(),
                            ArgoDraft::LogLevel::INFO);

    Run();
}

Client::Client(const int port, const std::string &host, const int bufferSize) {
    this->port = port;
    this->host = host;
    this->bufferSize = bufferSize;

    logger.SetFileLogLevel(ArgoDraft::LogLevel::INFO);
    logger.SetConsoleLogLevel(ArgoDraft::LogLevel::INFO);

    logger.LogMessage(
        ("Client starting on port " + std::to_string(port) + " with host " + host + " with buffer size " +
         std::to_string(bufferSize)).c_str(), ArgoDraft::LogLevel::INFO);

    Run();
}

auto Client::CreateSocket() -> void {
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        logger.LogMessage("Failed to create client socket", ArgoDraft::LogLevel::CRITICAL);
        return;
    }

    logger.LogMessage("Client socket created", ArgoDraft::LogLevel::INFO);
}

auto Client::Connect() -> void {
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    serverAddress.sin_addr.s_addr = inet_addr(host.c_str());

    if (connect(clientSocket, reinterpret_cast<sockaddr *>(&serverAddress), sizeof(serverAddress)) < 0) {
        std::cerr << "Failed to connect to server" << std::endl;
        logger.LogMessage("Failed to connect to server", ArgoDraft::LogLevel::CRITICAL);
        Close();
        return;
    }

    logger.LogMessage("Client connected to server", ArgoDraft::LogLevel::INFO);
}

auto Client::Send() -> void {
    // If the message queue is empty, return
    if (messageQueue.empty() || clientSocket < 0) {
        return;
    }

    while (!messageQueue.empty()) {
        // Get the message from the front of the queue
        const std::string message = messageQueue.front();

        // Filter out internal commands
        if (message != "//exit") {
            // Send the message
            if (const int sendResults = send(clientSocket, message.c_str(), message.length(), 0); sendResults < 0) {
                std::cerr << "Failed to send message" << std::endl;
                logger.LogMessage("Failed to send message", ArgoDraft::LogLevel::CRITICAL);
                exit(EXIT_FAILURE);
            }

            // Log the message
            logger.LogMessage(("Client sent message: " + message).c_str(), ArgoDraft::LogLevel::INFO);
        }

        // If the message was "//exit", close the client socket
        if (message == "//exit") {
            Close();
        }

        // Remove the message from the queue
        messageQueue.pop();
    }
}

auto Client::Receive() const -> void {
    while (clientSocket > 0) {
        char buffer[bufferSize];
        if (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {
            std::cerr << "Client failed to receive message" << std::endl;
            logger.LogMessage("Client failed to receive message", ArgoDraft::LogLevel::CRITICAL);
            return;
        }

        logger.LogMessage(("Client received message: " + std::string(buffer)).c_str(), ArgoDraft::LogLevel::INFO);
    }
}

auto Client::Close() -> void {
    if (close(clientSocket) < 0) {
        std::cerr << "Failed to close client socket" << std::endl;
        logger.LogMessage("Failed to close client socket", ArgoDraft::LogLevel::CRITICAL);
        return;
    }

    clientSocket = 0;
    logger.LogMessage("Client socket closed", ArgoDraft::LogLevel::INFO);
}

auto Client::Run() -> void {
#ifdef __WIN32__
    logger.LogMessage("Starting Windows Sockets", ArgoDraft::LogLevel::DEBUG);
    constexpr WORD versionWanted = MAKEWORD(1, 1);
    WSADATA wsaData;
    if (const int WASockResult = WSAStartup(versionWanted, &wsaData); WASockResult != 0) {
        std::cerr << "WSAStartup failed with error: " << WASockResult << std::endl;
        logger.LogMessage("WSAStartup failed", ArgoDraft::LogLevel::CRITICAL);
        return;
    }
    logger.LogMessage("Client Windows Sockets started", ArgoDraft::LogLevel::DEBUG);
#endif

    // Add messages to the queue
    messageQueue.emplace("Client Hello!");
    messageQueue.emplace("A second message from the client.");
    messageQueue.emplace("And a third message from the client.");

    // Add an absurdly long message to the queue
    // messageQueue.emplace(
    //     "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras viverra sollicitudin commodo. Integer facilisis"
    //     " fermentum neque, sed congue tellus auctor sit amet. Sed felis massa, faucibus at mollis porttitor, fermentum "
    //     "a nulla. Pellentesque eget fringilla diam. Morbi eget congue purus, vitae facilisis felis. Praesent vitae semper "
    //     "sapien. Aenean egestas lacus mi. Integer faucibus mollis fringilla. Pellentesque felis urna, condimentum eget "
    //     "blandit quis, posuere a quam. Morbi non lacus id metus porta tristique. Praesent vitae dui id elit placerat "
    //     "pharetra eget et magna. Integer nec iaculis arcu. -- Duis et volutpat leo. Sed tempus lacus blandit arcu "
    //     "interdum suscipit. Proin a urna vitae risus vulputate condimentum vitae in dolor. Suspendisse sed malesuada "
    //     "dolor, sed tempor nisl. Quisque luctus neque velit, non dapibus turpis pulvinar eget. Lorem ipsum dolor sit "
    //     "amet, consectetur adipiscing elit. Morbi eu lectus in purus dignissim molestie ac a massa. Phasellus tincidunt, "
    //     "eros ut gravida vehicula, sem nisl elementum nibh, suscipit rhoncus libero fusce."
    // );

    messageQueue.emplace("And a final message from the client.");

    // Tell the server to close the client connection
    messageQueue.emplace("//exit");

    CreateSocket();

    Connect();

    if (clientSocket > 0) {
        // Ideally send and receive would be in separate threads or non-blocking calls
        // For now, we'll just call them in sequence
        // The client and server should have these in opposite order for now
        Send();
        Receive();
    }

    // Close the client socket
    // Close();

#ifdef __WIN32__
    // Clean up Windows Sockets
    logger.LogMessage("Cleaning up Windows Sockets", ArgoDraft::LogLevel::DEBUG);
    WSACleanup();
#endif
}
