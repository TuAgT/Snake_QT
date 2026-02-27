#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QMutex>
#include <QDir>

// 日志级别枚举
enum class LogLevel {
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3
};

// 日志记录器类
class Logger {
public:
    // 获取单例实例
    static Logger &getInstance();

    // 设置日志级别
    void setLogLevel(LogLevel level);

    // 设置日志文件路径
    void setLogFile(const QString &filePath);

    // 设置是否输出到控制台
    void setConsoleOutput(bool enabled);

    // 记录日志消息
    void log(LogLevel level, const QString &message);

    // 各种级别的便捷方法
    void debug(const QString &message);

    void info(const QString &message);

    void warn(const QString &message);

    void error(const QString &message);

private:
    Logger(); // 私有构造函数用于单例模式
    ~Logger();

    // 获取日志级别字符串
    QString levelToString(LogLevel level);

    LogLevel m_logLevel;
    QString m_logFilePath;
    bool m_consoleOutput;
    QMutex m_mutex;
    QFile *m_logFile;
    QTextStream *m_logStream;
};

// 宏定义，方便使用日志功能
#define LOG_DEBUG(msg) Logger::getInstance().debug(QString("[%1:%2] %3").arg(__FILE__).arg(__LINE__).arg(msg))
#define LOG_INFO(msg) Logger::getInstance().info(QString("[%1:%2] %3").arg(__FILE__).arg(__LINE__).arg(msg))
#define LOG_WARN(msg) Logger::getInstance().warn(QString("[%1:%2] %3").arg(__FILE__).arg(__LINE__).arg(msg))
#define LOG_ERROR(msg) Logger::getInstance().error(QString("[%1:%2] %3").arg(__FILE__).arg(__LINE__).arg(msg))

#endif // LOGGER_H
