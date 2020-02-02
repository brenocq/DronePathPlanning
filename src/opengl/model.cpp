#include "model.h"

Model::Model(const std::string& _modelName, const std::string& _fileType):
	modelName(_modelName), fileType(_fileType)
{}

Model::~Model()
{}

void Model::loadModel()
{
	printf("Loading model %s\n",modelName.c_str());
	const std::string& fileName = "models/"+modelName+"/"+modelName+".obj";
	printf("file: %s\n",fileName.c_str());

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

	if(!scene)
	{
		printf("Model (%s) failed to load: %s", fileName.c_str(), importer.GetErrorString());
		return;
	}

	loadNode(scene->mRootNode, scene);
	loadMaterials(scene);
}

void Model::loadNode(aiNode *node, const aiScene *scene)
{
	for(int i=0; i<int(node->mNumMeshes); i++)
	{
		loadMesh(scene->mMeshes[node->mMeshes[i]], scene);
	}

	for(int i=0; i<int(node->mNumChildren); i++)
	{
		loadNode(node->mChildren[i], scene);
	}
}

void Model::loadMesh(aiMesh *mesh, const aiScene *scene)
{
	std::vector<GLfloat> vertices;
	std::vector<unsigned int> indices;

	for(int i=0; i<int(mesh->mNumVertices); i++)
	{
		vertices.insert(vertices.end(), {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z});
		// If texture coords exists...
		if(mesh->mTextureCoords[0])
		{
			vertices.insert(vertices.end(), {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
		}
		else
		{
			vertices.insert(vertices.end(), {0.0f, 0.0f});
		}
		vertices.insert(vertices.end(), {-mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z});
	}

	for(int i=0; i<int(mesh->mNumFaces); i++)
	{
		aiFace face = mesh->mFaces[i];
		for(int j=0; j<int(face.mNumIndices); j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	Mesh *newMesh = new Mesh();
	newMesh->createMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
	meshList.push_back(newMesh);
	meshToTex.push_back(mesh->mMaterialIndex);
}

void Model::loadMaterials(const aiScene *scene)
{
	textureList.resize(scene->mNumMaterials);

	for(int i=0; i<int(scene->mNumMaterials); i++)
	{
		aiMaterial *material = scene->mMaterials[i];	

		textureList[i] = nullptr;

		if(material->GetTextureCount(aiTextureType_DIFFUSE))
		{
			aiString path;
			if(material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
			{
				int idx = std::string(path.data).rfind("\\");
				std::string filename = std::string(path.data).substr(idx+1);	

				std::string texPath = std::string("textures/") + modelName + "/" + filename;

				textureList[i] = new Texture(texPath.c_str());

				if(fileType.compare("rgb")==0)
				{
					if(!textureList[i]->loadTexture())
					{
						printf("Failed to load texture(rgb) at: %s\n", texPath.c_str());
						delete textureList[i];
						textureList[i] = nullptr;
					}
				}else{
					if(!textureList[i]->loadTextureA())
					{
						printf("Failed to load texture(rgba) at: %s\n", texPath.c_str());
						delete textureList[i];
						textureList[i] = nullptr;
					}
				}
			}
		}
		if(!textureList[i])
		{
			textureList[i]=new Texture("textures/plain.png");
			textureList[i]->loadTextureA();
		}
	}
}

void Model::renderModel()
{
	for(int i=0; i<int(meshList.size()); i++)
	{
		unsigned int materialIndex = meshToTex[i];

		if(int(materialIndex)<int(textureList.size()) && textureList[materialIndex])
		{
			textureList[materialIndex]->useTexture();
		}

		meshList[i]->renderMesh();
	}
}

void Model::clearModel()
{
	for(int i=0; i<int(meshList.size()); i++)
	{
		if(meshList[i])
		{
			delete meshList[i];
			meshList[i] = nullptr;
		}
	}

	for(int i=0; i<int(textureList.size()); i++)
	{
		if(textureList[i])
		{
			delete textureList[i];
			textureList[i] = nullptr;
		}
	}
}

