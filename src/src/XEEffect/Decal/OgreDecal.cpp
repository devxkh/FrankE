#include <XEEffect/Decal/OgreDecal.hpp>
#include <cassert>

#include <Ogre/OgreMain/include/OgreManualObject.h>

namespace XE
{

	//DecalGenerator DecalGenerator::mInstance;

	/// Set "true" for smooth shading (more efficient) and "false" for flat shading (less efficient)
	/// If "true", each face will share vertex indicies with averaged normals
	/// If set to "false", each face will need to send duplicated vertex information
	const bool SHARE_VERTEX_NORMALS = true;

	/// Set "true" to save debug drawing information
	/// Should be "false" by default, unless you intend to draw debugging info
	/// You should not enable debug drawing for dynamic decals
	const bool DEBUG_ENABLED = false;

	/// OgreMesh constructor
	OgreMesh::OgreMesh(const Ogre::v1::MeshPtr& mesh, const Ogre::Vector3& scale)
	{
		initialize(mesh, scale);
	}

	/// Extracts all of the triangles from the mesh and places them in a nice, easy-to-read vector
	/// Note that position and orientaiton are not used here, although any future support for that is welcome.
	void OgreMesh::initialize(const Ogre::v1::MeshPtr& mesh, const Ogre::Vector3& scale)
	{
		extractTrianglesFromMesh(meshTriangles, mesh, Ogre::Vector3::ZERO, Ogre::Quaternion::IDENTITY, scale);
	}

	/// Finds all of the trangles in the AABB by brute force. 
	void OgreMesh::findTrianglesInAABB(const Ogre::Vector3& aabbMin, const Ogre::Vector3& aabbMax, std::vector< Triangle >& intersecting_triangles)
	{
		std::vector<Triangle>::iterator iter;

		for (iter = meshTriangles.begin(); iter != meshTriangles.end(); ++iter)
		{
			/// Check aginst triangle bounding box first to increase efficiency
			if (collide_triangle_bounding_box(aabbMin, aabbMax, *iter))
			{
				/// Perform the actual triangle-AABB test
				if (collide_triangle_exact(aabbMin, aabbMax, *iter))
				{
					intersecting_triangles.push_back(*iter);
				}
			}
		}

	}

	/// Decal constructor.
	//Decal::Decal()
	//{
	//    object = 0;
	//}

	/// DecalGenerator constructor
	DecalGenerator::DecalGenerator()
	{
		sceneMgr = 0;
	}

	/// DecalGenerator destructor
	DecalGenerator::~DecalGenerator()
	{
	}

	/// Turn debug drawing on, only works if DEBUG_ENABLED is true
	void DecalGenerator::turnDebugOn()
	{
		if (mDebugNode && DEBUG_ENABLED)
		{
			mDebugVisible = true;
			mDebugNode->setVisible(true, true);
		}
	}

	/// Turn debug drawing off, only works if DEBUG_ENABLED is true
	void DecalGenerator::turnDebugOff()
	{
		if (mDebugNode && DEBUG_ENABLED)
		{
			mDebugVisible = false;
			mDebugNode->setVisible(false, true);
		}
	}

	/// Flip debug drawing on/off, only works if DEBUG_ENABLED is true
	void DecalGenerator::flipDebug()
	{
		if (mDebugNode && DEBUG_ENABLED)
		{
			mDebugVisible = !mDebugVisible;
			mDebugNode->setVisible(mDebugVisible, true);
		}
	}

	/// Initialize the DecalGenerator. Not much to do here.
	void DecalGenerator::initialize(OgreSceneManager& ogreSceneManager)
	{
	//todo KH	sceneMgr = sceneManager;

		mDebugVisible = false;

		if (DEBUG_ENABLED)
		{
			mDebugNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
		}
		else
		{
			mDebugNode = 0;
		}
	}

	/// Add a triangle to the final decal object
	void DecalGenerator::AddTriangle(Ogre::v1::ManualObject* decalObject, std::vector< int >& points, int p1, int p2, int p3, Ogre::v1::ManualObject* lines)
	{
		int ai = points[0];
		int bi = points[p2 - p1];
		int ci = points[p3 - p1];

		if (!SHARE_VERTEX_NORMALS)
		{
			decalObject->triangle(p1, p2, p3);
		}
		else
		{
			decalObject->triangle(ai, bi, ci);
		}

		/// Debug stuff
		if (DEBUG_ENABLED)
		{
			Ogre::Vector3 v1 = uniquePoints[ai].p;
			Ogre::Vector3 v2 = uniquePoints[bi].p;
			Ogre::Vector3 v3 = uniquePoints[ci].p;

			lines->colour(Ogre::ColourValue::Red);

			lines->position(v1);
			lines->position(v2);

			lines->position(v1);
			lines->position(v3);

			lines->position(v2);
			lines->position(v3);
		}
	}

	/*

	 Generates the decal and returns a Decal object. The caller is responsible for NULL-checking the manual object.
	 This gigantic function should probably be chopped into smaller bite-sized pieces, but I'm just doo darn lazy.

	 @param mesh    The mesh to project the decal onto.
	 @param pos     The position of the decal
	 @param width   The width of the decal
	 @param height  The height of the decal
	 Note: The aspect ratio defined by width/height should match the texture, otherwise it will appear stretched.

	 @param materialName    The name of the material to use for the decal
	 @param flipTexture     Will randomly flip the texture to introduce variety (useful for blood splatter, explosion decals, etc.)
	 @param decalObject     If NULL, this function will automatically create a new manual object (default). Otherwise, it will re-use the one passed in.
	 For dynamic decals (generating one every frame), it is much more efficient to reuse the same manual object,
	 as long as the material doesn't change.


	 */
	Ogre::v1::ManualObject* DecalGenerator::createDecal(TriangleMesh* mesh, const Ogre::Vector3& pos, float width, float height,
		const Ogre::String& materialName, bool flipTexture, Ogre::v1::ManualObject* decalObject)
	{

		/// Clear out any old left-over stuff from the fridge.
		triangles.clear();
		uniquePoints.clear();
		finalPolys.clear();
		polygon_points.clear();

		float depth = max(width, height);


		/// Define our AABB 
		Ogre::Vector3 aabbMin = pos + Ogre::Vector3(-depth, -depth, -depth);
		Ogre::Vector3 aabbMax = pos + Ogre::Vector3(depth, depth, depth);


		/// We're gonna need triangles. Lot's of triangles.
		mesh->findTrianglesInAABB(aabbMin, aabbMax, triangles);

		if (triangles.empty())
		{
			/// No triangles were found, return an empty Decal
			/// Note that the caller is responsible for verifying the returned object
			return decalObject;
		}

		std::vector< Triangle >::iterator iter;
		Ogre::Vector3 averageN(0, 0, 0);

		/// Calculate the average normal of all the triangles gathered from our AABB
		for (iter = triangles.begin(); iter != triangles.end(); ++iter)
		{
			averageN += iter->normal;
		}

		/// This average normal length is too close to zero, which is a bad omen. Get out while we still can!
		if (averageN.length() < VEC_EPSILON)
		{
			return decalObject;
		}

		averageN.normalise();

		Ogre::Vector3 right, up;

		/// Calculate a coordinate space from the the average of all the triangle normals
		/// We're creating the projection box that will be used to clip the triangles

		if (averageN == Ogre::Vector3(0, 1, 0))
		{
			right = Ogre::Vector3(1, 0, 0);
		}
		else if (averageN == Ogre::Vector3(0, -1, 0))
		{
			right = Ogre::Vector3(-1, 0, 0);
		}
		else
		{
			right = (-averageN).crossProduct(Ogre::Vector3(0, 1, 0));
		}

		right.normalise();

		up = right.crossProduct(-averageN);
		up.normalise();


		/// Now that we have our coordinate space, let's define some planes. No silly, not the ones that fly in the sky!
		// These are the clipping planes! Be careful, because you might get cut.
		const int NUM_EDGE_PLANES = 6;

		Ogre::Vector4 edgePlanes[NUM_EDGE_PLANES];

		Ogre::Vector3 planeR[6];
		Ogre::Vector3 planeN[6];

		planeN[0] = averageN;
		planeN[1] = -averageN;
		planeN[2] = right;
		planeN[3] = -right;
		planeN[4] = up;
		planeN[5] = -up;


		/// These are to ensure that certain points are not "out of bounds"
		double distanceLimit = sqrt((depth * depth) + (depth * depth)) * 1.25;
		double edgeLimitX = sqrt((width * width) + (width * width)) * 1.05;
		double edgeLimitY = sqrt((height * height) + (height * height)) * 1.05;

		/// A point for each plane
		planeR[0] = pos + (planeN[0] * depth);
		planeR[1] = pos + (planeN[1] * depth);
		planeR[2] = pos + (planeN[2] * width);
		planeR[3] = pos + (planeN[3] * width);
		planeR[4] = pos + (planeN[4] * height);
		planeR[5] = pos + (planeN[5] * height);

		/// Set up each edge plane as a four dimensional vector defined in interstellar space. Carl Sagan would be all over this.
		for (int i = 0; i < NUM_EDGE_PLANES; ++i)
		{
			edgePlanes[i] = Ogre::Vector4(planeN[i].x, planeN[i].y, planeN[i].z, planeR[i].dotProduct(planeN[i]));
		}

		//Ogre::Vector3 averageNormal(0, 0, 0);
		//
		//double totalPoints = 0;
		//Ogre::Vector3 averagePoint;

		/// Loop through each triangle to find the meaning of life
		for (iter = triangles.begin(); iter != triangles.end(); ++iter)
		{
			polygon_points.clear();

			polygon_points.push_back(iter->v[0]);
			polygon_points.push_back(iter->v[1]);
			polygon_points.push_back(iter->v[2]);

			Ogre::Vector3 n = iter->normal;

			Ogre::Vector3 polygonNormal = n;

			/// Clip this triangle against each edge
			for (int edge = 0; edge < NUM_EDGE_PLANES; ++edge)
			{
				/// Clip the polygon against the edge plane.
				/// Why is this function returning duplicate points?

				//FIX http://www.ogre3d.org/forums/viewtopic.php?f=11&t=72683&start=25#p474540
				//std::cout << "Step vor neu -------:size" << polygon_points.size() << "," << polygon_points[0] << std::endl;
				//if (polygon_points.size() == 0)  // ADD THIS IF-STATEMENT
				//{
				//	continue;
				//}

				int clipped_count = 3;

				if (polygon_points.size() != 0)
					clipped_count = plane_clip_polygon(edgePlanes[edge], &(polygon_points[0]), polygon_points.size(), clippedPoints);
				//	std::cout << "Step x nach plane_clip_polygon -------: " << clipped_count << ",count:" << clippedPoints << std::endl;
				//	clipped_count = 3;

				polygon_points.clear();
				int index = 0;

				for (int i = 0; i < clipped_count; ++i)
				{
					Ogre::Vector3 p = clippedPoints[i];

					/// Do not use any duplicate points returned by plane_clip_polygon()
					if (!isDuplicate(polygon_points, p))
					{
						polygon_points.push_back(p);

						/// If this was the last edge plane we checked against, then we have all of our clipped points for this triangle
						if (edge == NUM_EDGE_PLANES - 1)
						{
							/// Check if this point was clipped by comparing it to each original vertex of the triangle.
							/// If this point is an original triangle vertex, then it wasn't clipped.
							if ((p - iter->v[0]).length() < VEC_EPSILON || (p - iter->v[1]).length() < VEC_EPSILON || (p - iter->v[2]).length() < VEC_EPSILON)
							{
								pointWasClipped[index] = false;
							}
							else
							{
								pointWasClipped[index] = true;
							}
						}

						++index;
					}
				}
			}


			/// If we ended up with less points than what we started out with, then we're in big horse doo-doo
			if (polygon_points.size() < 3)
				continue;

			finalPolys.push_back(DecalPolygon(polygonNormal));

			int size = polygon_points.size();

			double area = 1;

			/// Find the area of our freshly clipped polygon; used for generating a "better" vertex normal
			if (polygon_points.size() >= 3)
			{
				polygon_points.push_back(polygon_points[0]);
				polygon_points.push_back(polygon_points[1]);

				area = area3D_Polygon(size, &(polygon_points[0]), n);
			}

			/// Loop through each point in our clipped polygon, and find the unique ones.
			for (int i = 0; i < polygon_points.size() - 2; ++i)
			{
				Ogre::Vector3 p = polygon_points[i];

				/* averagePoint += p;
				 ++totalPoints;*/

				/// Make sure this point is not "out of bounds"
				if ((p - pos).length() < distanceLimit)
				{
					/// Check to see if this point is a duplicate
					/// Assuming this point is not a duplicate, set uniqueIndex to be the point added next
					int uniqueIndex = uniquePoints.size();

					/// If a duplicate is found, uniqueIndex will be set to that point
					if (!isDuplicate(uniquePoints, p, uniqueIndex))
					{
						uniquePoints.push_back(UniquePoint(p, pointWasClipped[i]));
					}

					/// Make sure we're still OK
					assert(uniqueIndex >= 0 && uniqueIndex < uniquePoints.size());

					// Update the normal for this point (we'll normalize it later). NormaLIZE.
					uniquePoints[uniqueIndex].normal += (polygonNormal * area);

					finalPolys.back().points.push_back(uniqueIndex);
				}

			}

			//    averageNormal += (n * area);
		}

		//std::cout << "Step x -1 -------" << std::endl;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		///                                                                                                                                ///
		///                             We intterupt this program to give you a brief word from our sponsers...                            ///
		///                                                                                                                                ///
		/// Congratulations. You've made it this far. Half the battle is over. At this point, we have all of our final clipped points.     ///
		/// Now we need to project those points to 2D so we can calculate the UV coordinates. Don't worry, there's more fudge on the way.  ///
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//   averageNormal.normalise();
		//   
		//if (totalPoints == 0)
		//	return Decal(); //shit!!

		//   averagePoint /= totalPoints;

		Ogre::Vector3 projectionPlaneNormal = -averageN;

		Ogre::Vector3 projectionPlaneRight = right;
		projectionPlaneRight.normalise();

		Ogre::Vector3 projectionPlaneUp = up;
		projectionPlaneUp.normalise();

		Ogre::Quaternion planeOrien(projectionPlaneRight, projectionPlaneUp, -projectionPlaneNormal);

		Ogre::Quaternion finalOrien(Ogre::Vector3(1, 0, 0), Ogre::Vector3(0, 1, 0), Ogre::Vector3(0, 0, -1));

		planeOrien.normalise();
		finalOrien.normalise();

		/// This is the quaternion we'll use to tranform each point so we can project them onto the XY plane
		/// This quaternion takes the projection plane's coordinate system (which is indentical our clipping box)
		/// and rotates it so that it is parrallel with the XY plane, at which point we nuke the Z axis on every point to
		/// project them into 2D.
		Ogre::Quaternion finalQuat = planeOrien.UnitInverse() * finalOrien;

		/// My mom always said, you can never normalize too much. Except when you spell it wrong.
		finalQuat.normalise();

		std::vector< DecalPolygon >::iterator pIter;

		double leftMost, rightMost, topMost, bottomMost;

		bool initCorners = false;

		Ogre::Vector3 center = finalQuat * pos;
		Ogre::Vector2 centerPoint(center.x, center.y);

		std::vector< UniquePoint >::iterator pointIter;

		//std::cout << "Step x -1 loop -------" << std::endl;

		/// Loop through all of our points and project them into 2D.
		for (pointIter = uniquePoints.begin(); pointIter != uniquePoints.end(); ++pointIter)
		{
			/// Rotate each point so that we can project them onto the XY plane
			/// finalQuat transforms the projection plane so that it's parallel with the XY plane
			Ogre::Vector3 v = finalQuat * pointIter->p;

			/// Project/flatten the point by eliminating the Z coordinate
			Ogre::Vector2 projectedPoint(v.x, v.y);

			pointIter->uvCoord = projectedPoint;

			/// Find the left, right, top, and bottom edge
			if (pointIter->isEdge)
			{
				Ogre::Vector2 diff = (projectedPoint - centerPoint);

				/// More fudge-checking to make sure nothing is out of bounds
				if (fabs(diff.x) < edgeLimitX && fabs(diff.y) < edgeLimitY)
				{
					if (!initCorners)
					{
						leftMost = rightMost = projectedPoint.x;
						topMost = bottomMost = projectedPoint.y;

						initCorners = true;
					}

					if (projectedPoint.x < leftMost)
						leftMost = projectedPoint.x;

					if (projectedPoint.x > rightMost)
						rightMost = projectedPoint.x;

					if (projectedPoint.y > topMost)
						topMost = projectedPoint.y;

					if (projectedPoint.y < bottomMost)
						bottomMost = projectedPoint.y;
				}
			}
		}

		//	std::cout << "Step x -2 -------" << std::endl;

		/// The hardest part is over. Now we get to fudge the UV coords, because you can never have too much fudge.

		std::vector< UniquePoint >::iterator topRight, bottomRight, topLeft, bottomLeft;

		Ogre::Vector2 cornerTopLeft(leftMost, topMost);
		Ogre::Vector2 cornerTopRight(rightMost, topMost);
		Ogre::Vector2 cornerBottomLeft(leftMost, bottomMost);
		Ogre::Vector2 cornerBottomRight(rightMost, bottomMost);

		bool initValues = false;

		double minDistanceTopLeft, minDistanceTopRight, minDistanceBottomLeft, minDistanceBottomRight;

		std::vector< UniquePoint >::iterator projectedPointIter;

		/// Loop throgh all of our (2D) points and figure out which points are nearest to each of the four corners.
		/// Why do we do this? Because I said so. Do not question my infinite wisdom.
		for (projectedPointIter = uniquePoints.begin(); projectedPointIter != uniquePoints.end(); ++projectedPointIter)
		{
			Ogre::Vector2 p = projectedPointIter->uvCoord;

			double distanceTopLeft = (p - cornerTopLeft).length();
			double distanceTopRight = (p - cornerTopRight).length();
			double distanceBottomLeft = (p - cornerBottomLeft).length();
			double distanceBottomRight = (p - cornerBottomRight).length();

			if (!initValues)
			{
				initValues = true;

				topRight = projectedPointIter;
				topLeft = projectedPointIter;
				bottomRight = projectedPointIter;
				bottomLeft = projectedPointIter;

				minDistanceTopLeft = distanceTopLeft;
				minDistanceTopRight = distanceTopRight;
				minDistanceBottomLeft = distanceBottomLeft;
				minDistanceBottomRight = distanceBottomRight;
			}
			else
			{
				if (distanceTopLeft < minDistanceTopLeft)
				{
					minDistanceTopLeft = distanceTopLeft;
					topLeft = projectedPointIter;
				}

				if (distanceTopRight < minDistanceTopRight)
				{
					minDistanceTopRight = distanceTopRight;
					topRight = projectedPointIter;
				}

				if (distanceBottomLeft < minDistanceBottomLeft)
				{
					minDistanceBottomLeft = distanceBottomLeft;
					bottomLeft = projectedPointIter;
				}

				if (distanceBottomRight < minDistanceBottomRight)
				{
					minDistanceBottomRight = distanceBottomRight;
					bottomRight = projectedPointIter;
				}
			}
		}

		if (!initValues)
			return decalObject; //mist !!

		/// Here we calculate (via fudge factor) the UV edges which are used to determine the UV coords.
		/// This is the fudge motherload.
		/// I could try to explain why we're doing this, but it would just sound like I have no idea what I'm talking about.
		/// Which is probably true.
		rightMost = average(average(topRight->uvCoord.x, bottomRight->uvCoord.x), rightMost);
		leftMost = average(average(topLeft->uvCoord.x, bottomLeft->uvCoord.x), leftMost);

		topMost = average(average(topLeft->uvCoord.y, topRight->uvCoord.y), topMost);
		bottomMost = average(average(bottomRight->uvCoord.y, bottomLeft->uvCoord.y), bottomMost);

		/// Calcuate the width and height used to calculate UV coords.
		width = rightMost - leftMost;
		height = topMost - bottomMost;

		int randomFlipType = 0;

		if (flipTexture)
			randomFlipType = rand() % 8;

		//	std::cout << "Step x -3 -------" << std::endl;


		/// Ok, now we get to the final UV coords. For real this time, no kidding.
		for (projectedPointIter = uniquePoints.begin(); projectedPointIter != uniquePoints.end(); ++projectedPointIter)
		{
			Ogre::Vector2 p = projectedPointIter->uvCoord;

			double uvMin = 0;
			double uvMax = 1;

			/// Ta da!
			double u = (p.x - leftMost) / width;
			double v = (p.y - bottomMost) / height;

			/// Oops, we wouldn't want any rebel coordiantes wreaking havoc.
			if (u < uvMin)
				u = uvMin;
			else if (u > uvMax)
				u = uvMax;

			if (v < uvMin)
				v = uvMin;
			else if (v > uvMax)
				v = uvMax;

			projectedPointIter->uvCoord.x = u;
			projectedPointIter->uvCoord.y = (1 - v);

			/// Randomly flip UV coords between 8 different ways
			/// This might be desirable for things like blood splatter, explosions, etc to simply introduce variety
			if (flipTexture && randomFlipType > 0)
			{
				switch (randomFlipType)
				{
				case 1:
				{
					projectedPointIter->uvCoord.x = (1 - u);
					projectedPointIter->uvCoord.y = (1 - v);
				}
				case 2:
				{
					projectedPointIter->uvCoord.x = (1 - u);
					projectedPointIter->uvCoord.y = v;
				}
				case 3:
				{
					projectedPointIter->uvCoord.x = u;
					projectedPointIter->uvCoord.y = v;
				}
				case 4:
				{
					projectedPointIter->uvCoord.y = (1 - u);
					projectedPointIter->uvCoord.x = (1 - v);
				}
				case 5:
				{
					projectedPointIter->uvCoord.y = (1 - u);
					projectedPointIter->uvCoord.x = v;
				}
				case 6:
				{
					projectedPointIter->uvCoord.y = u;
					projectedPointIter->uvCoord.x = v;
				}
				case 7:
				{
					projectedPointIter->uvCoord.y = u;
					projectedPointIter->uvCoord.x = (1 - v);

				}
				}

			}
		}


		/// All of the final UV coords have been generated. Now it's rendering time. 
		/// What are you waiting for? Let's make that manual object that you've been dreaming about.

		std::vector<UniquePoint>::iterator uniqueIter;

		/// Debug drawing stuff
		//if (DEBUG_ENABLED)
		//{
		//	Ogre::v1::ManualObject* moDebug = sceneMgr->createManualObject();

		//	moDebug->begin("debug_draw", Ogre::v1::RenderOperation::OT_TRIANGLE_LIST);

		//	int indexOffset = 0;

		//	for (uniqueIter = uniquePoints.begin(); uniqueIter != uniquePoints.end(); ++uniqueIter)
		//	{
		//	//KH todo	createCubeMesh(sceneMgr, uniqueIter->p, 0.25, Ogre::ColourValue::Red, moDebug, indexOffset);
		//		indexOffset += 8;
		//	}

		//	moDebug->end();

		//	if (!mDebugVisible)
		//		moDebug->setVisible(false);

		//	mDebugNode->attachObject(moDebug);
		//}


		///// "lines" is used for debug drawing triangles
		//Ogre::v1::ManualObject* lines = 0;

		//if (DEBUG_ENABLED)
		//{
		//	lines = sceneMgr->createManualObject();
		//	lines->begin("debug_draw", Ogre::v1::RenderOperation::OT_LINE_LIST);
		//}

		////	std::cout << "Step x -create -------" << std::endl;

		///// Create a new manual object if this one doesn't exist
		//if (!decalObject)
		//{
		//	decalObject = sceneMgr->createManualObject();
		//}
		//else
		//{
		//	/// Make sure the decal object can be dynmically updated
		//	if (!decalObject->getDynamic())
		//		decalObject->setDynamic(true);
		//}

		//Ogre::String material = materialName;

		//if (decalObject->getDynamic() && decalObject->getNumSections() > 0)
		//{
		//	/// Update the existng decal instead of starting a new one
		//	decalObject->beginUpdate(0);
		//}
		//else
		//{
		//	/// Start a new decal
		//	decalObject->begin(material, Ogre::v1::RenderOperation::OT_TRIANGLE_LIST);
		//}

		/// If we're sharing vertices, then simply set up all of the vertex info ahead of time
		if (SHARE_VERTEX_NORMALS)
		{
			for (uniqueIter = uniquePoints.begin(); uniqueIter != uniquePoints.end(); ++uniqueIter)
			{

				uniqueIter->normal.normalise();


				//uniqueIter->p = uniqueIter->p - 25.8 * uniqueIter->normal;


				decalObject->position(uniqueIter->p);
				decalObject->normal(uniqueIter->normal);
				decalObject->textureCoord(uniqueIter->uvCoord);
			}
		}

		int p1, p2, p3;
		p1 = p2 = p3 = 0;

		// Each of these finalPolys is a just list of indicies into the uniquePoints vector
	/*	for (pIter = finalPolys.begin(); pIter != finalPolys.end(); ++pIter)
		{
			std::vector< int >::iterator iter;

			Ogre::Vector3 norm = pIter->norm;

			if (pIter->points.size() >= 3)
			{
				p2 = p1 + 1;
				p3 = p2 + 1;

				int t = 0;

				for (iter = pIter->points.begin(); iter != pIter->points.end(); ++iter)
				{
					if (!SHARE_VERTEX_NORMALS)
					{
						decalObject->position(uniquePoints[*iter].p);
						decalObject->normal(norm);
						decalObject->textureCoord(uniquePoints[*iter].uvCoord);
					}

					if (t >= 3)
					{
						++p2;
						++p3;

						AddTriangle(decalObject, pIter->points, p1, p2, p3, lines);
					}

					++t;

					if (t == 3)
					{
						AddTriangle(decalObject, pIter->points, p1, p2, p3, lines);
					}

				}

				p1 = p3 + 1;
			}
		}

		decalObject->end();

		/// Finish debug drawing stuff
		if (DEBUG_ENABLED)
		{
			lines->end();

			if (!mDebugVisible)
				lines->setVisible(false);

			mDebugNode->attachObject(lines);

		}*/

		/// And were done. Phew.
		//  Decal decal;
		// decal.object = decalObject;

		return decalObject;
	}

}


