#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>

#include <thread>

namespace Hydra
{

    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        uint32_t ThreadID;
    };

    struct InstrumentationSession
    {
        std::string Name;
    };

    class Instrumentor
    {
    public:
        Instrumentor()
            : m_CurrentSession(nullptr)
            , m_ProfileCount(0)
        {
        }

        void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            m_OutputStream.open(filepath);
            WriteHeader();
            m_CurrentSession = new InstrumentationSession{name};
        }

        void EndSession()
        {
            WriteFooter();
            m_OutputStream.close();
            delete m_CurrentSession;
            m_CurrentSession = nullptr;
            m_ProfileCount = 0;
        }

        void WriteProfile(const ProfileResult& result)
        {
            if (m_ProfileCount++ > 0)
                m_OutputStream << ",";

            std::string name = result.Name;
            std::replace(name.begin(), name.end(), '"', '\'');

            m_OutputStream << "{";
            m_OutputStream << "\"cat\":\"function\",";
            m_OutputStream << "\"dur\":" << (result.End - result.Start) << ',';
            m_OutputStream << "\"name\":\"" << name << "\",";
            m_OutputStream << "\"ph\":\"X\",";
            m_OutputStream << "\"pid\":0,";
            m_OutputStream << "\"tid\":" << result.ThreadID << ",";
            m_OutputStream << "\"ts\":" << result.Start;
            m_OutputStream << "}";

            m_OutputStream.flush();
        }

        void WriteHeader()
        {
            m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
            m_OutputStream.flush();
        }

        void WriteFooter()
        {
            m_OutputStream << "]}";
            m_OutputStream.flush();
        }

        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }

    private:
        InstrumentationSession* m_CurrentSession;
        std::ofstream m_OutputStream;
        int m_ProfileCount;
    };

    class InstrumentationTimer
    {
    public:
        InstrumentationTimer(const char* name)
            : m_Name(name)
            , m_Stopped(false)
        {
            m_StartTimepoint = std::chrono::high_resolution_clock::now();
        }

        ~InstrumentationTimer()
        {
            if (!m_Stopped)
                Stop();
        }

        void Stop()
        {
            auto endTimepoint = std::chrono::high_resolution_clock::now();

            long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
            long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

            uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
            Instrumentor::Get().WriteProfile({m_Name, start, end, threadID});

            m_Stopped = true;
        }

    private:
        const char* m_Name;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
        bool m_Stopped;
    };
}


#define HD_PROFILE 1

#if HD_PROFILE
    #if defined(__GNUC__) || defined(__clang__)
        #define HD_FUNC_SIG __PRETTY_FUNCTION__
    #elif defined(_MSC_VER)
        #define HD_FUNC_SIG __FUNCSIG__
    #elif defined(__cplusplus) && (__cplusplus >= 201103) // Фолбек на стандартный C++11
        #define HD_FUNC_SIG __func__
    #else
        #define HD_FUNC_SIG "HD_FUNC_SIG unknown!"
    #endif

    #define HD_PROFILE_CONCAT_INNER(a, b) a##b
    #define HD_PROFILE_CONCAT(a, b) HD_PROFILE_CONCAT_INNER(a, b)

    #define HD_PROFILE_BEGIN_SESSION(name, filepath) \
        ::Hydra::Instrumentor::Get().BeginSession(name, filepath)

    #define HD_PROFILE_END_SESSION() \
        ::Hydra::Instrumentor::Get().EndSession()

    #define HD_PROFILE_SCOPE(name) \
        ::Hydra::InstrumentationTimer HD_PROFILE_CONCAT(timer, __LINE__)(name)

    #define HD_PROFILE_FUNCTION() HD_PROFILE_SCOPE(HD_FUNC_SIG)

#else

    #define HD_PROFILE_BEGIN_SESSION(name, filepath)
    #define HD_PROFILE_END_SESSION()
    #define HD_PROFILE_SCOPE(name)
    #define HD_PROFILE_FUNCTION()

#endif