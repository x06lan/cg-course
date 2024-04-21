#include <fstream>
#include <sstream>
#include <vector>
#include <random>
// #include <stdio>

struct  Vector3d
{
    float x=0.0;
    float y=0.0;
    float z=0.0;
};


struct FaceIndices {
    int v1, v2, v3;
};
class BoundBox{
    public:
    Vector3d center;
    Vector3d right_top;
    Vector3d left_bottom;
    void push_point(Vector3d vertex){
        if (vertex.x > right_top.x){
            right_top.x = vertex.x;
        }else if(vertex.x < left_bottom.x){
            left_bottom.x = vertex.x;
        }
        if (vertex.y > right_top.y){
            right_top.y = vertex.y;
        }else if(vertex.y < left_bottom.y){
            left_bottom.y = vertex.y;
        }
        if (vertex.z > right_top.z){
            right_top.z = vertex.z;
        }else if(vertex.z < left_bottom.z){
            left_bottom.z = vertex.z;
        }
    }
    void update_center(){
        center={left_bottom.x + (right_top.x - left_bottom.x)/2, left_bottom.y + (right_top.y - left_bottom.y)/2, left_bottom.z + (right_top.z - left_bottom.z)/2}; 
    }
    float get_radius(){
        this->update_center();
        return sqrt(pow(right_top.x - center.x, 2) + pow(right_top.y - center.y, 2) + pow(right_top.z - center.z, 2));
    }
};

float generateRandomFloat(int seed) {
    std::mt19937 gen(seed);  // Mersenne Twister random number engine with seed
    std::uniform_real_distribution<float> dist(0.0f, 1.0f); // Uniform distribution between 0.0 and 1.0
    return dist(gen);
}

void readObj(const std::string& filename, std::vector<Vector3d>& vertices, std::vector<FaceIndices>& faces, BoundBox& box) {
    std::ifstream in(filename);
    std::string line;


    while (std::getline(in, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            Vector3d vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            // printf("x=%.2f,y=%.2f,z=%.2f\n", vertex.x, vertex.y, vertex.z);
            
            box.push_point(vertex);
            
            vertices.push_back(vertex);
        } else if (prefix == "f") {
            FaceIndices face;
            iss >> face.v1 >> face.v2 >> face.v3;
            // printf("v1=%d,v2=%d,v3=%d\n", face.v1, face.v2, face.v3);
            faces.push_back(face);
        }
        else{
            iss.ignore();
        }
    }
    box.update_center();
}

void drawObj( std::vector<Vector3d>& vertices, std::vector<FaceIndices>& faces,unsigned int renderMode,int renderColor){
    // std::random_device rd;
    // std::mt19937 e2(rd());
    // std::uniform_real_distribution<float> dist(0.0, 1.0);

    if(renderMode==GL_TRIANGLES || renderMode==GL_LINES){
        for(int i=0;i<faces.size();i++){
            Vector3d v1 = vertices[faces[i].v1 - 1];
            Vector3d v2 = vertices[faces[i].v2 - 1];
            Vector3d v3 = vertices[faces[i].v3 - 1];
            if(renderMode==GL_TRIANGLES){
                glBegin(renderMode);
                if (renderColor == 0)
                    glColor3f(1.0, 1.0, 1.0);
                else 
                    glColor3f(generateRandomFloat(i*3),generateRandomFloat(i*3+1),generateRandomFloat(i*3+2));
                // glTexCoord2f(1.0f, 1.0f);
                glVertex3f(v1.x, v1.y, v1.z);
                // glTexCoord2f(1.0f, 1.0f);
                glVertex3f(v2.x, v2.y, v2.z);
                // glTexCoord2f(1.0f, 1.0f);
                glVertex3f(v3.x, v3.y, v3.z);
                glEnd();
            }
            else if(renderMode ==GL_LINES){
                glBegin(renderMode);

                if (renderColor == 0)
                    glColor3f(1.0, 1.0, 1.0);
                else 
                    glColor3f(generateRandomFloat(i*3),generateRandomFloat(i*3+1),generateRandomFloat(i*3+2));
                glVertex3f(v1.x, v1.y, v1.z);
                glVertex3f(v2.x, v2.y, v2.z);
                glEnd();

                glBegin(renderMode);
                glVertex3f(v2.x, v2.y, v2.z);
                glVertex3f(v3.x, v3.y, v3.z);
                glEnd();

                glBegin(renderMode);
                glVertex3f(v1.x, v1.y, v1.z);
                glVertex3f(v2.x, v2.y, v2.z);
                glEnd();
            }
        }
    }
    else if (renderMode == GL_POINTS){
        for(int i=0;i<vertices.size();i++){
            Vector3d v = vertices[i];
            glPointSize(10);
            if (renderColor == 0)
                glColor3f(1.0, 1.0, 1.0);
            else 
                glColor3f(generateRandomFloat(i*3),generateRandomFloat(i*3+1),generateRandomFloat(i*3+2));

            glBegin(renderMode);
            glVertex3f(v.x, v.y, v.z);
            glEnd();
        }
    }

}

