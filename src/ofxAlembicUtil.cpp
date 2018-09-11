#include "ofxAlembicUtil.h"

#include "H5public.h"

static bool inited = false;

void ofxAlembic::init()
{
	if (inited) return;
	inited = true;
	
	ofLogVerbose("ofxAlembic") << "alembic version: " << Alembic::Abc::GetLibraryVersionShort();
	
	H5dont_atexit();
}

void ofxAlembic::transform(ofMesh &mesh, const ofMatrix4x4 &m)
{
    vector<glm::vec3>& vertices = mesh.getVertices();
    glm::mat4x4 mGlm = m;

	for (int i = 0; i < vertices.size(); i++)
	{
        vertices[i] = mGlm * glm::vec4(vertices[i], 0);
	}

	if (mesh.hasNormals())
	{
		vector<glm::vec3>& normals = mesh.getNormals();

		for (int i = 0; i < normals.size(); i++)
		{
			const ofVec3f& v = normals[i];
            normals[i] = glm::vec4(v.x, v.y, v.z, 0) * mGlm;
		}
	}
}

vector<ofVec3f> toOf(const vector<ofxAlembic::Point>& v)
{
	vector<ofVec3f> arr(v.size());
	for (int i = 0; i < v.size(); i++)
		arr[i] = v[i].pos;

	return arr;
}
