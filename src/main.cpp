#include <bits/stdc++.h>
#include "parser.hpp"
#include "Octree.hpp"

using namespace std;
vector<AABB*> resultingVoxels;
// D&C
Octree* buildOctree(const AABB& bbox,const vector<Triangle>& triangles,int currDepth,int maxDepth,int& voxelCnt,vector<int>& nodesPerDepth,vector<int>& prunedPerDepth, bool useSAT)
{
    Octree* node = nullptr;
    // Base 1
    if (triangles.empty()) {
        prunedPerDepth[currDepth]++;
    }
    // Base 2
    else if (currDepth == maxDepth) {
        nodesPerDepth[currDepth]++;
        voxelCnt++;
        node = new Octree(bbox, true, true);
        for (const Triangle& tri : triangles){
            resultingVoxels.push_back(new AABB(bbox.minAABB, bbox.maxAABB));
        }
    }
    // Div
    else {
        nodesPerDepth[currDepth]++;
        node = new Octree(bbox, false, false);
        vector<AABB> childBoxes = node->divideBB();
        for (int i = 0; i < 8; i++) {
            vector<Triangle> childTriangles;
            for (const Triangle& tri : triangles) {
                bool intersect = useSAT ? childBoxes[i].isIntersectSAT(tri) : childBoxes[i].isIntersect(tri);
                if (intersect) {
                    childTriangles.push_back(tri);
                }
            }
            node->children[i] = buildOctree(childBoxes[i], childTriangles,currDepth + 1, maxDepth,voxelCnt, nodesPerDepth, prunedPerDepth, useSAT);
        }
    }

    return node;
}

int findIndexPosition(const Point& Vertice, const vector<Point> verticeList){
    for (int i = 0; i < verticeList.size(); i++){
        if (verticeList[i] == Vertice){
            return i;
        }
    }
    return -1;
}
void writeVoxels(Octree* node, std::ofstream& outF, int& currVertexIndex) {
    if (node == nullptr) return;
    if (node->isVoxel) {
        Point minP = node->BB.minAABB;
        Point maxP = node->BB.maxAABB;
        outF << "v " << minP.x << " " << minP.y << " " << minP.z << endl;
        outF << "v " << maxP.x << " " << minP.y << " " << minP.z << endl;
        outF << "v " << maxP.x << " " << maxP.y << " " << minP.z << endl;
        outF << "v " << minP.x << " " << maxP.y << " " << minP.z << endl;
        outF << "v " << minP.x << " " << minP.y << " " << maxP.z << endl;
        outF << "v " << maxP.x << " " << minP.y << " " << maxP.z << endl;
        outF << "v " << maxP.x << " " << maxP.y << " " << maxP.z << endl;
        outF << "v " << minP.x << " " << maxP.y << " " << maxP.z << endl;
        //face
        int v = currVertexIndex;         
        outF << "f " << v+1 << " " << v+2 << " " << v+3 << endl;
        outF << "f " << v+1 << " " << v+3 << " " << v+4 << endl;
        outF << "f " << v+5 << " " << v+8 << " " << v+7 << endl;
        outF << "f " << v+5 << " " << v+7 << " " << v+6 << endl;
        outF << "f " << v+1 << " " << v+5 << " " << v+6 << endl;
        outF << "f " << v+1 << " " << v+6 << " " << v+2 << endl;
        outF << "f " << v+4 << " " << v+3 << " " << v+7 << endl;
        outF << "f " << v+4 << " " << v+7 << " " << v+8 << endl;
        outF << "f " << v+1 << " " << v+4 << " " << v+8 << endl;
        outF << "f " << v+1 << " " << v+8 << " " << v+5 << endl;
        outF << "f " << v+2 << " " << v+6 << " " << v+7 << endl;
        outF << "f " << v+2 << " " << v+7 << " " << v+3 << endl;
        currVertexIndex += 8; 
        return;
    }
    for (int i = 0; i < 8; i++) {
        writeVoxels(node->children[i], outF, currVertexIndex);
    }
}


int main() {
    string filepath;
    int maxDepth;
    int method;
    cout << "Masukkan path file .obj: ";
    getline(cin, filepath);
    cout << "Masukkan maxDepth: ";
    cin >> maxDepth;
    cout << "Pilih metode intersection (1: AABBvsAABB, 2:SAT): ";
    cin >> method;
    bool useSAT = (method == 2);

    if (maxDepth < 1) {
        cerr << "Error:  harus >= 1." << endl;
        return 1;
    }

    Parser parser;
    try {
        parser.parse(filepath);
    } catch (const exception& e) {
        cerr << "Error parsing: " << e.what() << endl;
        return 1;
    }

    vector<Triangle> triangles;
    for (int i = 0; i + 2 < (int)parser.faces.size(); i += 3) {
        int idx0 = parser.faces[i] - 1;
        int idx1 = parser.faces[i+1] - 1;
        int idx2 = parser.faces[i+2] - 1;

        if (idx0 < 0 || idx0 >= (int)parser.vertices.size() ||
            idx1 < 0 || idx1 >= (int)parser.vertices.size() ||
            idx2 < 0 || idx2 >= (int)parser.vertices.size()) {
            cerr << "Error: Indeks face tidak valid pada face ke-" << (i/3 + 1) << endl;
            return 1;
        }

        triangles.push_back(Triangle(parser.vertices[idx0],
                                     parser.vertices[idx1],
                                     parser.vertices[idx2]));
    }

    Point minP = parser.vertices[0];
    Point maxP = parser.vertices[0];
    for (size_t i = 1; i < parser.vertices.size(); i++) {
        const Point& p = parser.vertices[i];
        minP.x = min(minP.x, p.x);
        minP.y = min(minP.y, p.y);
        minP.z = min(minP.z, p.z);
        maxP.x = max(maxP.x, p.x);
        maxP.y = max(maxP.y, p.y);
        maxP.z = max(maxP.z, p.z);
    }

    AABB rootBox(minP, maxP);
    rootBox = rootBox.makeUniCube();
    int voxelCnt = 0;
    vector<int> nodesPerDepth(maxDepth + 1, 0);
    vector<int> prunedPerDepth(maxDepth + 1, 0);

    //Build
    auto startTime = chrono::high_resolution_clock::now();
    Octree* root = buildOctree(rootBox, triangles, 1, maxDepth,
                               voxelCnt, nodesPerDepth, prunedPerDepth, useSAT);
    auto endTime = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsed = endTime - startTime;


    int vertexCnt = voxelCnt * 8;
    int faceCnt = voxelCnt * 12;
    string outputPath = "output.obj";
    cout << endl;
    cout << "============================================" << endl;
    cout << "         HASIL VOXELISASI OCTREE            " << endl;
    cout << "============================================" << endl;
    cout << "Banyaknya voxel   : " << voxelCnt << endl;
    cout << "Banyaknya vertex  : " << vertexCnt << endl;
    cout << "Banyaknya faces   : " << faceCnt << endl;
    cout << endl;

    cout << "--- Statistik Node Octree Terbentuk ---" << endl;
    for (int d = 1; d <= maxDepth; d++) {
        cout << d << " : " << nodesPerDepth[d] << endl;
    }
    cout << endl;

    cout << "--- Statistik Node Tidak Perlu Ditelusuri ---" << endl;
    for (int d = 1; d <= maxDepth; d++) {
        cout << d << " : " << prunedPerDepth[d] << endl;
    }
    cout << endl;

    cout << "Kedalaman octree  : " << maxDepth << endl;
    cout << "Waktu eksekusi    : " << elapsed.count() << " ms" << endl;
    cout << "Output disimpan di: " << outputPath << endl;
    cout << "============================================" << endl;

    outputPath = "output.obj";
    std::ofstream outFile("output.obj");
    if (outFile.is_open()) {
        int startIdx = 0;
        writeVoxels(root, outFile, startIdx);
        outFile.close();
        std::cout << "File Voxel berhasil ditulis ke: output.obj\n";
    }

    // Bersihkan mem
    if (root != nullptr) {
        delete root;
    }
    return 0;
}