#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <shellapi.h>
#ifdef min
#undef min
#endif // min
#ifdef max
#undef max
#endif // max
#ifdef CreateWindow
#undef CreateWindow
#endif // CreateWindow
#include <wrl.h>
using namespace Microsoft::WRL;
#include <d3dx12.h>
#include <dxgi1_6.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXTex.h>
using namespace DirectX;
#include <algorithm>
#include <atomic>
#include <cassert>
#include <chrono>
#include <condition_variable>
#include <filesystem>
#include <map>
#include <memory>
#include <mutex>
#include <new>
#include <string>
#include <unordered_map>
#include <thread>
#include <vector>
namespace fs = std::filesystem;
#include "helpers.hpp"