#include "core/inputManager.h"
#include "detail/qualifier.hpp"
#include <core/system.h>
#include <core/window.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <memory>

class ImGuiSystem : public System::ISystem {

public:
  float newShineVal = 0.0;
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

    auto matView = world.view<PhongMaterial>();

    for (auto [entity, PhongMaterial] : matView.each()) {
      ImGui::SliderFloat("shininess", &PhongMaterial.shininess, 0.0, 120.0);
    }

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
