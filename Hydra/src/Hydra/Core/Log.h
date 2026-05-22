#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Hydra
{
	
	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

}

// Core log macros
#define HD_CORE_ERROR(...)     ::Hydra::Log::GetCoreLogger()->error(__VA_ARGS__)
#define HD_CORE_WARN(...)      ::Hydra::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define HD_CORE_INFO(...)      ::Hydra::Log::GetCoreLogger()->info(__VA_ARGS__)
#define HD_CORE_TRACE(...)     ::Hydra::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define HD_CORE_CRITICAL(...)  ::Hydra::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define HD_ERROR(...)		   ::Hydra::Log::GetClientLogger()->error(__VA_ARGS__)
#define HD_WARN(...)		   ::Hydra::Log::GetClientLogger()->warn(__VA_ARGS__)
#define HD_INFO(...)		   ::Hydra::Log::GetClientLogger()->info(__VA_ARGS__)
#define HD_TRACE(...)		   ::Hydra::Log::GetClientLogger()->trace(__VA_ARGS__)
#define HD_CRITICAL(...)	   ::Hydra::Log::GetClientLogger()->critical(__VA_ARGS__)