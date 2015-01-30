#include "Scene\Scene.h"
#include <sstream>
#include "json\json.h"

Scene::Scene(): activeCamera(0)
{
	cameras.push_back(new Camera());
	cameras.push_back(new Camera());
	masterLoaded = false;
	for(auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		*it = NULL;
	}
}
Scene::~Scene()
{
	for(auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}
	for(auto it = cameras.begin(); it != cameras.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}

}
bool Scene::LoadScene(std::string filename)
{
	Json::Reader reader;
	Json::Value root;
	std::fstream input;



	//std::size_t found;
	input.open("Scene/"+filename+".scn");
	if(!input.is_open())
	{
		std::cout << "file not found use .scn file extension" << std::endl;
		return false;
	}
	bool parsingSuccessful = reader.parse( input, root );
	if ( !parsingSuccessful )
	{
		// report to the user the failure and their locations in the document.
		std::cout  << "Failed to parse configuration\n" << reader.getFormattedErrorMessages();
		return 0;
	}
	///Storing the scene data from JSON
	sceneData.name = root["scene"]["name"].asString();
	sceneData.sceneShader = root["scene"]["sceneshader"].asString();
	sceneData.currentCamera = root["scene"]["currentcamera"].asString();
	sceneData.currentLight = root["scene"]["currentlight"].asString();
	sceneData.messageHandlers =	root["scene"]["messagehandlers"].asBool();
	sceneData.menu = root["scene"]["messagehandlers"].asBool();

	///Creating a new Entity.
	for(Json::ValueIterator entsIter = root["scene"]["entities"].begin(); entsIter != root["scene"]["entities"].end(); ++entsIter)
	{
		for(unsigned int i = 0; i < root["scene"]["activeentities"].size();++i)
		{
			Json::Value entityKey = entsIter.key();
			Json::Value entity = (*entsIter);
			GameObject *g = new GameObject(entityKey.asString());
			if(entityKey.asString() == root["scene"]["activeentities"][i].asString())
			{
				for(Json::ValueIterator it2 = entity.begin(); it2 != entity.end(); ++it2)
				{
					Json::Value key = it2.key();
					Json::Value value = (*it2);
					//cout << key.asString() << endl;
					if(key.asString() == "type" )
					{
						g->setEntityType(value.asString());
					}
					if(key.asString() == "components" )
					{
						for(Json::ValueIterator compIter = value.begin(); compIter != value.end(); ++compIter)
						{
							Json::Value compKey = compIter.key();
							Json::Value compVal = (*compIter);
							std::string objString, textureString;

							for(Json::ValueIterator compValIter = compVal.begin(); compValIter != compVal.end(); ++compValIter)
							{
								Json::Value compVal2 = (*compValIter);
								Json::Value compValKey = compValIter.key();
								
								if(compValKey.asString() == "OBJModel")
								{
									objString = compVal2.asString();
									
								}
								if(compValKey.asString() == "TextureFile")
								{
									textureString = compVal2.asString();
									
								}
							}
							g->getRenderComp()->init(rManager->getModel().at(objString), rManager->getTexture().at(textureString));
							//g->getTransformComp()->Rotate(
						}
					}
					//cout << value.asString() << endl;
				}
			}
			gameObjects.push_back(g);
		}
	}


	input.close();




	return true;
}
void Scene::InitScene(std::string loadSceneName, std::string masterSceneName)//Loads gameobjects and shaders.
{
	filename = loadSceneName;
	rManager = ResourceManager::getInstance();
	if(rManager->LoadMaster(masterSceneName))
	{
		masterLoaded = true;
		if(!LoadScene(loadSceneName))
		{
			std::cout << "error loading scene\n";
		}
	}

	programHandle = rManager->getShaders().at(0)->programhandle;




	if(gameObjects.size() != 0 )
	{
		for(auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			(*it)->init();
			for(unsigned int i =0; i < cameras.size();++i)
			{
				cameras[i]->init(rManager->getShaders().at(0)->programhandle);
			}
		}
	}


}
void Scene::Update(bool keys[])//Updates the scene running in a loop
{


	cameras[activeCamera]->update();

	if(gameObjects.size() != 0 )
	{
		for(auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
		{
			(*it)->update(keys);

		}
	}


}
void Scene::Render()
{
	gl::UseProgram(rManager->getShaders().at(0)->programhandle);

	for(auto it = gameObjects.begin(); it != gameObjects.end(); ++it)
	{

		model = glm::mat4(1);



		model = glm::translate(model,(*it)->getTransformComp()->getTranslate());
		model = glm::rotate(model,glm::radians((*it)->getTransformComp()->getRotate().x),glm::vec3(1.0f,0.0f,0.0f));
		model = glm::rotate(model,glm::radians((*it)->getTransformComp()->getRotate().y),glm::vec3(0.0f,1.0f,0.0f));
		model = glm::rotate(model,glm::radians((*it)->getTransformComp()->getRotate().z),glm::vec3(0.0f,0.0f,1.0f));
		model = glm::scale(model,(*it)->getTransformComp()->getScale());

		setUpMatricies();
		setLightParams();

		(*it)->render();

	}

}
void Scene::resize(int w, int h)
{
	gl::Viewport(0,0,w,h);
	cameras[activeCamera]->setAspectRatio((float)w/h);
}

void Scene::nextCamera()
{
	if(activeCamera == cameras.size()-1)
	{
		activeCamera = 0;
	}
	else ++activeCamera;

}


void Scene::setLightParams()
{


	GLuint loc5 = gl::GetUniformLocation(programHandle, "numLights");
	gl::Uniform1i(loc5, lights.size());
	for(unsigned int i =0; i< lights.size();++i)
	{
		std::ostringstream oss;
		oss << "lights[" << i << "].diffuse";
		std::string var = oss.str();
		GLuint loc = gl::GetUniformLocation(programHandle, var.c_str());
		gl::Uniform3f(loc,lights.at(i).diffuse.x,lights.at(i).diffuse.y,lights.at(i).diffuse.z);
		oss.clear();
		oss.str("");
		oss << "lights[" << i << "].ambient";
		var = oss.str();
		GLuint loc1 = gl::GetUniformLocation(programHandle, var.c_str());
		gl::Uniform3f(loc1,lights.at(i).ambient.x,lights.at(i).ambient.y,lights.at(i).ambient.z);
		oss.clear();
		oss.str("");
		oss << "lights[" << i << "].attenuation";
		var = oss.str();
		GLuint loc2 = gl::GetUniformLocation(programHandle, var.c_str());
		gl::Uniform1f(loc2,lights.at(i).attenuation);
		oss.clear();
		oss.str("");
		oss << "lights[" << i << "].fallOffSize";
		var = oss.str();
		GLuint loc3 = gl::GetUniformLocation(programHandle, var.c_str());
		gl::Uniform1f(loc3,lights.at(i).fallOffSize);
		oss.clear();
		oss.str("");
		oss << "lights[" << i << "].position";
		var = oss.str();
		GLuint loc4 = gl::GetUniformLocation(programHandle, var.c_str());
		gl::Uniform3f( loc4,lights.at(i).position.x,lights.at(i).position.y,lights.at(i).position.z);

	}


}
void Scene::setUpMatricies()
{
	//glm::mat4 mv = cameras.at(activeCamera)->view() *  model;
	//prog.setUniform("ModelViewMatrix", mv);
	/*GLuint loc = gl::GetUniformLocation(programHandle,"ModelViewMatrix");
	gl::UniformMatrix4fv(loc, 1, FALSE, &mv[0][0]);*/
	GLuint loc1 = gl::GetUniformLocation(programHandle,"NormalMatrix");
	//glm::mat3 norMat = glm::mat3( glm::vec3(mv[0]), glm::vec3(mv[1]), glm::vec3(mv[2]));
	glm::mat3 normMat = glm::transpose(glm::inverse(glm::mat3(model)));
	gl::UniformMatrix3fv(loc1, 1, FALSE, &normMat[0][0] );

	GLuint viewMatrixID = 
		gl::GetUniformLocation(programHandle, "V");//programhandle in first parameter
	gl::UniformMatrix4fv(viewMatrixID, 1, gl::FALSE_, &cameras.at(activeCamera)->view()[0][0]);

	GLuint projectionMatrixID = 
		gl::GetUniformLocation(programHandle, "P");//programhandle in first parameter

	gl::UniformMatrix4fv(projectionMatrixID, 1, gl::FALSE_, &cameras.at(activeCamera)->projection()[0][0]);

	GLuint modelMatrixID = gl::GetUniformLocation(programHandle, "M");
	gl::UniformMatrix4fv(modelMatrixID, 1, gl::FALSE_, &model[0][0]);

}
void Scene::deleteShader()
{
	gl::DeleteProgram(programHandle);
	/*for(int i=0; i< rManager->getShaders().size();++i)
	{
	gl::DeleteShader(rManager->getShaders().at(i)->fragShader);
	gl::DeleteShader(rManager->getShaders().at(i)->vertShader);
	}*/

}



//int shaderID, modelID, textureID;
//std::size_t found;
//while(getline(input, line))
//{
//	ss.str("");
//	ss.clear();
//	found = line.find("scene");
//	if (found!= std::string::npos)
//	{
//		ss.str(line);
//		ss.ignore(5);
//		ss >> nameObject >> tX >> tY >> tZ 
//			>> rX >> rY >> rZ >>
//			sX >> sY >> sZ >> shaderID >> modelID >> textureID >>
//			animComp >> animSide;
//		GameObject *g = new GameObject(nameObject);
//		g->setID(shaderID,modelID, textureID);
//		g->getRenderComp()->init(rManager->getModel().at(modelID)->verts,rManager->getModel().at(modelID)->normals,
//			rManager->getModel().at(modelID)->textureCoords, rManager->getTexture().at(textureID));
//		g->getTransformComp()->getTranslate() = glm::vec3(tX , tY, tZ );
//		g->getTransformComp()->getRotate() = glm::vec3( rX ,rY , rZ );
//		g->getTransformComp()->getScale()= glm::vec3(sX,sY,sZ);
//		if(g->addComponent(animComp))
//		{
//			if(g->getAnimComp())
//			{
//				g->getAnimComp()->init(animSide);
//			}
//		}
//		gameObjects.push_back(g);

//	}

//}
///*while(getline(input,line))
//{
//ss.clear();
//ss.str(line);
//++lineCount;
//ss >> nameObject >> tX >> tY >> tZ 
//>> rX >> rY >> rZ >>
//sX >> sY >> sZ >> shaderID >> modelID >> textureID >>
//animComp >> animSide;//!< String stream reads in file lines.


//}*/