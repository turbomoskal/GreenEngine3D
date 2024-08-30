#pragma once

#include "Event.hpp"

#include <memory>
#include <string>

class Window;

class Game : public std::enable_shared_from_this<Game> {
public:
	Game(const std::wstring&, int, int, bool);
	virtual ~Game();
	int GetClientWidth() const { return _Width; }
	int GetClientHeight() const { return _Height; }
	virtual bool Initialize();
	virtual bool LoadContent() = 0;
	virtual bool UnloadContent() = 0;
	virtual bool Destroy();

protected:
	friend class Window;
	virtual void OnUpdate(UpdateEventArgs&);
	virtual void OnRender(RenderEventArgs&);
	virtual void OnKeyPressed(KeyEventArgs&);
	virtual void OnKeyReleased(KeyEventArgs&);
	virtual void OnMouseMoved(MouseMotionEventArgs&);
	virtual void OnMouseButtonPressed(MouseButtonEventArgs&);
	virtual void OnMouseButtonReleased(MouseButtonEventArgs&);
	virtual void OnMouseWheel(MouseWheelEventArgs&);
	virtual void OnResize(ResizeEventArgs&);
	virtual void OnWindowDestroy();
	std::shared_ptr<Window>		_PWindow;

private:
	std::wstring				_Name;
	int							_Width;
	int							_Height;
	bool						_VSync;
};