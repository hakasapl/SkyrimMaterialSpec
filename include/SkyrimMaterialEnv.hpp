#pragma once

#include <Shaders.hpp>
#include <nlohmann/json.hpp>

#include <unordered_map>

/**
 * @brief Class responsible for storing all material files
 *
 */
class SkyrimMaterialEnv {
private:
  std::unordered_map<std::filesystem::path, nlohmann::json> m_materials;

  std::filesystem::path
      m_materialPath; /** Path to the material directory (all inherits fields
                         are relative to this location) */

public:
  SkyrimMaterialEnv(const std::filesystem::path &materialPath);

  void clear();

  auto validateMaterial(const std::filesystem::path &relPath) -> bool;
  auto loadMaterial(const std::filesystem::path &relPath,
                    const bool &validate = true) -> bool;
  auto purgeMaterial(const std::filesystem::path &path) -> bool;

  // Same methods but for streams
  auto validateMaterial(std::istream &stream) -> bool;
  auto loadMaterial(const std::filesystem::path &path, std::istream &stream,
                    const bool &validate = true) -> bool;

  // Material queries
  auto getMaterial(const std::filesystem::path &relPath,
                   nifly::BSShaderProperty &outMaterial) -> bool;
};