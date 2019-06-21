#include "Global.h"
#include "LoadOBJ.h"


LoadOBJ::LoadOBJ( )
{ }

void LoadOBJ::GetModelFilename( char * filename )
{
	std::ifstream fin;
	fin.open( filename );
	TESTRESULT( !fin.good( ) );
}

void LoadOBJ::ReadFileCounts( char* filename, int& vertexCount, int& textureCount, int& normalCount, int& faceCount )
{
	std::ifstream fin;
	char input;

	// Initialize the counts.
	vertexCount = 0;
	textureCount = 0;
	normalCount = 0;
	faceCount = 0;

	// Open the file.
	fin.open( filename );

	// Check if it was successful in opening the file.
	TESTRESULT( ( fin.fail( ) ) );

	// Read from the file and continue to read until the end of the file is reached.
	fin.get( input );
	while( !fin.eof( ) )
	{
		// If the line starts with 'v' then count either the vertex, the texture coordinates, or the normal vector.
		if( input == 'v' )
		{
			fin.get( input );
			if( input == ' ' )
			{
				vertexCount++;
			}
			if( input == 't' )
			{
				textureCount++;
			}
			if( input == 'n' )
			{
				normalCount++;
			}
		}

		// If the line starts with 'f' then increment the face count.
		if( input == 'f' )
		{
			fin.get( input );
			if( input == ' ' )
			{
				faceCount++;
			}
		}

		// Otherwise read in the remainder of the line.
		while( input != '\n' )
		{
			fin.get( input );
		}

		// Start reading the beginning of the next line.
		fin.get( input );
	}

	// Close the file.
	fin.close( );
}

void LoadOBJ::LoadDataStructures( char* filename, int vertexCount, int textureCount, int normalCount, int faceCount )
{
	VertexType *vertices, *texcoords, *normals;
	FaceType *faces;
	std::ifstream fin;
	int vertexIndex, texcoordIndex, normalIndex, faceIndex, vIndex, tIndex, nIndex;
	char input, input2;
	std::ofstream fout;


	// Initialize the four data structures.
	vertices = new VertexType[vertexCount];
	TESTRESULT( !vertices );

	texcoords = new VertexType[textureCount];
	TESTRESULT( !texcoords );

	normals = new VertexType[normalCount];
	TESTRESULT( !normals );

	faces = new FaceType[faceCount];
	TESTRESULT( !faces );

	// Initialize the indexes.
	vertexIndex = 0;
	texcoordIndex = 0;
	normalIndex = 0;
	faceIndex = 0;

	// Open the file.
	fin.open( filename );

	// Check if it was successful in opening the file.
	TESTRESULT( fin.fail( ) );

	// Read in the vertices, texture coordinates, and normals into the data structures.
	// Important: Also convert to left hand coordinate system since Maya uses right hand coordinate system.
	fin.get( input );
	while( !fin.eof( ) )
	{
		if( input == 'v' )
		{
			fin.get( input );

			// Read in the vertices.
			if( input == ' ' )
			{
				fin >> vertices[vertexIndex].x >> vertices[vertexIndex].y >> vertices[vertexIndex].z;

				// Invert the Z vertex to change to left hand system.
				vertices[vertexIndex].z = vertices[vertexIndex].z * -1.0f;
				vertexIndex++;
			}

			// Read in the texture uv coordinates.
			if( input == 't' )
			{
				fin >> texcoords[texcoordIndex].x >> texcoords[texcoordIndex].y;

				// Invert the V texture coordinates to left hand system.
				texcoords[texcoordIndex].y = 1.0f - texcoords[texcoordIndex].y;
				texcoordIndex++;
			}

			// Read in the normals.
			if( input == 'n' )
			{
				fin >> normals[normalIndex].x >> normals[normalIndex].y >> normals[normalIndex].z;

				// Invert the Z normal to change to left hand system.
				normals[normalIndex].z = normals[normalIndex].z * -1.0f;
				normalIndex++;
			}
		}

		// Read in the faces.
		if( input == 'f' )
		{
			fin.get( input );
			if( input == ' ' )
			{
				// Read the face data in backwards to convert it to a left hand system from right hand system.
				fin
					>> faces[faceIndex].v3 >> input2 >> faces[faceIndex].t3 >> input2 >> faces[faceIndex].n3
					>> faces[faceIndex].v2 >> input2 >> faces[faceIndex].t2 >> input2 >> faces[faceIndex].n2
					>> faces[faceIndex].v1 >> input2 >> faces[faceIndex].t1 >> input2 >> faces[faceIndex].n1;
				faceIndex++;
			}
		}

		// Read in the remainder of the line.
		while( input != '\n' )
		{
			fin.get( input );
		}

		// Start reading the beginning of the next line.
		fin.get( input );
	}

	// Close the file.
	fin.close( );

	// Open the output file.
	fout.open( "model.txt" );

	// Write out the file header that our model format uses.
	fout
		<< "Vertex Count: " << ( faceCount * 3 ) << std::endl
		<< std::endl
		<< "Data:" << std::endl
		<< std::endl;

	// Now loop through all the faces and output the three vertices for each face.
	for( int i = 0; i < faceIndex; i++ )
	{
		vIndex = faces[i].v1 - 1;
		tIndex = faces[i].t1 - 1;
		nIndex = faces[i].n1 - 1;

		fout
			<< vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << std::endl;

		vIndex = faces[i].v2 - 1;
		tIndex = faces[i].t2 - 1;
		nIndex = faces[i].n2 - 1;

		fout
			<< vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << std::endl;

		vIndex = faces[i].v3 - 1;
		tIndex = faces[i].t3 - 1;
		nIndex = faces[i].n3 - 1;

		fout
			<< vertices[vIndex].x << ' ' << vertices[vIndex].y << ' ' << vertices[vIndex].z << ' '
			<< texcoords[tIndex].x << ' ' << texcoords[tIndex].y << ' '
			<< normals[nIndex].x << ' ' << normals[nIndex].y << ' ' << normals[nIndex].z << std::endl;
	}

	// Close the output file.
	fout.close( );

	// Release the four data structures.
	if( vertices )
	{
		delete[] vertices;
		vertices = nullptr;
	}
	if( texcoords )
	{
		delete[] texcoords;
		texcoords = nullptr;
	}
	if( normals )
	{
		delete[] normals;
		normals = nullptr;
	}
	if( faces )
	{
		delete[] faces;
		faces = nullptr;
	}
}
