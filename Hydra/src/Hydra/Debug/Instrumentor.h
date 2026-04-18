#pragma once

#include <algorithm>
#include <chrono>
#include <fstream>

#include <string>
#include <thread>

namespace Hydra
{

    struct ProfileResult
    {
        std::string Name;
        long long Start, End;
        std::thread::id ThreadID;
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
        {
        }

        void BeginSession(const std::string& name, const std::string& filepath = "results.json")
        {
            std::lock_guard lock(m_Mutex);
            if (m_CurrentSession)
            {
                // If there is already a current session, then close it before beginning new one.
				// Subsequent profiling output meant for the original session will end up in the
				// newly opened session instead.  That's better than having badly formatted
				// profiling output.
				if (Log::GetCoreLogger())  // Edge case: BeginSession() might be before Log::Init()
					HD_CORE_ERROR("Instrumentor::BeginSession('{0}') when session '{1}' already open.", name, m_CurrentSession->Name);
				InternalEndSession();
            }
            m_OutputStream.open(filepath);
            if (m_OutputStream.is_open())
            {
                m_CurrentSession = new InstrumentationSession({name});
                WriteHeader();
            }
            else
            {
                if (Log::GetCoreLogger())  // Edge case: BeginSession() might be before Log::Init()
                    HD_CORE_ERROR("Instrumentor could not open results file '{0}'.", filepath);
            }
        }

        void EndSession()
        {
            std::lock_guard lock(m_Mutex);
            InternalEndSession();
        }

        void WriteProfile(const ProfileResult& result)
        {
            std::stringstream json;

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			json << ",{";
			json << "\"cat\":\"function\",";
			json << "\"dur\":" << (result.End - result.Start) << ',';
			json << "\"name\":\"" << name << "\",";
			json << "\"ph\":\"X\",";
			json << "\"pid\":0,";
			json << "\"tid\":" << result.ThreadID << ",";
			json << "\"ts\":" << result.Start;
			json << "}";

			std::lock_guard lock(m_Mutex);
			if (m_CurrentSession) 
            {
				m_OutputStream << json.str();
				m_OutputStream.flush();
			}
        }

        static Instrumentor& Get()
        {
            static Instrumentor instance;
            return instance;
        }

    private:
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

        // Note: you must already own lock on m_Mutex before
		// calling InternalEndSession()
        void InternalEndSession()
        {
            if (m_CurrentSession)
            {
                WriteFooter();
                m_OutputStream.close();
                delete m_CurrentSession;
                m_CurrentSession = nullptr;
            }
        }

    private:
        std::mutex m_Mutex;
        InstrumentationSession* m_CurrentSession;
        std::ofstream m_OutputStream;
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
            Instrumentor::Get().WriteProfile({ m_Name, start, end, std::this_thread::get_id() });

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