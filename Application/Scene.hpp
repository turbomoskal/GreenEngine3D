/*
*		Scene
*/

#pragma once

// xS1235 warning is OK
class Scene {
public:
	virtual ~Scene() = 0;
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
};