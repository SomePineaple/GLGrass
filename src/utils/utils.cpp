#include "utils.h"

#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <chrono>
#include <random>

std::string Utils::readFileToString(const char * filename) {
  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    std::cerr << "Could not open the file - '"
              << filename << "'" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::string contents((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
  return contents;
}

unsigned long Utils::currentTimeMillis() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

float Utils::randFloat(float min, float max) {
  std::random_device rd;
  std::default_random_engine eng(rd());
  std::uniform_real_distribution<float> distr(min, max);
  return distr(eng);
}

std::vector<Utils::Vertex> Utils::loadOBJ( std::istream& in ) {
  std::vector<Vertex> verts;

  std::vector< glm::vec4 > positions( 1, glm::vec4( 0, 0, 0, 0 ) );
  std::vector< glm::vec3 > normals( 1, glm::vec3( 0, 0, 0 ) );
  std::string lineStr;
  while( std::getline( in, lineStr ) ) {
    std::istringstream lineSS( lineStr );
    std::string lineType;
    lineSS >> lineType;

    // vertex
    if( lineType == "v" )
    {
        float x = 0, y = 0, z = 0, w = 1;
        lineSS >> x >> y >> z >> w;
        positions.push_back( glm::vec4( x, y, z, w ) );
    }

    // normal
    if( lineType == "vn" )
    {
        float i = 0, j = 0, k = 0;
        lineSS >> i >> j >> k;
        normals.push_back( glm::normalize( glm::vec3( i, j, k ) ) );
    }

    // polygon
    if( lineType == "f" ) {
      std::vector< VertRef > refs;
      std::string refStr;
      while( lineSS >> refStr ) {
        std::istringstream ref( refStr );
        std::string vStr, vtStr, vnStr;
        std::getline( ref, vStr, '/' );
        std::getline( ref, vtStr, '/' );
        std::getline( ref, vnStr, '/' );
        int v = atoi( vStr.c_str() );
        int vt = atoi( vtStr.c_str() );
        int vn = atoi( vnStr.c_str() );
        v  = (  v >= 0 ?  v : positions.size() +  v );
        vn = ( vn >= 0 ? vn : normals.size()   + vn );
        refs.push_back( VertRef( v, vt, vn ) );
      }

      // triangulate, assuming n>3-gons are convex and coplanar
      for( size_t i = 1; i+1 < refs.size(); ++i ) {
        const VertRef* p[3] = { &refs[0], &refs[i], &refs[i+1] };

        // http://www.opengl.org/wiki/Calculating_a_Surface_Normal
        glm::vec3 U( positions[ p[1]->v ] - positions[ p[0]->v ] );
        glm::vec3 V( positions[ p[2]->v ] - positions[ p[0]->v ] );
        glm::vec3 faceNormal = glm::normalize( glm::cross( U, V ) );

        for( size_t j = 0; j < 3; ++j ) {
          Vertex vert;
          vert.position = glm::vec3( positions[ p[j]->v ] );
          vert.normal = ( p[j]->vn != 0 ? normals[ p[j]->vn ] : faceNormal );
          verts.push_back( vert );
        }
      }
    }
  }

  return verts;
}
