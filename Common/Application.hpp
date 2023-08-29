#pragma once

class GLFWwindow;

class Application
{
private:
	GLFWwindow* window;

private:
	/// <summary>
	/// The time, in seconds, of the latest frame.
	/// </summary>
	float latestFrameTime = 0.0f;

	/// <summary>
	/// Time between consecutive frames, in seconds.
	/// </summary>
	float deltaTime = 0.0f;

public:
	Application(const char* title, int windowWidth, int windowHeight);
	~Application();

	void RunLoop();
	virtual void OnUpdate();

	/// <summary>
	/// Called before GLFW is terminated.
	/// </summary>
	virtual void OnShutdown();

public:
	// Events.
	virtual void OnWindowResized(int newWidth, int newHeight);

	virtual void OnKeyPressed(int key);
	virtual void OnKeyReleased(int key);
	virtual void OnKeyHeld(int key);

	virtual void OnMousePressed(int button);
	virtual void OnMouseReleased(int button);
};