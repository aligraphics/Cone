#pragma once

#include "Mesh.hpp"

#include "glm/glm.hpp"

class Context;

class SceneMember
{
public:
    SceneMember(Context* context, const Mesh::MeshInfo& meshInfo);
    ~SceneMember() = default;

    SceneMember(const SceneMember& otherSceneMember) = delete;
    SceneMember& operator=(const SceneMember& otherSceneMember) = delete;
public:
    SceneMember& Translate(float x, float y, float z);
    SceneMember& Rotate(float angleX, float angleY, float angleZ);
    SceneMember& Scale(float x, float y, float z);
    void UpdateModelMatrix();
public:
    inline const Mesh& GetMesh() const { return m_Mesh; }
    inline const glm::mat4& GetModelMatrix() const { return m_ModelMatrix; }
private:
    Context*                m_Context;
    Mesh                    m_Mesh;
    glm::vec3               m_Translation;
    glm::vec3               m_Rotation;
    glm::vec3               m_Scale;
    glm::mat4               m_ModelMatrix;
};
