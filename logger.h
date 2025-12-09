
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <string>

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::mutex init_mtx;
    static std::mutex write_mtx;
    std::ofstream logFile;

public:
    Logger(const std::string& filename = "Test/output2.txt") {//생성자
        logFile.open(filename, std::ios::trunc);
        logFile << "[Init] Logger started." << std::endl;
    }
    ~Logger() {//소멸자
        if (logFile.is_open()) {
            logFile << "[Shutdown] Logger closed." << std::endl;
            logFile.close();
        }
    }
    static Logger* getInstance(const std::string& filename = "Test/output2.txt") {
        std::lock_guard<std::mutex> lock(init_mtx);
        if (!instance) {
            instance = std::make_unique<Logger>(filename);//인스턴스 최초 생성
        }
        return instance.get();//인스턴스 반환
    }

    void log(const std::string& message) {
        /* TODO */
        std::lock_guard<std::mutex> lock(write_mtx);//동기화
        logFile << message << std::endl;//로그 작성
    }

};

std::unique_ptr<Logger> Logger::instance;
std::mutex Logger::init_mtx;
std::mutex Logger::write_mtx;

