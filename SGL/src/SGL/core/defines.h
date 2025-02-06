#pragma once

#define SGL_LOG_INFO(info, ...) fprintf(stdout, "[SGL Info] "##info##"\n", __VA_ARGS__)
#define SGL_LOG_ERROR(error, ...) fprintf(stderr, "[SGL Error] "##error##"\n", __VA_ARGS__)
#define SGL_LOG_WARNING(warning, ...) fprintf(stderr, "[SGL Warning] "##warning##"\n", __VA_ARGS__)

#ifdef SGL_DEBUG
	#define SGL_ASSERT(condition) do { if (!(condition)) { SGL_LOG_ERROR("Assert failed: "#condition); __debugbreak(); } } while(false)
#else
	#define SGL_ASSERT(condition)
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