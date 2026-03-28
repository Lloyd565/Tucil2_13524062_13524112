# Tucil2_13524062_13524112


## Deskripsi Program

Program ini mengkonversi model tiga dimensi berformat `.obj` menjadi representasi voxel — yaitu kumpulan kubus-kubus kecil seragam yang menyusun permukaan objek, seperti di Minecraft.

Konversi dilakukan menggunakan struktur data **Octree** dengan algoritma **Divide and Conquer**. Ruang tiga dimensi yang membungkus objek dibagi secara rekursif menjadi 8 sub-kubus pada setiap levelnya, hingga mencapai kedalaman maksimum yang ditentukan pengguna. Sub-kubus yang tidak bersentuhan dengan permukaan objek langsung dipangkas (*pruning*) untuk efisiensi.

Program menyediakan dua metode pengecekan interseksi:
- **AABBvsAABB** — pengecekan cepat menggunakan bounding box segitiga
- **SAT (Separating Axis Theorem)** — pengecekan presisi tinggi

### Struktur Repository

```
Tucil2_NIM1_NIM2/
├── src/
│   ├── main.cpp
│   ├── parser.hpp / parser.cpp
│   ├── Point.hpp
│   ├── Triangle.hpp
│   ├── AABB.hpp / AABB.cpp
│   ├── Octree.hpp / Octree.cpp
│   ├── TriangleMesh.hpp / TriangleMesh.cpp
├── test/
│   └── (file .obj hasil konversi untuk laporan)
├── doc/
│   └── laporan.pdf
└── README.md
```

---

## Requirement

| Kebutuhan | Keterangan |
|---|---|
| Compiler | `g++` dengan dukungan C++17 atau lebih baru |
| OS | Windows / Linux / macOS |
| Library | Standard library C++ |

Pastikan `g++` sudah terinstall:
```bash
g++ --version
```

Jika belum terinstall, pada Ubuntu/Debian:
```bash
sudo apt install g++
```

Pada Windows, gunakan [MinGW](https://www.mingw-w64.org/) atau [WSL](https://learn.microsoft.com/en-us/windows/wsl/).

---

## Cara Kompilasi

Jalankan perintah berikut dari folder utama project:

```bash
g++ -std=c++17 -O2 -o voxelizer src/main.cpp src/parser.cpp src/AABB.cpp src/Octree.cpp
```

Atau jika ingin menyimpan executable di folder `bin`:

```bash
g++ -std=c++17 -O2 -o bin/voxelizer src/main.cpp src/parser.cpp src/AABB.cpp src/Octree.cpp
```

---

## Cara Menjalankan Program

Jalankan executable yang sudah dikompilasi dari folder utama project:

```bash
./voxelizer
```

Jika executable disimpan di folder `bin`:

```bash
./bin/voxelizer
```

Program akan meminta input :

```
Masukkan path file .obj: test/pumpkin.obj
Masukkan maxDepth: 8
Pilih metode intersection (1: AABBvsAABB, 2: SAT): 2
```

### Input

| Input | Keterangan |
|---|---|
| Path file `.obj` | Path ke file obj|
| `maxDepth` | Kedalaman maksimum Octree (bilangan bulat ≥ 1)|
| Metode interseksi | `1` untuk AABBvsAABB, `2` untuk SAT|

### Pemilihan Depth

| Tujuan | Depth yang disarankan |
|---|---|
| Laporan | 7 – 8 |
| Stres test | 9 – 10 (pakai SAT) |

### Format File `.obj` yang Didukung

Program hanya memproses baris `v` (vertex) dan `f` (face segitiga):

```
v 2.229345 -0.992723 -0.862826
v 2.292449 -0.871852 -0.882400
v 2.410367 -0.777999 -0.841105
f 1 2 3
```

---

## Author

| Nama | NIM | Kelas |
|---|---|---|
| Nathan Edward Christofer Marpaung | 13524062 | K2 |
| Richard Samuel Simanullang | 13524112 | K2 |
