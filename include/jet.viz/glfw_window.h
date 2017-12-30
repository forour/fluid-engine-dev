// Copyright (c) 2017 Doyub Kim
//
// I am making my contributions/submissions to this project solely in my
// personal capacity and am not conveying any rights to any intellectual
// property of any third parties.

#ifndef INCLUDE_JET_VIZ_GLFW_WINDOW_H_
#define INCLUDE_JET_VIZ_GLFW_WINDOW_H_

#ifdef JET_USE_GL

#include <jet/macros.h>

#include <jet.viz/event.h>
#include <jet.viz/gl_renderer.h>
#include <jet.viz/glfw_app.h>
#include <jet.viz/input_events.h>
#include <jet.viz/view_controller.h>

struct GLFWwindow;

namespace jet {
namespace viz {

class GlfwWindow final {
 public:
    void setViewController(const ViewControllerPtr& viewController);

    const GLRendererPtr& renderer() const;

    GLFWwindow* glfwWindow() const;

    void requestRender(unsigned int numFrames = 1);

    bool isAnimationEnabled() const;
    void setIsAnimationEnabled(bool enabled);

    void setSwapInterval(int interval);

    // Event handlers
    Event<GlfwWindow*>& onUpdateEvent();
    Event<GlfwWindow*>& onGuiEvent();
    Event<GlfwWindow*, const KeyEvent&>& onKeyDownEvent();
    Event<GlfwWindow*, const KeyEvent&>& onKeyUpEvent();
    Event<GlfwWindow*, const PointerEvent&>& onPointerPressedEvent();
    Event<GlfwWindow*, const PointerEvent&>& onPointerReleasedEvent();
    Event<GlfwWindow*, const PointerEvent&>& onPointerDraggedEvent();
    Event<GlfwWindow*, const PointerEvent&>& onPointerHoverEvent();
    Event<GlfwWindow*, const PointerEvent&>& onMouseWheelEvent();

    //! Returns the framebuffer size.
    //! Note that the framebuffer size can be different from the window size,
    //! especially on a Retina display (2x the window size).
    Size2 framebufferSize() const;

    //! Returns the window size.
    Size2 windowSize() const;

 private:
    GLFWwindow* _window = nullptr;

    MouseButtonType _pressedMouseButton = MouseButtonType::None;
    ModifierKey _lastModifierKey = ModifierKey::None;

    bool _isAnimationEnabled = false;
    unsigned int _numRequestedRenderFrames = 0;

    int _width = 1;
    int _height = 1;
    bool _hasPointerEntered = false;
    double _pointerPosX = 0.0;
    double _pointerPosY = 0.0;
    double _pointerDeltaX = 0.0;
    double _pointerDeltaY = 0.0;

    GLRendererPtr _renderer;
    ViewControllerPtr _viewController;

    int _swapInterval = 0;

    Event<GlfwWindow*> _onUpdateEvent;
    Event<GlfwWindow*> _onGuiEvent;
    Event<GlfwWindow*, const KeyEvent&> _onKeyDownEvent;
    Event<GlfwWindow*, const KeyEvent&> _onKeyUpEvent;
    Event<GlfwWindow*, const PointerEvent&> _onPointerPressedEvent;
    Event<GlfwWindow*, const PointerEvent&> _onPointerReleasedEvent;
    Event<GlfwWindow*, const PointerEvent&> _onPointerDraggedEvent;
    Event<GlfwWindow*, const PointerEvent&> _onPointerHoverEvent;
    Event<GlfwWindow*, const PointerEvent&> _onMouseWheelEvent;

    EventToken _onBasicCameraStateChangedEventToken = kEmptyEventToken;

    GlfwWindow(const std::string& title, int width, int height);

    void render();

    void resize(int width, int height);

    void update();

    void key(int key, int scancode, int action, int mods);

    void pointerButton(int button, int action, int mods);

    void pointerMoved(double x, double y);

    void pointerEnter(bool entered);

    void mouseWheel(double deltaX, double deltaY);

    double getScaleFactor() const;

    friend class GlfwApp;
};

typedef std::shared_ptr<GlfwWindow> GlfwWindowPtr;

}  // namespace viz
}  // namespace jet

#endif  // JET_USE_GL

#endif  // INCLUDE_JET_VIZ_GLFW_WINDOW_H_
