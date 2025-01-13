#pragma once
#include "SimpleIni.h"
#include <iostream>
#include <string>

class Config {
public:
    int windowWidth;
    int windowHeight;
    std::string windowTitle;
    bool vSync;
    int fpsLimit;
    std::string logLevel;
    std::string logFile;

    bool LoadConfig(const std::string& filePath) {
        CSimpleIniA ini;
        ini.SetUnicode();  // Support Unicode characters
        SI_Error rc = ini.LoadFile(filePath.c_str());
        if (rc < 0) {
            std::cerr << "Failed to load configuration file: " << filePath << std::endl;
            return false;
        }

        // Read configuration values
        windowWidth = ini.GetLongValue("window", "width", 1280);
        windowHeight = ini.GetLongValue("window", "height", 720);
        windowTitle = ini.GetValue("window", "title", "Default Title");

        vSync = ini.GetBoolValue("graphics", "v_sync", true);
        fpsLimit = ini.GetLongValue("graphics", "fps_limit", 60);

        logLevel = ini.GetValue("logging", "log_level", "info");
        logFile = ini.GetValue("logging", "log_file", "logs/output.log");

        return true;
    }
};


