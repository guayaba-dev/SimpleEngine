
#include <core/pch.hpp>

#include <core/components.h>
#include <core/engine.h>
#include <core/meshManager.h>
#include <core/shaderManager.h>
#include <core/textureManager.h>

#include <string>

float square[] = {
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // top left
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
    0.5f,  0.5f,  0.0f, 1.0f, 1.0f, // top right
    0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
    -0.5f, 0.5f,  0.0f, 0.0f, 1.0f, // top left
};

int main() {
  Engine engine = Engine();
  engine.start();

  TextureManager texMag = TextureManager();
  MeshManager meshMag = MeshManager();
  ShaderManager shaderMag = ShaderManager();

  MeshComponent asf;
  meshMag.loadMesh("square", square, 6, asf.vao, asf.vbo);
  asf.vertexCount = 6;
  asf.textureID = texMag.loadTexture("assets/container.jpg");

  MaterialComponent maf;

  maf.shaderID = shaderMag.loadShader("basicShader", "assets/basic.vert",
                                      "assets/basic.frag");

  auto &registry = engine.getWorld();

  auto entity = registry.create();

  registry.emplace<MeshComponent>(entity, asf);
  registry.emplace<MaterialComponent>(entity, maf);
  auto &transform = registry.emplace<TransformComponent>(entity);
  transform.position = glm::vec3(0.f, 0.f, 3.0f);

  registry.ctx().emplace<CameraComponent>();
  registry.ctx().emplace<TransformComponent>();

  engine.run();

  engine.shutDown();

  return 0;
}
