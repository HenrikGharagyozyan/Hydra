#pragma once

#include "Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#pragma warning(pop)


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

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
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