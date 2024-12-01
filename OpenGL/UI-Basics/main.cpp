#include <string>

#include <ArgoDraft/ArgoLogger.hpp>

#include "src/Window.hpp"

int main() {
    try {
        Window window ("UI Basics", 1024, 1024);

        while (!window.shouldClose()) {
            window.update();
        }
    }
    catch (const std::exception& e) {
        const std::string logFileName = "UI-Basics.log";
        auto logger = ArgoDraft::Logger(logFileName);
        
        logger.SetFileLogLevel(ArgoDraft::LogLevel::ERROR);
        logger.SetConsoleLogLevel(ArgoDraft::LogLevel::WARNING);
        
        logger.LogMessage(("Error: " + std::string(e.what())).c_str(), ArgoDraft::LogLevel::CRITICAL);
    }
}
