#include "core/inputManager.h"
#include <core/system.h>
#include <core/window.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <memory>

class ImGuiSystem : public System::ISystem {

public:
  ImGuiSystem(std::shared_ptr<Window> windowPtr) {
    window = windowPtr;
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    io = std::make_unique<ImGuiIO>(ImGui::GetIO());
    ImGui_ImplGlfw_InitForOpenGL(window->getWindow(), true);
    ImGui_ImplOpenGL3_Init();
  }

  void on_start(entt::registry &world) override {}

  void on_update(entt::registry &world, float dt) override {
    if (InputManager::isKeyDown(GLFW_KEY_P))
      InputManager::toggleInputMode(window->getWindow());

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    /*
        std::cerr << "DisplaySize: " << ImGui::GetIO().DisplaySize.x << ", "
                  << ImGui::GetIO().DisplaySize.y << "\n";
    */

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  };

  void on_stop(entt::registry &world) override {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
  };

private:
  std::shared_ptr<Window> window;
  std::unique_ptr<ImGuiIO> io;
};
