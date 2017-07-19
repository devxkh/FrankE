using System;
using System.Collections.Generic;
using System.Text;

//using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using System.IO;
using System.Text;
using VEX.Interface.Scene.Services;
using VEX.Core.Shared.Model.UI.Helper;
using System.Linq;

namespace VEX.Core.Shared.Utility
{
    /* This version of ObjImporter first reads through the entire file, getting a count of how large
   * the final arrays will be, and then uses standard arrays for everything (as opposed to ArrayLists
   * or any other fancy things). 
   */
    public class ObjMesh
    {
        public Vector3[] vertices { get; set; }
        public Vector2[] uv { get; set; }
        public Vector3[] normals { get; set; }
      //  public int[] triangles { get; set; }
        public int[] indices { get; set; }
    }

    public class ObjImporter
    {

        private struct meshStruct
        {
            public Vector3[] vertices;
            public Vector3[] normals;
            public Vector2[] uv;
            public Vector2[] uv1;
            public Vector2[] uv2;
            public int[] indices;
            public int[] faceVerts;
            public int[] faceUVs;
            public Vector3[] faceData;
            public string name;
            public string fileName;
        }

        // Use this for initialization
        public ObjMesh ImportFile(string filePath)
        {
            meshStruct newMesh = createMeshStruct(filePath);
            populateMeshStruct(ref newMesh);

            Vector3[] newVerts = new Vector3[newMesh.faceData.Length];
            Vector2[] newUVs = new Vector2[newMesh.faceData.Length];
            Vector3[] newNormals = new Vector3[newMesh.faceData.Length];
            int i = 0;
            /* The following foreach loops through the facedata and assigns the appropriate vertex, uv, or normal
             * for the appropriate Unity mesh array.
             */
            foreach (Vector3 v in newMesh.faceData)
            {
                newVerts[i] = newMesh.vertices[(int)v.X - 1];
                if (v.Y >= 1)
                    newUVs[i] = newMesh.uv[(int)v.Y - 1];

                if (v.Z >= 1)
                    newNormals[i] = newMesh.normals[(int)v.Z - 1];
                i++;
            }

            ObjMesh mesh = new ObjMesh();

            mesh.vertices = newVerts;
            mesh.uv = newUVs;
            mesh.normals = newNormals;
            mesh.indices = newMesh.indices;

            //mesh.RecalculateBounds();
            //mesh.Optimize();
      //      mesh = Optimize(mesh);

            SaveToBinaryFile(mesh);

            return mesh;
        }

        private void SaveToBinaryFile(ObjMesh mesh)
        {
            // Create the new, empty data file.
            string fileName = @"F:\Projekte\coop\obj2gltf\1.data";
            //if (File.Exists(fileName))
            //{
            //    Console.WriteLine(fileName + " already exists!");
            //    return;
            //}
            FileStream fs = new FileStream(fileName, FileMode.Create);
            // Create the writer for data.
            StreamWriter w = new StreamWriter(fs);
           // BinaryWriter w = new BinaryWriter(fs);
            // Write data to Test.data.
            foreach (var vertex in mesh.vertices)
            {
                var test = (Single)vertex.X;
                w.WriteLine(vertex.X.ToString("G17"));
                w.WriteLine(vertex.Y.ToString("G17"));
                w.WriteLine(vertex.Z.ToString("G17"));
            }

            foreach (var normal in mesh.normals)
            {
                w.WriteLine(normal.X.ToString("G17"));
                w.WriteLine(normal.Y.ToString("G17"));
                w.WriteLine(normal.Z.ToString("G17"));
            }

            foreach (var uv in mesh.uv)
            {
                w.WriteLine(uv.X.ToString("G17"));
                w.WriteLine(uv.Y.ToString("G17"));
            }

            foreach (var index in mesh.indices)
            {
                w.WriteLine((Int32)index);
            }

            //for (int i = 0; i < mesh.vertices.Length; i++)
            //{
            //    w.Write((int)mesh.vertices[i);
            //}
            w.Close();
            fs.Close();
           
            // Create the reader for data.
            //fs = new FileStream(fileName, FileMode.Open, FileAccess.Read);
            //BinaryReader r = new BinaryReader(fs);
            //// Read data from Test.data.
            //for (int i = 0; i < 11; i++)
            //{
            //    Console.WriteLine(r.ReadInt32());
            //}
            //r.Close();
            //fs.Close();
        }

        private ObjMesh Optimize(ObjMesh mesh)
        {
            Vector3 v;
            Vector3 v2;
            for (int i = 0; i < mesh.vertices.Length; i++)
            {
                v = mesh.vertices[i];
                for (int j = i + 1; j < mesh.vertices.Length; j++)
                {
                    v2 = mesh.vertices[j];
                    if (v.X == v2.X && v.Y == v2.Y && v.Z == v2.Z)
                    {
                        for (int ind = 0; ind < mesh.indices.Length; ind++)
                        {
                            if (mesh.indices[ind] == j)
                            {
                                mesh.indices[ind] = i;
                            }
                            else if (mesh.indices[ind] > j && mesh.indices[ind] > 0)
                                mesh.indices[ind]--;
                        }

                        var verticesList = mesh.vertices.ToList();
                        verticesList.RemoveAt(j);
                        mesh.vertices = verticesList.ToArray();

                        var uvList = mesh.uv.ToList();
                        uvList.RemoveAt(j);
                        mesh.uv = uvList.ToArray();

                        var normalsList = mesh.normals.ToList();
                        normalsList.RemoveAt(j);
                        mesh.normals = normalsList.ToArray();
                    }
                }
            }

            return mesh;
        }


        private static meshStruct createMeshStruct(string filename)
        {
            int triangles = 0;
            int vertices = 0;
            int vt = 0;
            int vn = 0;
            int face = 0;
            meshStruct mesh = new meshStruct();
            mesh.fileName = filename;
            StreamReader stream = File.OpenText(filename);
            string entireText = stream.ReadToEnd();
            stream.Close();
            using (StringReader reader = new StringReader(entireText))
            {
                string currentText = reader.ReadLine();
                char[] splitIdentifier = { ' ' };
                string[] brokenString;
                while (currentText != null)
                {
                    if (!currentText.StartsWith("f ") && !currentText.StartsWith("v ") && !currentText.StartsWith("vt ")
                        && !currentText.StartsWith("vn "))
                    {
                        currentText = reader.ReadLine();
                        if (currentText != null)
                        {
                            currentText = currentText.Replace("  ", " ");
                        }
                    }
                    else
                    {
                        currentText = currentText.Trim();                           //Trim the current line
                        brokenString = currentText.Split(splitIdentifier, 50);      //Split the line into an array, separating the original line by blank spaces
                        switch (brokenString[0])
                        {
                            case "v":
                                vertices++;
                                break;
                            case "vt":
                                vt++;
                                break;
                            case "vn":
                                vn++;
                                break;
                            case "f":
                                face = face + brokenString.Length - 1;
                                triangles = triangles + 3 * (brokenString.Length - 2); /*brokenString.Length is 3 or greater since a face must have at least
                                                                                     3 vertices.  For each additional vertice, there is an additional
                                                                                     triangle in the mesh (hence this formula).*/
                                break;
                        }
                        currentText = reader.ReadLine();
                        if (currentText != null)
                        {
                            currentText = currentText.Replace("  ", " ");
                        }
                    }
                }
            }
            mesh.indices = new int[triangles];
            mesh.vertices = new Vector3[vertices];
            mesh.uv = new Vector2[vt];
            mesh.normals = new Vector3[vn];
            mesh.faceData = new Vector3[face];
            return mesh;
        }

        private static void populateMeshStruct(ref meshStruct mesh)
        {
            StreamReader stream = File.OpenText(mesh.fileName);
            string entireText = stream.ReadToEnd();
            stream.Close();
            using (StringReader reader = new StringReader(entireText))
            {
                string currentText = reader.ReadLine();

                char[] splitIdentifier = { ' ' };
                char[] splitIdentifier2 = { '/' };
                string[] brokenString;
                string[] brokenBrokenString;
                int f = 0;
                int f2 = 0;
                int v = 0;
                int vn = 0;
                int vt = 0;
                int vt1 = 0;
                int vt2 = 0;
                while (currentText != null)
                {
                    if (!currentText.StartsWith("f ") && !currentText.StartsWith("v ") && !currentText.StartsWith("vt ") &&
                        !currentText.StartsWith("vn ") && !currentText.StartsWith("g ") && !currentText.StartsWith("usemtl ") &&
                        !currentText.StartsWith("mtllib ") && !currentText.StartsWith("vt1 ") && !currentText.StartsWith("vt2 ") &&
                        !currentText.StartsWith("vc ") && !currentText.StartsWith("usemap "))
                    {
                        currentText = reader.ReadLine();
                        if (currentText != null)
                        {
                            currentText = currentText.Replace("  ", " ");
                        }
                    }
                    else
                    {
                        currentText = currentText.Trim();
                        brokenString = currentText.Split(splitIdentifier, 50);
                        switch (brokenString[0])
                        {
                            case "g":
                                break;
                            case "usemtl":
                                break;
                            case "usemap":
                                break;
                            case "mtllib":
                                break;
                            case "v":
                                mesh.vertices[v] = new Vector3(System.Convert.ToSingle(brokenString[1]), System.Convert.ToSingle(brokenString[2]),
                                                         System.Convert.ToSingle(brokenString[3]));
                                v++;
                                break;
                            case "vt":
                                mesh.uv[vt] = new Vector2(System.Convert.ToSingle(brokenString[1]), System.Convert.ToSingle(brokenString[2]));
                                vt++;
                                break;
                            case "vt1":
                                mesh.uv[vt1] = new Vector2(System.Convert.ToSingle(brokenString[1]), System.Convert.ToSingle(brokenString[2]));
                                vt1++;
                                break;
                            case "vt2":
                                mesh.uv[vt2] = new Vector2(System.Convert.ToSingle(brokenString[1]), System.Convert.ToSingle(brokenString[2]));
                                vt2++;
                                break;
                            case "vn":
                                mesh.normals[vn] = new Vector3(System.Convert.ToSingle(brokenString[1]), System.Convert.ToSingle(brokenString[2]),
                                                        System.Convert.ToSingle(brokenString[3]));
                                vn++;
                                break;
                            case "vc":
                                break;
                            case "f":

                                int j = 1;
                                List<int> intArray = new List<int>();
                                while (j < brokenString.Length && ("" + brokenString[j]).Length > 0)
                                {
                                    Vector3 temp = new Vector3();
                                    brokenBrokenString = brokenString[j].Split(splitIdentifier2, 3);    //Separate the face into individual components (vert, uv, normal)
                                    temp.X = System.Convert.ToInt32(brokenBrokenString[0]);
                                    if (brokenBrokenString.Length > 1)                                  //Some .obj files skip UV and normal
                                    {
                                        if (brokenBrokenString[1] != "")                                    //Some .obj files skip the uv and not the normal
                                        {
                                            temp.Y = System.Convert.ToInt32(brokenBrokenString[1]);
                                        }
                                        temp.Z = System.Convert.ToInt32(brokenBrokenString[2]);
                                    }
                                    j++;

                                    mesh.faceData[f2] = temp;
                                    intArray.Add(f2);
                                    f2++;
                                }
                                j = 1;
                                while (j + 2 < brokenString.Length)     //Create triangles out of the face data.  There will generally be more than 1 triangle per face.
                                {
                                    mesh.indices[f] = intArray[0];
                                    f++;
                                    mesh.indices[f] = intArray[j];
                                    f++;
                                    mesh.indices[f] = intArray[j + 1];
                                    f++;

                                    j++;
                                }
                                break;
                        }
                        currentText = reader.ReadLine();
                        if (currentText != null)
                        {
                            currentText = currentText.Replace("  ", " ");       //Some .obj files insert double spaces, this removes them.
                        }
                    }
                }
            }
        }
    }
}
