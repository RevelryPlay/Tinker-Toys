#include <iostream>
#include <ArgoDraft/ArgoLogger.hpp>

#include "src/imguiRenderer.cpp"

int main() {
    try {
        ImguiRenderer::renderOpenGL();
    }
    catch (const std::exception& e) {
        
        const std::string logFileName = "default.log";
        const auto logger = ArgoDraft::Logger(logFileName);
        logger.LogMessage(("Error: " + std::string(e.what())).c_str(), ArgoDraft::LogLevel::CRITICAL);

        return 1;
    }

    return 0;
}
