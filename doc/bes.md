This document describes BES files.

File format
===========

* all strings are terminated by NULL characters
* length of every string includes NULL character

This file is made of:
* Header
* Preview
* Data

Header
------

Total size: 16

| Offset | Name      | Type     |
|--------|-----------|----------|
| 0      | Signature | CHAR[4]  |
| 4      | Version   | CHAR[5]  |
| 9      | Unknown   | UINT32LE |
| 13     | Unknown   | CHAR[3]  |

1. Signature identifying the BES file. Contains fixed string 'BES' with NULL character at the end (0x42 0x45 0x53 0x00).
2. Version of this BES file. VietCong knows following versions:
  - 0004 (0x30 0x30 0x30 0x34 0x00)
  - 0005 (0x30 0x30 0x30 0x35 0x00)
  - 0006 (0x30 0x30 0x30 0x36 0x00)
  - 0007 (0x30 0x30 0x30 0x37 0x00)
  - 0008 (0x30 0x30 0x30 0x38 0x00)
  - 0100 (0x30 0x31 0x30 0x30 0x00)
3. Unknown word (or four chars?).
4. Unknown (always zeros).

Preview
-------

Total size: 12288 (0x3000)

This block contains preview image made by 3D modelling tool.
Preview image is made of 64x64 pixels, where every pixel is the following format:

| Offset | Name      | Type  |
|--------|-----------|-------|
| 0      | Green     | UINT8 |
| 1      | Blue      | UINT8 |
| 2      | Red       | UINT8 |

Data
----

Data block contains several sub-blocks.
Each sub-block contain it's label, size and data itself.

Here is quick reference table of known data sub-blocks:

| Block Name     | Label  |
|----------------|--------|
| Object         | 0x0001 |
| ...            | ...    |
| Unknown 0x030  | 0x0030 |
| Mesh           | 0x0031 |
| Vertices       | 0x0032 |
| Faces          | 0x0033 |
| Properties     | 0x0034 |
| Unknown 0x035  | 0x0035 |
| Unknown 0x036  | 0x0036 |
| ...            | ...    |
| Unknown 0x038  | 0x0038 |
| ...            | ...    |
| User Info      | 0x0070 |
| ...            | ...    |
| Material       | 0x1000 |
| Bitmap         | 0x1001 |
| PteroMat       | 0x1002 |

### Object

| Offset | Name            | Type     |
|--------|-----------------|----------|
| 0      | Label           | UINT32LE |
| 4      | Blok size       | UINT32LE |
| 8      | Object children | UINT32LE |
| 12     | Name length     | UINT32   |
| 16     | Name            | CHAR[]   |

1. Label of this sub-block - always 0x001
2. Size of this sub-block (including this field and label)
3. Number of 'Object' sub-blocks inside of this one
4. Length of 'Name' string
5. Name

Other data sub-blocks may follow. Known sub-blocks:
* Object
* Unknown 0x030
* Material

### Unknown 0x030

| Offset | Name          | Type     |
|--------|---------------|----------|
| 0      | Label         | UINT32LE |
| 4      | Blok size     | UINT32LE |
| 8      | Mesh children | UINT32LE |

1. Label of this sub-block - always 0x030
2. Size of this sub-block (including this field and label)
3. Number of children meshes inside of this block

Other data sub-blocks may follow. Known sub-blocks:
* Mesh
* Properties
* Unknown 0x035
* Unknown 0x036

### Mesh

| Offset | Name      | Type     |
|--------|-----------|----------|
| 0      | Label     | UINT32LE |
| 4      | Blok size | UINT32LE |
| 8      | Material  | UINT32LE |

1. Label of this sub-block - always 0x031
2. Size of this sub-block (including this field and label)
3. Material ID (popints to the one of children of 'Material' data block) used by this mesh.
Value 0xFFFFFFFF if no material is used.

Other data sub-blocks may follow. Known sub-blocks:
* Vertices
* Faces

### Vertices

| Offset | Name           | Type     |
|--------|----------------|----------|
| 0      | Label          | UINT32LE |
| 4      | Blok size      | UINT32LE |
| 8      | Vertices count | UINT32LE |
| 12     | Size of vertex | UINT32LE |
| 16     | Unknown        | UINT32LE |

1. Label of this sub-block - always 0x032
2. Size of this sub-block (including this field and label)
3. Number of vertices in this data block
4. Size of vertex structure
5. Unknown - usually 0x12 or 0x112

Vertices data structures follows:

| Offset | Name       | Type      |
|--------|------------|-----------|
| 0      | Position x | FLOAT32LE |
| 4      | Position y | FLOAT32LE |
| 8      | Position z | FLOAT32LE |
| 12     | Unknown    | CHAR[]    |

1. 'X' vertex coordinate.
2. 'Y' vertex coordinate.
3. 'Z' vertex coordinate.
4. Unknown

### Faces

This block contains object faces.
Every face is made of 3 vertices (a, b, c).
Vertex value points to vertex ID in 'Vertices' data block.

| Offset | Name        | Type     |
|--------|-------------|----------|
| 0      | Label       | UINT32LE |
| 4      | Blok size   | UINT32LE |
| 8      | Faces count | UINT32LE |

1. Label of this sub-block - always 0x033
2. Size of this sub-block (including this field and label)
3. Number of faces in this data block

Faces data structures follows (size of each structure is 12 bytes):

| Offset | Name     | Type     |
|--------|----------|----------|
| 0      | Vertex a | UINT32LE |
| 4      | Vertex b | UINT32LE |
| 8      | Vertex c | UINT32LE |

1. Vertex 'a'
2. Vertex 'b'
3. Vertex 'c'

### Properties

This block contains User defined properties (as known from 3D Studio Max).
Purpose of these properties is unknown.

| Offset | Name        | Type     |
|--------|-------------|----------|
| 0      | Label       | UINT32LE |
| 4      | Blok size   | UINT32LE |
| 8      | Text length | UINT32LE |
| 12     | Text        | CHAR[]   |

1. Label of this sub-block - always 0x034
2. Size of this sub-block (including this field and label)
3. Length of 'Text' string
4. String containing user defined properties

### Unknown 0x035

| Offset | Name      | Type         |
|--------|-----------|--------------|
| 0      | Label     | UINT32LE     |
| 4      | Blok size | UINT32LE     |
| 8      | Position1 | FLOAT32LE[3] |
| 20     | Unknown1  | CHAR[64]     |
| 84     | Position2 | FLOAT32LE[3] |
| 96     | Unknown2  | CHAR[4]      |

1. Label of this sub-block - always 0x035
2. Size of this sub-block (including this field and label) - always 0x64 (100B)
3. Object position in scene - coordinates are in the following order: x, y, z
4. Unknown
5. Same values as 3.
6. Unknown - usually 0x3F800000

### Unknown 0x036

| Offset | Name      | Type     |
|--------|-----------|----------|
| 0      | Label     | UINT32LE |
| 4      | Blok size | UINT32LE |
| 8      | Unknown   | UINT32LE |

1. Label of this sub-block - always 0x036
2. Size of this sub-block (including this field and label)
3. Unknown

### Unknown 0x038

| Offset | Name      | Type     |
|--------|-----------|----------|
| 0      | Label     | UINT32LE |
| 4      | Blok size | UINT32LE |
| 8      | Unknown   | CHAR[]   |

1. Label of this sub-block - always 0x038
2. Size of this sub-block (including this field and label)
3. Unknown

### User info

Space between 'Name' and 'Comment' is filled with zeros


| Offset | Name           | Type     |
|--------|----------------|----------|
| 0      | Label          | UINT32LE |
| 4      | Blok size      | UINT32LE |
| 8      | Name length    | UINT32LE |
| 12     | Comment length | UINT32LE |
| 16     | Unknown        | UINT32LE |
| 20     | Name           | CHAR[]   |
| 84     | Comment        | CHAR[]   |

1. Label of this sub-block - always 0x070
2. Size of this sub-block (including this field and label)
3. Length of 'Name' string. Should not exceed 64 bytes.
4. Length of 'Comment' string.
5. Unknown
6. Name (max 64)
7. Comment

### Material

| Offset | Name              | Type     |
|--------|-------------------|----------|
| 0      | Label             | UINT32LE |
| 4      | Block size        | UINT32LE |
| 8      | Material children | UINT32LE |

1. Label of this sub-block - always 0x1000
2. Size of this sub-block (including this field and label)
3. Number of materials inside of this block

Other data sub-blocks may follow. Known sub-blocks:
* Bitmap
* PteroMat

### Bitmap

| Offset | Name        | Type     |
|--------|-------------|----------|
| 0      | Label       | UINT32LE |
| 4      | Block size  | UINT32LE |
| 8      | Unknown1    | UINT32LE |
| 12     | Unknown2    | UINT32LE |
| 16     | Type        | UINT32LE |

1. Label of this sub-block - always 0x1001
2. Size of this sub-block (including this field and label)
3. Unknown
4. Unknown
5. Map type bitfield.
Here is a sorted list of maps contained in this bitmap:
  * 0 - Diffuse Color
  * 1 - Displacement
  * 2 - Bump
  * 3 - Ambient Color
  * 4 - Specular Color
  * 5 - Specular Level
  * 6 - Glossiness
  * 7 - Self-Illumination
  * 8 - Unknown
  * 9 - Filter Color
  * 10 - Reflection
  * 11 - Refraction

Set bit in field 'Type' indicates that bitmap contains appropriate map.
All maps have the same structure:

| Offset | Name        | Type     |
|--------|-------------|----------|
| 0      | Name length | UINT32LE |
| 4      | Coordinates | UINT32LE |
| 8      | Name        | CHAR[]   |

1. Length of 'Name' string
2. Coordinates configuration bitfield.
Tile and mirror can not be used at the same time.
  *  0 - U tile
  *  1 - V tile
  *  2 - U mirror
  *  3 - V mirror
3. Name of bitmap file

### PteroMat

| Offset | Name         | Type     |
|--------|--------------|----------|
| 0      | Label        | UINT32LE |
| 4      | Block size   | UINT32LE |
| 8      | Sides        | UINT32LE |
| 12     | Type         | UINT32LE |
| 16     | CollisionMat | CHAR[4]  |
| 20     | Unknown      | UINT32LE |
| 24     | Vegetation   | CHAR[4]  |
| 28     | Name length  | UINT32LE |
| 32     | Name         | CHAR[]   |

Some other data may follow.

1. Label of this sub-block - always 0x1002
2. Size of this sub-block (including this field and label)
3. Number of material sizes: 0 = 1 sided, 1 = 2-sided. Other values are invalid.
4. Texture type bitfield. Here is a sorted list of textures contained in this material:
  * 16 - Diffuse #1 - Ground
  * 17 - Diffuse #2 - Multitexture
  * 18 - Diffuse #3 - Overlay
  * 19 - Environment #1
  * 20 - LightMap
  * 21 - Unknown
  * 22 - Environment #2
  * 23 - LightMap (Engine Lights)
5. Collision Material (only first 2 bytes are valid, the rest are zeros)
6. Unknown
Here is description of some **bytes** - bytes not listed here are always zero:
  * 0 - unknown
  * 1 - unknown
  * 2 - Type of transparent (represented by value):
    * 0: - none - (opaque)
    * 1: #0 - transparent, zbufwrite, sort
    * 2: #1 - transparent, zbufwrite, sort, 1-bit alpha
    * 3: #2 - translucent, no\_zbufwrite, sort
    * 4: #3 - transparent, zbufwrite, nosort, 1-bit alpha
    * 5: #4 - translucent, add with background, no\_zbufwrite, sort
  * 3 - unknown
7. Grow/Grass Type (only first 2 **bytes** are valid, the rest are zeros)
  * 0 - Grow Type
  * 1 - Grass Type
8. Length of 'Name' string
9. Material name

Set bit in field 'Type' indicates that PteroMat contains appropriate texture.
All textures have the same structure:

| Offset | Name        | Type     |
|--------|-------------|----------|
| 0      | Coordinates | UINT32LE |
| 4      | Name length | UINT32LE |
| 8      | Name        | CHAR[]   |

1. Coordinates configuration bitfield.
Upper 4 bytes should be equal to PteroMat's 'Type' field (but it is not always true - probably due some bug in 3DS Max).
Meaning of lower 4 bytes follows (all bits except those listed here are always zero):
  * 0 - U tile
  * 1 - V tile
  * 4 - unknown
2. Length of 'Name' string
3. Name of texture file

