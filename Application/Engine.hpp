/*
*		Engine
*/
#pragma once

#include "LangHeaders.hpp"
#include "WinHeaders.hpp"
#include "DXHeaders.hpp"

constexpr auto g_MaxLoadString(100);

class Window;
class Renderer;
class Direct3D;
class Direct2D;

class Engine {
private:
	D2D1_SIZE_U ClientSize;
	std::shared_ptr<Direct3D> ptrD3D12;
	std::shared_ptr<Direct2D> ptrD2D1;

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	HINSTANCE MainInstance;
	bool TearingSupport;
public:
	std::shared_ptr<Direct3D> GetD3DPtr();
	std::shared_ptr<Direct2D> GetD2DPtr();
	static void Create(HINSTANCE);
	static void Destroy();
	static Engine& Get();
	std::shared_ptr<Window> CreateRenderWindow(D2D1_SIZE_U, bool);
	void DestroyWindow(const std::shared_ptr<Window>);
	int Run(std::shared_ptr<Renderer>);
	void Quit(int);
protected:
	Engine(HINSTANCE);
	virtual ~Engine();
};