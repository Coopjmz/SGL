#pragma once

#ifdef SGL_DEBUG
#	define SGL_LOG_INFO(fmt, ...) do { std::cout << "[SGL Info] " << std::format(fmt, __VA_ARGS__) << std::endl; } while(false)
#	define SGL_LOG_WARNING(fmt, ...) do { std::cout << "[SGL Warning] " << std::format(fmt, __VA_ARGS__) << std::endl; } while(false)
#	define SGL_LOG_ERROR(fmt, ...) do { std::cerr << "[SGL Error] " << std::format(fmt, __VA_ARGS__) << std::endl; } while(false)
#else
#	define SGL_LOG_INFO(fmt, ...)
#	define SGL_LOG_WARNING(fmt, ...)
#	define SGL_LOG_ERROR(fmt, ...)
#endif

#if defined(_MSC_VER)
#	define DEBUG_BREAK() __debugbreak()
#elif defined(__GNUC__) || defined(__clang__)
#	define DEBUG_BREAK() __builtin_trap()
#else
#	include <csignal>
#	define DEBUG_BREAK() raise(SIGTRAP)
#endif

#ifdef SGL_DEBUG
	#define SGL_ASSERT(condition) do { if (!(condition)) { SGL_LOG_ERROR("Assertion failed: \"{}\", File: {}, Line: {}", #condition, __FILE__, __LINE__); DEBUG_BREAK(); } } while(false)
#else
	#define SGL_ASSERT(condition) do { if (!(condition)) abort(); } while(false)
#endif

#define ReturnIf(condition, ...) do { if (condition) return __VA_ARGS__; } while(false)
#define ReturnUnless(condition, ...) do { if (!(condition)) return __VA_ARGS__; } while(false)
#define AssertReturnIf(condition, ...) do { if (condition) { SGL_ASSERT(!#condition); return __VA_ARGS__; } } while(false)
#define AssertReturnUnless(condition, ...) do { if (!(condition)) { SGL_ASSERT(!#condition); return __VA_ARGS__; } } while(false)

#define BreakIf(condition) { if (condition) break; }
#define BreakUnless(condition) { if (!(condition)) break; }
#define AssertBreakIf(condition) { if (condition) { SGL_ASSERT(!#condition); break; } }
#define AssertBreakUnless(condition) { if (!(condition)) { SGL_ASSERT(!#condition); break; } }

#define ContinueIf(condition) { if (condition) continue; }
#define ContinueUnless(condition) { if (!(condition)) continue; }
#define AssertContinueIf(condition) { if (condition) { SGL_ASSERT(!#condition); continue; } }
#define AssertContinueUnless(condition) { if (!(condition)) { SGL_ASSERT(!#condition); continue; } }

#define SafeDelete(ptr) do { delete ptr; ptr = nullptr; } while(false)
#define SafeDeleteArray(ptr) do { delete[] ptr; ptr = nullptr; } while(false)