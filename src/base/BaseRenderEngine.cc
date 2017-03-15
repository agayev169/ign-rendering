/*
 * Copyright (C) 2015 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <ignition/common/Console.hh>

#include "ignition/rendering/ogre/OgreRenderEngine.hh"

using namespace ignition;
using namespace rendering;

//////////////////////////////////////////////////
BaseRenderEngine::BaseRenderEngine()
{
}

//////////////////////////////////////////////////
BaseRenderEngine::~BaseRenderEngine()
{
}

//////////////////////////////////////////////////
bool BaseRenderEngine::Load()
{
  if (this->loaded)
  {
    ignwarn << "Render-engine has already been loaded" << std::endl;
    return true;
  }

  this->loaded = this->LoadImpl();
  return this->loaded;
}

//////////////////////////////////////////////////
bool BaseRenderEngine::Init()
{
  if (!this->loaded)
  {
    ignerr << "Render-engine must be loaded first" << std::endl;
    return false;
  }

  if (this->initialized)
  {
    ignwarn << "Render-engine has already been initialized" << std::endl;
    return true;
  }

  this->initialized = this->InitImpl();
  return this->initialized;
}

//////////////////////////////////////////////////
bool BaseRenderEngine::Fini()
{
  return true;
}

//////////////////////////////////////////////////
bool BaseRenderEngine::IsLoaded() const
{
  return this->loaded;
}

//////////////////////////////////////////////////
bool BaseRenderEngine::IsInitialized() const
{
  return this->initialized;
}

//////////////////////////////////////////////////
bool BaseRenderEngine::IsEnabled() const
{
  return this->initialized;
}

//////////////////////////////////////////////////
unsigned int BaseRenderEngine::SceneCount() const
{
  return this->Scenes()->Size();
}

//////////////////////////////////////////////////
bool BaseRenderEngine::HasScene(ConstScenePtr _scene) const
{
  return this->Scenes()->Contains(_scene);
}

//////////////////////////////////////////////////
bool BaseRenderEngine::HasSceneId(unsigned int _id) const
{
  return this->Scenes()->ContainsId(_id);
}

//////////////////////////////////////////////////
bool BaseRenderEngine::HasSceneName(const std::string &_name) const
{
  return this->Scenes()->ContainsName(_name);
}

//////////////////////////////////////////////////
ScenePtr BaseRenderEngine::SceneById(unsigned int _id) const
{
  return this->Scenes()->GetById(_id);
}

//////////////////////////////////////////////////
ScenePtr BaseRenderEngine::SceneByName(const std::string &_name) const
{
  return this->Scenes()->GetByName(_name);
}

//////////////////////////////////////////////////
ScenePtr BaseRenderEngine::SceneByIndex(unsigned int _index) const
{
  return this->Scenes()->GetByIndex(_index);
}

//////////////////////////////////////////////////
void BaseRenderEngine::DestroyScene(ScenePtr _scene)
{
  this->Scenes()->Destroy(_scene);
}

//////////////////////////////////////////////////
void BaseRenderEngine::DestroySceneById(unsigned int _id)
{
  this->Scenes()->DestroyById(_id);
}

//////////////////////////////////////////////////
void BaseRenderEngine::DestroySceneByName(const std::string &_name)
{
  this->Scenes()->DestroyByName(_name);
}

//////////////////////////////////////////////////
void BaseRenderEngine::DestroySceneByIndex(unsigned int _index)
{
  this->Scenes()->DestroyByIndex(_index);
}

//////////////////////////////////////////////////
void BaseRenderEngine::DestroyScenes()
{
  this->Scenes()->DestroyAll();
}

//////////////////////////////////////////////////
ScenePtr BaseRenderEngine::CreateScene(const std::string &_name)
{
  unsigned int sceneId = this->NextSceneId();
  return this->CreateScene(sceneId, _name);
}

//////////////////////////////////////////////////
ScenePtr BaseRenderEngine::CreateScene(unsigned int _id,
    const std::string &_name)
{
  if (!this->IsInitialized())
  {
    ignerr << "Render-engine has not been initialized" << std::endl;
    return nullptr;
  }

  if (this->HasSceneId(_id))
  {
    ignerr << "Scene already exists with id: " << _id << std::endl;
    return nullptr;
  }

  if (this->HasSceneName(_name))
  {
    ignerr << "Scene already exists with id: " << _id << std::endl;
    return nullptr;
  }

  ScenePtr scene = this->CreateSceneImpl(_id, _name);
  this->PrepareScene(scene);
  return scene;
}

//////////////////////////////////////////////////
void BaseRenderEngine::Destroy()
{
}

//////////////////////////////////////////////////
void BaseRenderEngine::PrepareScene(ScenePtr _scene)
{
  if (_scene)
  {
    _scene->Load();
    _scene->Init();
  }
}

//////////////////////////////////////////////////
unsigned int BaseRenderEngine::NextSceneId()
{
  return this->nextSceneId--;
}
