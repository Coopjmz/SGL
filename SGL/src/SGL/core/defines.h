#pragma once

#define LOG(string) std::cout << (string) << std::endl
#define LOG_ERR(error) std::cerr << (error) << std::endl
#define LOG_VAR(variable) std::cout << #variable << " = " << (variable) << std::endl
#define LOG_NEW_LINE() std::cout << std::endl

#define ASSERT(condition) do { if (!(condition)) __debugbreak(); } while(false)

#define ReturnIf(condition, ...) do { if (condition) return __VA_ARGS__; } while(false)
#define ReturnUnless(condition, ...) do { if (!(condition)) return __VA_ARGS__; } while(false)
#define AssertReturnIf(condition, ...) do { if (condition) { ASSERT(false); return __VA_ARGS__; } } while(false)
#define AssertReturnUnless(condition, ...) do { if (!(condition)) { ASSERT(false); return __VA_ARGS__; } } while(false)

#define BreakIf(condition) { if (condition) break; }
#define BreakUnless(condition) { if (!(condition)) break; }
#define AssertBreakIf(condition) { if (condition) { ASSERT(false); break; } }
#define AssertBreakUnless(condition) { if (!(condition)) { ASSERT(false); break; } }

#define ContinueIf(condition) { if (condition) continue; }
#define ContinueUnless(condition) { if (!(condition)) continue; }
#define AssertContinueIf(condition) { if (condition) { ASSERT(false); continue; } }
#define AssertContinueUnless(condition) { if (!(condition)) { ASSERT(false); continue; } }

#define SafeDelete(ptr) do { delete ptr; ptr = nullptr; } while(false)
#define SafeDeleteArray(ptr) do { delete[] ptr; ptr = nullptr; } while(false)