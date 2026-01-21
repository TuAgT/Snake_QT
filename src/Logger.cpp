#include "../include/Logger.h"
#include <QStandardPaths>
#include <QCoreApplication>

Logger::Logger() 
    : m_logLevel(LogLevel::INFO)
    , m_consoleOutput(true)
    , m_logFile(nullptr)
    , m_logStream(nullptr)
{
    // 默认日志文件路径设置为应用程序目录下的logs文件夹
    QDir logDir(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/logs");
    if (!logDir.exists()) {
        logDir.mkpath(".");
    }
    
    QString fileName = QString("app_%1.log").arg(QDateTime::currentDateTime().toString("yyyyMMdd"));
    m_logFilePath = logDir.filePath(fileName);
    
    // 尝试打开日志文件
    m_logFile = new QFile(m_logFilePath);
    if (m_logFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        m_logStream = new QTextStream(m_logFile);
    } else {
        // 如果无法创建日志文件，则回退到控制台输出
        delete m_logFile;
        m_logFile = nullptr;
        m_logStream = nullptr;
    }
}

Logger::~Logger() {
    if (m_logStream) {
        delete m_logStream;
        m_logStream = nullptr;
    }
    if (m_logFile) {
        m_logFile->close();
        delete m_logFile;
        m_logFile = nullptr;
    }
}

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setLogLevel(LogLevel level) {
    QMutexLocker locker(&m_mutex);
    m_logLevel = level;
}

void Logger::setLogFile(const QString& filePath) {
    QMutexLocker locker(&m_mutex);
    
    // 关闭当前日志文件
    if (m_logStream) {
        delete m_logStream;
        m_logStream = nullptr;
    }
    if (m_logFile) {
        m_logFile->close();
        delete m_logFile;
        m_logFile = nullptr;
    }
    
    // 打开新日志文件
    m_logFilePath = filePath;
    m_logFile = new QFile(filePath);
    if (m_logFile->open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        m_logStream = new QTextStream(m_logFile);
    } else {
        delete m_logFile;
        m_logFile = nullptr;
        m_logStream = nullptr;
    }
}

void Logger::setConsoleOutput(bool enabled) {
    QMutexLocker locker(&m_mutex);
    m_consoleOutput = enabled;
}

void Logger::log(LogLevel level, const QString& message) {
    QMutexLocker locker(&m_mutex);
    
    // 检查日志级别
    if (level < m_logLevel) {
        return;
    }
    
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
    QString levelStr = levelToString(level);
    QString fullMessage = QString("[%1] [%2] %3").arg(timestamp).arg(levelStr).arg(message);
    
    // 输出到控制台
    if (m_consoleOutput) {
        std::cout << fullMessage.toStdString() << std::endl;
    }
    
    // 输出到文件
    if (m_logFile && m_logStream) {
        (*m_logStream) << fullMessage << Qt::endl;
        m_logStream->flush();
    }
}

void Logger::debug(const QString& message) {
    log(LogLevel::DEBUG, message);
}

void Logger::info(const QString& message) {
    log(LogLevel::INFO, message);
}

void Logger::warn(const QString& message) {
    log(LogLevel::WARN, message);
}

void Logger::error(const QString& message) {
    log(LogLevel::ERROR, message);
}

QString Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::DEBUG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARN: return "WARN";
        case LogLevel::ERROR: return "ERROR";
        default: return "UNKNOWN";
    }
}