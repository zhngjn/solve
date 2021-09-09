#include <iostream>
#include <string>
#include <chrono>
#include <time.h>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <memory>

class ILogger {
public:
    virtual ILogger& operator<<(const char* text) = 0;
    virtual std::ostream& GetStream() = 0;
    virtual void Reset() = 0;
};

class Logger : public ILogger {
public:
    Logger(std::ostream& strm)
        : strm_(strm) {}

    Logger& operator<<(const char* text) {
        strm_ << text << std::endl;
        return *this;
    }

    std::ostream& GetStream() {
        return strm_;
    }

    void Reset() {}

private:
    std::ostream& strm_;
};

class LoggerDecorator : public ILogger {
public:
    LoggerDecorator(std::shared_ptr<ILogger> logger)
        : logger_(logger) {}

    LoggerDecorator& operator<<(const char* text) {
        logger_->operator<<(text);
        return *this;
    }

    std::ostream& GetStream() {
        return logger_->GetStream();
    }

protected:
    std::shared_ptr<ILogger> logger_;
};

class TimeLoggerDecorator : public LoggerDecorator {
public:
    enum TimeFormat {
        kReset,
        kTime,
        kDateTime,
    };

public:
    TimeLoggerDecorator(std::shared_ptr<ILogger> logger, TimeFormat fmt)
        : LoggerDecorator(logger), fmt_(fmt) {}

    TimeLoggerDecorator& operator<<(const char* text) {
        GetStream() << TmToString(Now());
        LoggerDecorator::operator<<(text);
        return *this;
    }

    void Reset() { fmt_ = kReset; }

    void SetFormat(TimeFormat fmt) { fmt_ = fmt; }

private:
    std::string TmToString(const tm& time) const {
        std::stringstream strm;
        strm << std::setfill('0');
        switch (fmt_) {
        case kDateTime:
            strm << std::setw(4) << (time.tm_year + 1900) << "-"
                 << std::setw(2) << (time.tm_mon + 1) << "-"
                 << std::setw(2) << (time.tm_mday);
            strm << " ";
        case kTime:
            strm << std::setw(2) << time.tm_hour << ":"
                 << std::setw(2) << time.tm_min << ":"
                 << std::setw(2) << time.tm_sec;
            break;
        case kReset:
            break;
        default:
            break;
        }
        std::string result = strm.str();
        if (!result.empty())
            return "[" + result + "]";
        else
            return "";
    }

    static tm Now() {
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::time_t tt = std::chrono::system_clock::to_time_t(now);
        tm time;
        localtime_r(&tt, &time);
        return time;
    }

private:
    TimeFormat fmt_;
};

struct ColorLoggerDecorator : public LoggerDecorator {
public:
    enum Color {
        kReset,
        kRed,
        kGreen,
        kYellow,
        kBlue,
        kMagenta,
        kCyan,
    };

public:
    ColorLoggerDecorator(std::shared_ptr<ILogger> logger, Color color)
        : LoggerDecorator(logger), color_(color) {}

    ColorLoggerDecorator& operator<<(const char* text) {
        GetStream() << Color2String(color_);
        LoggerDecorator::operator<<(text);
        GetStream() << Color2String(kReset);
        return *this;
    }

    void Reset() { color_ = kReset; }

    void SetColor(Color color) { color_ = color; }

private:
    static std::string Color2String(Color color) {
        static std::unordered_map<Color, std::string> table = {
            {kReset, "\e[0m"},
            {kRed, "\e[1;31m"},
            {kGreen, "\e[1;32m"},
            {kYellow, "\e[1;33m"},
            {kBlue, "\e[1;34m"},
            {kMagenta, "\e[1;35m"},
            {kCyan, "\e[1;36m"},
        };
        auto it = table.find(color);
        return it != table.end() ? it->second : table[kReset];
    }

private:
    Color color_;
};

int main() {
    {
        auto logger =
                std::make_shared<ColorLoggerDecorator>(
                    std::make_shared<TimeLoggerDecorator>(
                        std::make_shared<Logger>(std::cout),
                        TimeLoggerDecorator::kDateTime),
                    ColorLoggerDecorator::kRed);

        *logger << "After two years I remember the rest of that day,"
                << "and that night and the next day,";
    }
    {
        auto logger = std::make_shared<Logger>(std::cout);
        auto decorator1 = std::make_shared<ColorLoggerDecorator>(logger, ColorLoggerDecorator::kBlue);
        auto decorator2 = std::make_shared<TimeLoggerDecorator>(decorator1, TimeLoggerDecorator::kTime);
        auto decorator3 = std::make_shared<ColorLoggerDecorator>(decorator2, ColorLoggerDecorator::kYellow);
        auto decorator4 = std::make_shared<TimeLoggerDecorator>(decorator3, TimeLoggerDecorator::kDateTime);
        auto decorator5 = std::make_shared<ColorLoggerDecorator>(decorator4, ColorLoggerDecorator::kCyan);

        *decorator5 << "only as an endless drill of police and photographers and newspaper men in and out of Gatsby's front door."
                    << "A rope stretched across the main gate and a policeman by it kept out the curious,";

        decorator1->Reset();
        decorator2->SetFormat(TimeLoggerDecorator::kDateTime);
        decorator3->SetColor(ColorLoggerDecorator::kMagenta);
        decorator4->Reset();

        *decorator5 << "only as an endless drill of police and photographers and newspaper men in and out of Gatsby's front door."
                    << "A rope stretched across the main gate and a policeman by it kept out the curious,";
    }
}
