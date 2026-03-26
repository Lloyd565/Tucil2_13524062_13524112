#include <bits/stdc++.h>
#include "parser.hpp"
#include "Octree.hpp"

using namespace std;
vector<Triangle*> newTriangles;
// D&C
Octree* buildOctree(const AABB& bbox,const vector<Triangle>& triangles,int currDepth,int maxDepth,int& voxelCnt,vector<int>& nodesPerDepth,vector<int>& prunedPerDepth)
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
            newTriangles.push_back(new Triangle(tri.v0, tri.v1, tri.v2));
        }
    }
    // Divide
    else {
        nodesPerDepth[currDepth]++;
        node = new Octree(bbox, false, false);
        vector<AABB> childBoxes = node->divideBB();
        for (int i = 0; i < 8; i++) {
            vector<Triangle> childTriangles;
            for (const Triangle& tri : triangles) {
                if (childBoxes[i].isIntersect(tri)) {
                    childTriangles.push_back(tri);
                }
            }
            node->children[i] = buildOctree(childBoxes[i], childTriangles,currDepth + 1, maxDepth,voxelCnt, nodesPerDepth, prunedPerDepth);
        }
    }

    return node;
}

// vector<Triangle*> getNewTriangles(const Octree& VoxelTree){
//     vector<Triangle*> newTriangles;
//     if (VoxelTree.isMaxDepth) { return }
// }
int findIndexPosition(const Point& Vertice, const vector<Point> verticeList){
    for (int i = 0; i < verticeList.size(); i++){
        if (verticeList[i] == Vertice){
            return i;
        }
    }
    return -1;
}
void VoxelWrite(const vector<Triangle*>& newTriangles, const vector<Point>& oldVertices, const string& outputPath) {
    vector<int> faceList;
    ofstream outFile;
    outFile.open(outputPath);
    if (!outFile) {
        cerr << "Error: Tidak dapat membuka file untuk ditulis." << endl;
        return;
    }
    for (int i = 0; i< newTriangles.size(); i++){
        Triangle* tri = newTriangles[i];
        outFile << "v " << tri->v0.x << " " << tri->v0.y << " " << tri->v0.z << endl;
        outFile << "v " << tri->v1.x << " " << tri->v1.y << " " << tri->v1.z << endl;
        outFile << "v " << tri->v2.x << " " << tri->v2.y << " " << tri->v2.z << endl;
        int idx0 = findIndexPosition(tri->v0, oldVertices);
        int idx1 = findIndexPosition(tri->v1, oldVertices);
        int idx2 = findIndexPosition(tri->v2, oldVertices);
        if (idx0 == -1 || idx1 == -1 || idx2 == -1){
            cerr << "Error: Vertice tidak ditemukan pada vertice list." << endl;
            return;
        }
        faceList.push_back(idx0 + 1);
        faceList.push_back(idx1 + 1);
        faceList.push_back(idx2 + 1);
    }
    for (int i = 0; i < faceList.size(); i+=3){
        outFile << "f " << faceList[i] << " " << faceList[i+1] << " " << faceList[i+2] << endl;
    }
    outFile.close();
}

int main() {
    string filepath;
    int maxDepth;
    cout << "Masukkan path file .obj: ";
    getline(cin, filepath);
    cout << "Masukkan maxDepth: ";
    cin >> maxDepth;

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
                               voxelCnt, nodesPerDepth, prunedPerDepth);
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

    outputPath = "ayam.obj";
    // TODO: VoxelWriter : tulis file output.obj
    VoxelWrite(newTriangles, parser.vertices, outputPath);
    // Bersihkan mem
    if (root != nullptr) {
        delete root;
    }
    return 0;
}