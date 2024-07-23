/*
*		Renderer
*/

#pragma once
#include "Event.hpp"
#include "Scene.hpp"
#include "LangHeaders.hpp"
#include "DXHeaders.hpp"

class Window;

// TODO: WTF is std::enable_shared_from_this ???
class Renderer : public std::enable_shared_from_this<Renderer> {
public:
	Renderer(D2D1_SIZE_U, bool);
	virtual ~Renderer();
	virtual bool Initialize();
	virtual bool UploadContent();
	virtual void UnloadContent();
	virtual void Destroy();
	inline auto GetSceneSize() const {
		return SceneSize;
	}
protected:
	friend class Window;
	virtual void OnUpdate(UpdateEvent&);
	virtual void OnRender(RenderEvent&);
	virtual void OnKeyPressed(KeyEvent&);
	virtual void OnKeyReleased(KeyEvent&);
	virtual void OnMouseMoved(MouseMotionEvent&);
	virtual void OnMousePressed(MouseButtonEvent&);
	virtual void OnMouseReleased(MouseButtonEvent&);
	virtual void OnMouseWheel(MouseWheelEvent&);
	virtual void OnResize(ResizeEvent&);
	virtual void OnWindowDestroy();
	std::shared_ptr<Window> ptrWindow;
private:
	D2D1_SIZE_U SceneSize;
	bool VSync;
};