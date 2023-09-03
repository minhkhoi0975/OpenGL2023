#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Application.hpp"

Application::Application(const char* title, int windowWidth, int windowHeight)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		std::cout << "Error: Cannot initialize GLFW." << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// Use OpenGL 3.3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a window.
	window = glfwCreateWindow(windowWidth, windowHeight, title, nullptr, nullptr);
	if (!window)
	{
		std::cout << "Error: Cannot create a window." << std::endl;
		std::exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);

	// Set GLFW callbacks.
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height)
	{
		Application* application = (Application*)glfwGetWindowUserPointer(window);
		application->OnWindowResized(width, height);
	});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Application* application = (Application*)glfwGetWindowUserPointer(window);
		switch (action)
		{
		case GLFW_PRESS:
			application->OnKeyPressed(key);
			break;
		case GLFW_RELEASE:
			application->OnKeyReleased(key);
			break;
		case GLFW_REPEAT:
			application->OnKeyHeld(key);
			break;
		}
	});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
	{
		Application* application = (Application*)glfwGetWindowUserPointer(window);
		switch (action)
		{
		case GLFW_PRESS:
			application->OnMousePressed(button);
			break;
		case GLFW_RELEASE:
			application->OnMouseReleased(button);
			break;
		}
	});

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double newMouseX, double newMouseY)
	{
		Application* application = (Application*)glfwGetWindowUserPointer(window);
		application->OnCursorMove(newMouseX, newMouseY);
	});

	// Initialize GLAD.
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error: Cannot initialize GLAD. " << std::endl;
		glfwTerminate();
		std::exit(EXIT_FAILURE);
	}

	std::cout << "Application initialized." << std::endl;
}

Application::~Application()
{
	OnShutdown();
	glfwTerminate();
}

void Application::OnShutdown()
{
	std::cout << "Application shut down." << std::endl;
}

void Application::RunLoop()
{
	while (!glfwWindowShouldClose(window))
	{
		// Update the time between frames.
		float time = glfwGetTime();
		deltaTime = time - latestFrameTime;
		latestFrameTime = time;

		// Update the cursor's position and delta position.
		double newCursorX, newCursorY;
		glfwGetCursorPos(window, &newCursorX, &newCursorY);
		cursorDeltaX = newCursorX - cursorX;
		cursorDeltaY = newCursorY - cursorY;
		cursorX = newCursorX;
		cursorY = newCursorY;

		OnUpdate();

		// Swap front and back buffers.
		glfwSwapBuffers(window);

		// Poll and process events.
		glfwPollEvents();
	}
}

void Application::OnUpdate()
{
}

void Application::CloseWindow()
{
	glfwSetWindowShouldClose(window, true);
}

void Application::GetCursor(float& cursorX, float& cursorY) const
{
	cursorX = this->cursorX;
	cursorY = this->cursorY;
}

void Application::GetCursorDelta(float& deltaX, float& deltaY) const
{
	deltaX = cursorDeltaX;
	deltaY = cursorDeltaY;
}

void Application::OnWindowResized(int newWidth, int newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
}

void Application::OnKeyPressed(int key)
{
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(window, true);
}

void Application::OnKeyReleased(int key)
{
}

void Application::OnKeyHeld(int key)
{
}

void Application::OnMousePressed(int button)
{
}

void Application::OnMouseReleased(int button)
{
}

void Application::OnCursorMove(double newMouseX, double newMouseY)
{
}